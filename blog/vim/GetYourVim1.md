## 从0打造属于你的neovim[1]

> 在上一期当中，我们简单讲解了neovim的基本配置，这一期我们继续，讲解**基本插件与配置**

### 插件管理器
#### 为什么要用插件管理器？
在这里推荐使用插件管理器来管理插件，这样子较为方便。常用的插件管理器有：
1. [lazy.nvim](https://github.com/folke/lazy.nvim)
2. [packer.nvim](https://github.com/wbthomason/packer.nvim)
3. [vim-plug](https://github.com/junegunn/vim-plug)

本文使用**lazy.nvim**作为插件管理器，你也可以选择自己喜欢的插件管理器

#### 使用lazy.nvim安装第一个插件
首先，我们进入到`~/.config/nvim/lua/config/`目录当中，创建文件`plugins.lua`文件

打开plugins.lua，将下列代码粘贴到文件中：
```lua
local lazypath = vim.fn.stdpath("data") .. "/lazy/lazy.nvim"
if not vim.loop.fs_stat(lazypath) then
  vim.fn.system({
    "git",
    "clone",
    "--filter=blob:none",
    "https://github.com/folke/lazy.nvim.git",
    "--branch=stable", -- latest stable release
    lazypath,
  })
end
vim.opt.rtp:prepend(lazypath)
```

这个文件的作用就是启用`lazy.nvim`插件

然后，我们创建目录`~/.config/nvim/lua/plugins/`，这个目录将被用于配置我们需要的插件。

我们来以主题插件为例，演示一下如何使用`lazy.nvim`安装配置插件：

创建文件`ui.lua`，进入到文件中，将下面代码粘贴到文件中：
```lua
return {
    'Kicamon/gruvbox.nvim',
    lazy = false,
    priority = 1000,
    config = function()
      vim.cmd("colorscheme gruvbox")
    end,
}
```

1. 这里我们使用了gruvbox主题，`Kicamon/gruvbox.nvim`是插件的github仓库位置，完整网址为`https://github.com/Kicamon/gruvbox.nvim`
2. `lazy = false`表示这个插件不使用懒加载，也就是无论如何打开neovim，这个插件都会被启用
3. `priority = 1000`表示这个插件的优先级为1000，这个值默认为50，将优先级调高，则插件会优先加载。因为主题插件具有特殊性，所以将其优先级调高
4. `config`这个函数就是插件的配置函数。这里，我们使用`vim.cmd("colorscheme gruvbox")`命令来启用主题
5. 最后，我们回到`~/.config/nvim/lua/config/plugins.lua`当中，在文件的末尾加上
    ```lua
    require("lazy").setup({
        require("plugins.ui"),
    })
    ```


#### 插件分类
再看一眼我们的文件目录
```lua
~/.config/nvim
├── lua
│   ├── config
│   │   ├── defaults.lua
│   │   ├── keymaps.lua
│   │   └── plugins.lua
│   ├── plugins
│   │   ├── editor.lua
│   │   ├── lsp.lua
│   │   ├── tools.lua
│   │   └── ui.lua
│   └── user
│       ├── user1.lua
│       ├── user2.lua
│       └── **.lua
├── snippets
│   └── *.snippets
└── init.lua
```

我们有四个插件文件，分别是`editor.lua`、`lsp.lua`、`tools.lua`、`ui.lua`，分别是编辑类、lsp和补全、工具类、界面类

