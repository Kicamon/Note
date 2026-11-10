#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
latex_to_notebook.py — 从 LaTeX 文件提取题目并追加到错题本

用法:
    python3 latex_to_notebook.py              # 粘贴模式: 运行后直接粘贴题目, 按 Ctrl+D 结束
    python3 latex_to_notebook.py 题目.tex [题目2.tex ...]
    python3 latex_to_notebook.py --notebook 错题本.md 题目.tex
    cat 题目.tex | python3 latex_to_notebook.py -

提取规则 (按优先级):
    1. 取 \\begin{document} 与 \\end{document} 之间的正文 (无 document 环境则用全文,
       并剔除 \\documentclass / \\usepackage 等导言区命令)
    2. 切分题目:
       a. 若存在注释标签 ("% 题目" / "% 第一个证明" / "% 第1题" 等), 按标签切分,
          每个标签后的内容为一道题;
       b. 否则若存在 "\\textbf{证明:}" 等标记:
          - 若第一个标记前有实质内容 (题目在前、解答在后的结构), 取每个标记前的段落;
          - 否则 (题目跟在标记后), 取每个标记后的内容;
       c. 否则全文视为一道题
    3. 转换格式:
       \\[..\\] / $$..$$ / equation / align 等环境  →  $$..$$ 展示公式块
       $..$                                           保留为行内公式
       \\textbf{..} → **..**,  \\emph{..} → *..*
       删除 LaTeX 注释 (% 到行尾) 与多余空白
    4. 追加到错题本 (默认: 脚本同目录的 mathematical_errors.md), 条目间以 --- 分隔,
       只写题目, 不写解题步骤

参数:
    --notebook PATH   错题本文件路径 (默认 mathematical_errors.md)
    --dry-run         只显示将要写入的内容, 不实际写入
    -y, --yes         粘贴模式下跳过写入确认

粘贴模式说明:
    不带文件参数运行即进入粘贴模式, 提示出现后直接粘贴 LaTeX 内容
    (可一次粘贴多道题), 粘贴完成后按 Ctrl+D (Windows: Ctrl+Z 后回车) 结束;
    单独输入 q 回车可放弃本次操作。
"""

import argparse
import os
import re
import sys
from pathlib import Path

SCRIPT_DIR = Path(__file__).resolve().parent
DEFAULT_NOTEBOOK = SCRIPT_DIR / "mathematical_errors.md"

# 题目边界标记
# "% 题目" / "% 第一个证明" / "% 第1题" / "% 第二道题" 等注释标签
TOPIC_COMMENT = re.compile(
    r'^\s*%\s*(?:题目|第\s*[0-9一二三四五六七八九十]+\s*(?:个\s*证明|道题|题))[^\n]*$',
    re.M)
PROOF_MARKER = re.compile(r'\\textbf\s*\{\s*证明\s*[:：]?\s*\}')  # \textbf{证明:} 等

# 可转为展示公式的数学环境
ENVIRONMENTS = r'equation\*?|align\*?|aligned|gather\*?|multline\*?'


def read_text(path: Path) -> str:
    """读取文本, 依次尝试 utf-8 / gb18030 编码。"""
    for enc in ('utf-8', 'gb18030'):
        try:
            return path.read_text(encoding=enc)
        except UnicodeDecodeError:
            continue
    return path.read_text(encoding='utf-8', errors='replace')


def strip_comments(tex: str) -> str:
    """删除 LaTeX 注释: % 到行尾 (保护 \\%)。"""
    tex = tex.replace(r'\%', '\x00')
    tex = re.sub(r'%[^\n]*', '', tex)
    return tex.replace('\x00', r'\%')


def extract_body(tex: str) -> str:
    """截取 document 环境内的正文; 没有则剔除导言区命令后返回全文。"""
    m = re.search(r'\\begin\{document\}', tex)
    if m:
        tex = tex[m.end():]
    e = re.search(r'\\end\{document\}', tex)
    if e:
        tex = tex[:e.start()]
    # 剔除可能残留的导言区命令
    tex = re.sub(r'\\documentclass\s*(?:\[[^\]]*\])?\{[^}]*\}', '', tex)
    tex = re.sub(r'\\usepackage\s*(?:\[[^\]]*\])?\{[^}]*\}', '', tex)
    return tex


def clean_problem_head(chunk: str) -> str:
    """去掉题目开头残留的 \\textbf{证明...} / 冒号 / 空白。"""
    chunk = re.sub(
        r'^\s*(?:\\noindent\s*)?\\textbf\s*\{\s*证明\s*[:：]?\s*\}',
        '', chunk)
    return chunk.strip(' :：\n\t')


def split_problems(body: str) -> list:
    """按标记切分题目, 返回题目原始文本列表。"""
    body = body.strip()
    if not body:
        return []
    if TOPIC_COMMENT.search(body):          # 优先: % 题目 / % 第N个证明 等注释标签
        parts = TOPIC_COMMENT.split(body)
    elif PROOF_MARKER.search(body):         # 其次: \textbf{证明...} 标记
        parts = PROOF_MARKER.split(body)
        # 判断题目在标记前还是标记后:
        # 标记前有实质内容 → 题目在前、解答在后, 取每个标记前的段落 (交替取)
        # 否则 → 题目跟在标记后, 取每个标记后的内容
        if strip_comments(parts[0]).strip():
            parts = parts[0::2]
        else:
            parts = parts[1:]
    else:                                   # 兜底: 全文一道题
        parts = [body]
    return [clean_problem_head(p) for p in parts if p.strip()]


def latex_to_markdown(chunk: str) -> str:
    """将一段 LaTeX 题目文本转为错题本格式的 markdown。"""
    # 数学环境 → $$...$$ (含 equation / align / aligned 等)
    chunk = re.sub(
        r'\\begin\{(%s)\}(.*?)\\end\{\1\}' % ENVIRONMENTS,
        lambda m: '\n$$\n' + m.group(2).strip() + '\n$$\n',
        chunk, flags=re.S)
    # \[ ... \] → $$...$$
    chunk = re.sub(
        r'\\\[\s*(.*?)\s*\\\]',
        lambda m: '\n$$\n' + m.group(1).strip() + '\n$$\n',
        chunk, flags=re.S)
    # $$ ... $$ → $$...$$
    chunk = re.sub(
        r'\$\$\s*(.*?)\s*\$\$',
        lambda m: '\n$$\n' + m.group(1).strip() + '\n$$\n',
        chunk, flags=re.S)
    # 行内公式去首尾空格: $ x $ → $x$
    chunk = re.sub(r'\$\s*(.*?)\s*\$', r'$\1$', chunk)
    # 文本格式命令
    chunk = re.sub(r'\\textbf\s*\{([^{}]*)\}', r'**\1**', chunk)
    chunk = re.sub(r'\\emph\s*\{([^{}]*)\}', r'*\1*', chunk)
    chunk = chunk.replace('~', ' ').replace(r'\ ', ' ')
    # 清理多余空白 (保留空行分隔段落与公式块)
    lines = [ln.strip() for ln in chunk.splitlines()]
    out, blank = [], False
    for ln in lines:
        if not ln:
            if not blank:
                out.append('')
            blank = True
        else:
            out.append(ln)
            blank = False
    return '\n'.join(out).strip()


def process(tex: str) -> list:
    """完整流程: 取正文 → 切分题目 → 转 markdown。"""
    body = extract_body(tex)
    problems = split_problems(body)
    problems = [strip_comments(p) for p in problems]
    return [latex_to_markdown(p) for p in problems if p.strip()]


def append_problems(notebook: Path, problems: list, dry_run: bool = False) -> None:
    """将题目列表追加到错题本, 条目间以 --- 分隔。"""
    text = notebook.read_text(encoding='utf-8') if notebook.exists() else ''
    block = '\n\n---\n\n'.join(problems)
    if text.strip():
        if not re.search(r'---\s*$', text):     # 已有内容且末尾无分隔线 → 先补一条
            block = '\n\n---\n\n' + block
        else:
            block = '\n\n' + block
    else:                                        # 新错题本 → 加标题
        block = '# 数学错题本\n\n' + block
    if dry_run:
        print('---- 将写入以下内容 ----')
        print(block)
        return
    with open(notebook, 'a', encoding='utf-8') as f:
        f.write(block.rstrip() + '\n')


def ask_confirm(prompt: str) -> bool:
    """直接从控制终端读取确认 (粘贴模式下 stdin 已读到 EOF, 不能再读)。

    返回 True 表示继续; 无法打开控制终端 (非交互环境) 时默认继续。
    """
    print(prompt, end='', flush=True)
    try:
        tty_path = '/dev/tty' if os.name != 'nt' else 'CONIN$'
        with open(tty_path, 'r') as tty:
            ans = tty.readline().strip().lower()
    except OSError:
        return True
    return ans not in ('n', 'no', '0')


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description='从 LaTeX 提取题目并追加到错题本')
    ap.add_argument('files', nargs='*',
                    help='LaTeX 源文件 (可选); 不传则进入粘贴模式; 传 - 从标准输入读取')
    ap.add_argument('--notebook', default=str(DEFAULT_NOTEBOOK),
                    help='错题本路径 (默认: 脚本同目录的 mathematical_errors.md)')
    ap.add_argument('--dry-run', action='store_true',
                    help='只显示将要写入的内容, 不实际写入')
    ap.add_argument('-y', '--yes', action='store_true',
                    help='粘贴模式下跳过写入确认')
    args = ap.parse_args(argv)

    interactive = not args.files
    all_problems = []

    def show_problems(problems: list) -> None:
        for i, p in enumerate(problems, 1):
            flat = p.replace('\n', ' ')
            suffix = '...' if len(flat) > 60 else ''
            print(f'  {i}. {flat[:60]}{suffix}')

    if args.files:
        for fname in args.files:
            if fname == '-':
                tex, name = sys.stdin.read(), '<stdin>'
            else:
                tex, name = read_text(Path(fname)), fname
            problems = process(tex)
            print(f'[{name}] 提取到 {len(problems)} 道题:')
            show_problems(problems)
            all_problems.extend(problems)
    else:
        # 粘贴模式
        print('粘贴模式: 请粘贴需要整理的 LaTeX 题目 (可一次粘贴多道), 完成后:',
              flush=True)
        print('  Linux/macOS: 按 Ctrl+D 结束    Windows: 按 Ctrl+Z 后回车',
              flush=True)
        print('  单独输入 q 回车可放弃本次操作', flush=True)
        print('-' * 50, flush=True)
        tex = sys.stdin.read()
        if tex.strip().lower() in ('q', 'quit', '退出'):
            print('已放弃, 未做任何修改。')
            return 0
        if not tex.strip():
            print('未读取到任何内容, 未做任何修改。', file=sys.stderr)
            return 1
        problems = process(tex)
        print(f'提取到 {len(problems)} 道题:')
        show_problems(problems)
        all_problems = problems

    if not all_problems:
        print('未提取到任何题目, 未做任何修改。', file=sys.stderr)
        return 1

    if interactive and not args.yes and not args.dry_run:
        if not ask_confirm(
                f'确认将这 {len(all_problems)} 道题追加到 {args.notebook}? [Y/n] '):
            print('已取消, 未做任何修改。')
            return 0

    append_problems(Path(args.notebook), all_problems, dry_run=args.dry_run)
    if not args.dry_run:
        print(f'已将 {len(all_problems)} 道题追加到 {args.notebook}')
    return 0


if __name__ == '__main__':
    sys.exit(main())
