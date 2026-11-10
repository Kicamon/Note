#!/usr/bin/env lua
-- -*- coding: utf-8 -*-
-- latex_to_notebook.lua — 从 LaTeX 提取题目并追加到错题本 (Lua 版)
--
-- 用法:
--   lua latex_to_notebook.lua                 粘贴模式: 运行后直接粘贴题目, 按 Ctrl+D 结束
--   lua latex_to_notebook.lua 题目.tex [题目2.tex ...]
--   lua latex_to_notebook.lua --notebook 错题本.md 题目.tex
--   cat 题目.tex | lua latex_to_notebook.lua -
--
-- 参数:
--   --notebook PATH   错题本文件路径 (默认: 脚本同目录 mathematical_errors.md)
--   --dry-run         只显示将要写入的内容, 不实际写入
--   -y, --yes         粘贴模式下跳过写入确认
--
-- 粘贴模式说明:
--   不带文件参数运行即进入粘贴模式, 提示出现后直接粘贴 LaTeX 内容
--   (可一次粘贴多道题), 粘贴完成后按 Ctrl+D (Windows: Ctrl+Z 后回车) 结束;
--   单独输入 q 回车可放弃本次操作。
--
-- 提取规则 (与 latex_to_notebook.py 一致):
--   1. 取 \begin{document} 与 \end{document} 之间的正文, 剔除导言区命令
--   2. 切分题目:
--      a. "% 题目" / "% 第一个证明" / "% 第1题" 等注释标签 → 每个标签后的内容为一道题
--      b. 否则 "\textbf{证明:}" 等标记 → 标记前有实质内容取标记前段落(题目+解答结构),
--         否则取每个标记后的内容
--      c. 否则全文视为一道题
--   3. 转换: \[..\] / $$..$$ / equation / align 等环境 → $$..$$ 展示公式块;
--      $..$ 保留为行内公式; \textbf{} → **..**; 删除注释与多余空白
--   4. 追加到错题本, 条目间以 --- 分隔, 只写题目, 不写解题步骤

local is_windows = package.config:sub(1, 1) == "\\"

-- 脚本所在目录 (用于默认错题本路径)
local SCRIPT_DIR = (arg and arg[0] or ""):match("^(.*)[/\\][^/\\]*$") or "."
local DEFAULT_NOTEBOOK = SCRIPT_DIR .. "/mathematical_errors.md"

-- \textbf{证明:} / \textbf{证明：} 标记 (半角/全角冒号分别匹配)
local PROOF_PATS = {
  "\\textbf%s*{%s*证明%s*:%s*}",
  "\\textbf%s*{%s*证明%s*：%s*}",
}

-- 可转为展示公式的数学环境
local ENVS = {
  "equation", "equation*", "align", "align*", "aligned",
  "gather", "gather*", "multline", "multline*",
}

local function trim(s)
  return (s:gsub("^%s+", ""):gsub("%s+$", ""))
end

local function trim_marks(s)
  s = s:gsub("^[%s:]+", ""):gsub("[%s:]+$", "")  -- 半角
  s = s:gsub("^：", ""):gsub("：$", "")           -- 全角冒号
  return s
end

-- 删除 LaTeX 注释: % 到行尾 (保护 \%)
-- 占位符用 \1 (SOH) 而不用 \0: LuaJIT 把 NUL 当作 C 字符串终止符, 会导致模式变空
local function strip_comments(tex)
  tex = tex:gsub("\\%%", "\1")
  tex = tex:gsub("%%[^\n]*", "")
  return tex:gsub("\1", "\\%%")
end

-- 截取 document 环境内的正文; 剔除导言区命令
local function extract_body(tex)
  local _, b = tex:find("\\begin{document}")
  if b then tex = tex:sub(b + 1) end
  local e = tex:find("\\end{document}")
  if e then tex = tex:sub(1, e - 1) end
  tex = tex:gsub("\\documentclass%s*%[?[^%]]*%]?%{[^}]*%}", "")
  tex = tex:gsub("\\usepackage%s*%[?[^%]]*%]?%{[^}]*%}", "")
  return tex
end

-- 判断一行是否为题目注释标签: "% 题目" / "% 第一个证明" / "% 第1题" 等
-- (Lua 模式无 "|" 分支, 用三个独立匹配)
local function is_topic_line(line)
  return line:match("^%%%s*题目") ~= nil
      or line:match("^%%%s*第.-证明") ~= nil
      or line:match("^%%%s*第.-题") ~= nil
end

local function split_lines(body)
  local lines = {}
  for ln in body:gmatch("[^\n]*") do
    table.insert(lines, ln)
  end
  return lines
end

-- 按标记切分题目, 返回题目原始文本列表
local function split_problems(body)
  body = trim(body)
  if body == "" then return {} end

  -- 优先: 注释标签切分
  local has_topic = false
  for _, ln in ipairs(split_lines(body)) do
    if is_topic_line(ln) then
      has_topic = true
      break
    end
  end

  local parts = {}
  if has_topic then
    local current = {}
    for _, ln in ipairs(split_lines(body)) do
      if is_topic_line(ln) then
        if #current > 0 then
          table.insert(parts, table.concat(current, "\n"))
          current = {}
        end
      else
        table.insert(current, ln)
      end
    end
    if #current > 0 then table.insert(parts, table.concat(current, "\n")) end
  else
    -- 其次: \textbf{证明...} 标记
    local markers = {}
    for _, pat in ipairs(PROOF_PATS) do
      local pos = 1
      while true do
        local s, e = body:find(pat, pos)
        if not s then break end
        table.insert(markers, { s, e })
        pos = e + 1
      end
    end
    if #markers > 0 then
      table.sort(markers, function(a, b) return a[1] < b[1] end)
      local pos = 1
      for _, mk in ipairs(markers) do
        table.insert(parts, body:sub(pos, mk[1] - 1))
        pos = mk[2] + 1
      end
      table.insert(parts, body:sub(pos))
      -- 标记前有实质内容 → 题目在前、解答在后, 取每个标记前的段落 (交替取)
      if strip_comments(trim(parts[1])) ~= "" then
        local out = {}
        for j = 1, #parts, 2 do table.insert(out, parts[j]) end
        parts = out
      else
        -- 否则题目跟在标记后, 取每个标记后的内容
        local out = {}
        for j = 2, #parts do table.insert(out, parts[j]) end
        parts = out
      end
    else
      parts = { body }
    end
  end

  -- 去掉题目开头残留的 \textbf{证明...} / 冒号 / 空白
  -- (Lua 模式不支持 (捕获)? 量化, 带/不带 \noindent 分两条匹配)
  local problems = {}
  for _, raw in ipairs(parts) do
    local p = raw
    p = p:gsub("^%s*\\noindent%s*\\textbf%s*{%s*证明%s*:%s*}", "")
    p = p:gsub("^%s*\\textbf%s*{%s*证明%s*:%s*}", "")
    p = p:gsub("^%s*\\noindent%s*\\textbf%s*{%s*证明%s*：%s*}", "")
    p = p:gsub("^%s*\\textbf%s*{%s*证明%s*：%s*}", "")
    p = trim_marks(p)
    if p ~= "" then table.insert(problems, p) end
  end
  return problems
end

-- 将一段 LaTeX 题目文本转为错题本格式的 markdown
local function latex_to_markdown(chunk)
  -- 数学环境 → $$...$$
  for _, env in ipairs(ENVS) do
    local pat = "\\begin{" .. env .. "}(.-)\\end{" .. env .. "}"
    chunk = chunk:gsub(pat, function(inner)
      return "\n$$\n" .. trim(inner) .. "\n$$\n"
    end)
  end
  -- \[ ... \] → $$...$$
  chunk = chunk:gsub("\\%[(.-)\\]", function(inner)
    return "\n$$\n" .. trim(inner) .. "\n$$\n"
  end)
  -- $$ ... $$ → $$...$$
  chunk = chunk:gsub("%$%$(.-)%$%$", function(inner)
    return "\n$$\n" .. trim(inner) .. "\n$$\n"
  end)
  -- 行内公式去首尾空格: $ x $ → $x$
  chunk = chunk:gsub("%$(.-)%$", function(inner)
    return "$" .. trim(inner) .. "$"
  end)
  -- 文本格式命令
  chunk = chunk:gsub("\\textbf%s*{(.-)}", "**%1**")
  chunk = chunk:gsub("\\emph%s*{(.-)}", "*%1*")
  chunk = chunk:gsub("~", " ")
  chunk = chunk:gsub("\\ ", " ")
  -- 清理多余空白 (保留空行分隔段落与公式块)
  local out, blank = {}, false
  for raw in chunk:gmatch("[^\n]*") do
    local ln = trim(raw)
    if ln == "" then
      if not blank then table.insert(out, "") end
      blank = true
    else
      table.insert(out, ln)
      blank = false
    end
  end
  return trim(table.concat(out, "\n"))
end

-- 完整流程: 取正文 → 切分题目 → 转 markdown
local function process(tex)
  local out = {}
  for _, p in ipairs(split_problems(extract_body(tex))) do
    p = latex_to_markdown(strip_comments(p))
    if p ~= "" then table.insert(out, p) end
  end
  return out
end

local function read_file(path)
  local f = io.open(path, "rb")
  if not f then return nil end
  local s = f:read("*a")
  f:close()
  return s
end

-- 将题目列表追加到错题本, 条目间以 --- 分隔
local function append_problems(notebook, problems, dry_run)
  local content = read_file(notebook) or ""
  local block = table.concat(problems, "\n\n---\n\n")
  if trim(content) ~= "" then
    if not content:match("%-%-%-%s*$") then   -- 已有内容且末尾无分隔线 → 先补一条
      block = "\n\n---\n\n" .. block
    else
      block = "\n\n" .. block
    end
  else                                        -- 新错题本 → 加标题
    block = "# 数学错题本\n\n" .. block
  end
  if dry_run then
    print("---- 将写入以下内容 ----")
    print(block)
    return
  end
  local f = io.open(notebook, "a")
  if not f then
    print("无法写入文件: " .. notebook)
    os.exit(1)
  end
  f:write(block:gsub("%s+$", "") .. "\n")
  f:close()
end

-- 直接从控制终端读取确认 (粘贴模式下 stdin 已读到 EOF, 不能再读)
local function ask_confirm(prompt)
  io.write(prompt)
  io.flush()
  local tty_path = is_windows and "CONIN$" or "/dev/tty"
  local ok, tty = pcall(io.open, tty_path, "r")
  if not ok or not tty then return true end  -- 非交互环境默认继续
  local ans = tty:read("*l")
  tty:close()
  ans = (ans or ""):lower()
  return not (ans == "n" or ans == "no" or ans == "0")
end

local function show_problems(problems)
  for i, p in ipairs(problems) do
    local flat = p:gsub("\n", " ")
    local suffix = ""
    if #flat > 60 then suffix = "..." end
    print(string.format("  %d. %s%s", i, flat:sub(1, 60), suffix))
  end
end

-- ================= 主流程 =================

local notebook = DEFAULT_NOTEBOOK
local dry_run, yes = false, false
local files = {}
local i = 1
while i <= #arg do
  local a = arg[i]
  if a == "--notebook" then
    i = i + 1
    if not arg[i] then
      print("--notebook 需要一个路径参数")
      os.exit(2)
    end
    notebook = arg[i]
  elseif a == "--dry-run" then
    dry_run = true
  elseif a == "-y" or a == "--yes" then
    yes = true
  elseif a:sub(1, 1) == "-" and a ~= "-" then
    print("未知参数: " .. a)
    os.exit(2)
  else
    table.insert(files, a)
  end
  i = i + 1
end

local interactive = #files == 0
local all_problems = {}

if #files > 0 then
  for _, fname in ipairs(files) do
    local tex
    if fname == "-" then
      tex = io.read("*a")
    else
      tex = read_file(fname)
      if not tex then
        print("无法读取文件: " .. fname)
        os.exit(1)
      end
    end
    local problems = process(tex)
    print(string.format("[%s] 提取到 %d 道题:", fname, #problems))
    show_problems(problems)
    for _, p in ipairs(problems) do table.insert(all_problems, p) end
  end
else
  -- 粘贴模式
  print("粘贴模式: 请粘贴需要整理的 LaTeX 题目 (可一次粘贴多道), 完成后:")
  print("  Linux/macOS: 按 Ctrl+D 结束    Windows: 按 Ctrl+Z 后回车")
  print("  单独输入 q 回车可放弃本次操作")
  print(string.rep("-", 50))
  io.flush()
  local tex = io.read("*a")
  local q = trim(tex):lower()
  if q == "q" or q == "quit" or q == "退出" then
    print("已放弃, 未做任何修改。")
    os.exit(0)
  end
  if trim(tex) == "" then
    print("未读取到任何内容, 未做任何修改。")
    os.exit(1)
  end
  local problems = process(tex)
  print(string.format("提取到 %d 道题:", #problems))
  show_problems(problems)
  all_problems = problems
end

if #all_problems == 0 then
  print("未提取到任何题目, 未做任何修改。")
  os.exit(1)
end

if interactive and not yes and not dry_run then
  local ok = ask_confirm(string.format(
      "确认将这 %d 道题追加到 %s? [Y/n] ", #all_problems, notebook))
  if not ok then
    print("已取消, 未做任何修改。")
    os.exit(0)
  end
end

append_problems(notebook, all_problems, dry_run)
if not dry_run then
  print(string.format("已将 %d 道题追加到 %s", #all_problems, notebook))
end
