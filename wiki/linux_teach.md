# Linux教程

[toc]

## 1 基础命令

| 命令             | 参数         | 作用                                                                 |
|------------------|--------------|----------------------------------------------------------------------|
| `ls`             |              | 列出当前目录下的文件和文件夹                                         |
| `ls`             | `-l`         | 列出当前目录下的文件和文件夹（并显示具体信息）                       |
| `ls`             | `-a`         | 列出当前目录下的文件和文件夹（包括隐藏文件和文件夹）                 |
| `ls`             | `-al`, `-la` | 列出当前目录下的文件和文件夹（包括隐藏文件和文件夹，并显示具体信息） |
| `cd`             |              | 跳转到目标目录，`.`表示当前目录，`..`表示上一目录                    |
| `cd`             | `-`          | 跳转到前一个目录                                                     |
| `clear`, `<c-l>` |              | 清屏                                                                 |
| `pwd`            |              | 显示当前目录位置                                                     |
| `cp`             |              | 复制文件                                                             |
| `cp`             | `-r`         | 复制文件夹                                                           |
| `cp`             | `-f`         | 复制文件且没有提示                                                   |
| `mv`             |              | 移动文件                                                             |
| `rm`             |              | 删除文件                                                             |
| `touch`          |              | 创建文件                                                             |
| `cat`            |              | 输出文件内容                                                         |
| `cat`            | `-n`         | 输出文件内容并显示行号                                               |
| `shmod`          |              | 设置文件权限                                                         |
| `head`           |              | 显示文件开头几行                                                     |
| `head`           | `--lines=`   | 显示文件开头几行，且指定行数                                         |
| `tail`           |              | 显示文件结尾几行                                                     |
| `head`           | `--lines=`   | 显示文件结尾几行，且指定行数                                         |

## 2 用户管理

### 2.1 创建新用户
> 如果当前只有一个`root`用户，那么最好创建一个非`root`用户，具体方式如下

1. 安装`sudo`命令：`apt install sudo`
2. 查看`/etc/sudoers`文件的内容
3. 检查`## User privilege specification`部分的内容，如：
  ```shell
  ##
  ## User privilege specification
  ##
  root ALL=(ALL:ALL) ALL

  ## Uncomment to allow members of group wheel to execute any command
  %wheel ALL=(ALL:ALL) ALL
  ```
  这里存在两个用户组，分别是`root`和`wheel`，不同的发行版第二个用户组可能会有不同，如果被注释了取消注释皆可

4. 使用命令`useradd -m -G wheel -s /bin/bash {myusername}`创建新用户
5. 使用`passwd {myusername}`设置用户密码

### 2.2 其他用户操作
| 操作                                 | 作用               |
|--------------------------------------|--------------------|
| `userdel {username}`                 | 删除用户           |
| `groupadd {groupname}`               | 添加用户组         |
| `usermod -aG {groupname} {username}` | 将用户添加到用户组 |

## 3 vim编辑器的使用和基本配置

### 3.1 vim基本使用
| 操作                     | 作用                             |
|--------------------------|----------------------------------|
| `i`                      | 进入插入模式                     |
| `<ESC>`                  | 进入普通模式                     |
| `h`, `j`, `k`, `l`       | 光标移动，分别对应左，下，右，上 |
| `<c-u>`, `<c-d>`         | 光标移动，分别对应上，下半页     |
| `0`                      | 跳跃到行首                       |
| `^`                      | 跳跃到第一个字符                 |
| `$`                      | 跳跃到行尾                       |
| `gg`                     | 跳跃到文件开头                   |
| `G`                      | 跳跃到文件结尾                   |
| `:{number}`, `{number}G` | 跳跃到第{number}行               |
| `v`                      | 进入选中模式                     |
| `V`                      | 进入行选中模式                   |
| `<c-v>`                  | 进入块选中模式                   |
| `y`                      | 复制选中的内容或者等待motion     |
| `yy`                     | 复制本行                         |
| `Y`                      | 复制光标到行尾的内容             |
| `p`                      | 将复制的内容在光标后粘贴         |
| `P`                      | 将复制的内容在光标前粘贴         |
| `u`                      | 撤销                             |
| `<c-r>`                  | 反撤销                           |
| `/{string}`              | 查找内容                         |
| `n`                      | 下一个匹配的查找内容             |
| `N`                      | 上一个匹配的查找内容             |
| `{number}{motion}`       | 执行{number}次行为               |
| `:w`, `:w!`              | 保存和强制保存                   |
| `:q`, `:q!`              | 退出和强制退出                   |
| `:wq`                    | 保存退出                         |
| `:noh`                   | 取消搜索高亮                     |


### 3.2 vim基本配置
| 配置内容                                                                      | 作用                         |
|-------------------------------------------------------------------------------|------------------------------|
| `syntax on`                                                                   | 开启关键词高亮               |
| `set number`                                                                  | 开启行号                     |
| `set relativenumber`                                                          | 开启相对行号                 |
| `set cursorline`                                                              | 高亮本行                     |
| `set lastatus=3`                                                              | 开启状态栏                   |
| `set tabstop=`                                                                | 设置tab大小                  |
| `set shiftwidth=`                                                             | 设置indent大小               |
| `set softtabstop=`                                                            | 设置tab大小                  |
| `set autoindent`                                                              | 设置自动缩进                 |
| `set smartindent`                                                             | 更智能的自动缩进             |
| `set list`                                                                    | 显示list字符                 |
| `set listchars=`                                                              | 设置list字符的内容           |
| `set wildmenu`                                                                | cmdline补全                  |
| `set ignorecase`                                                              | 搜索时忽略大小写             |
| `set smartcase`                                                               | 搜索输入大写时不会忽略大小写 |
| `set ttimeoutline=`, `set notimeout`                                          | 更快的响应时间               |
| `set conceallevel=0`                                                          | 取消特殊字符隐藏             |
| `let &t_SI.="\e[5 q"`, `let &t_SR.="\e[3 q"`, `let &t_EI.="\e[1 q"`           | 光标变化                     |
| `(nore)map`, `n(nore)map`,`i(nore)map`,`v(nore)map`,`t(nore)map`,`o(nore)map` | 快捷键映射                   |

### 3.3 利用vimscript创建新功能

- 如下是一个快速运行代码的功能：
```vim
nmap <F5> :call Run()<CR>
function! Run()
  echo " compiling..."
  if &filetype == 'c'
    :! gcc "%" -o "%<" && "./%<" && rm -f "./%<"
  elseif &filetype == 'cpp'
    :! g++ "%" -o "%<" -Wall -std=c++20 && "./%<" && rm -f "./%<"
  elseif &filetype == 'python'
    :! python "%"
  end
  redraw!
  echohl WarningMsg | echo " Running finish! :-)"
endfunction
```

## 4 tmux的使用和基本配置

### 4.1 tmux的作用和结构
1. 作用：增强终端的功能，提供多窗口、分屏、挂起等功能
2. 结构：
```
tmux:
├─session 0
│ ├─window 0
│ │ ├─pane 0
│ │ └─pane 1
│ └─window 1
│   ├─pane 0
│   ├─pane 1
│   └─pane 2
├─session 1
└─session 2
```

### 4.2 tmux的基本使用
| 命令/快捷键 | 参数           | 作用                      |
|-------------|----------------|---------------------------|
| `tmux`      |                | 创建新的session           |
| `tmux`      | `attach`       | 进入被挂起的session       |
| `tmux`      | `new -n`       | 创建新的session并为其命名 |
| `tmux`      | `ls`           | 查看所有的session         |
| `prefix`    | `c`            | 创建新的window            |
| `prefix`    | `{num}`        | 切换到第{num}个window     |
| `prefix`    | `n`            | 切换到下一个window        |
| `prefix`    | `p`            | 切换到上一个window        |
| `prefix`    | `&`            | 关闭当前window            |
| `prefix`    | `%`            | 在右侧创建一个pane        |
| `prefix`    | `"`            | 在下侧创建一个pane        |
| `prefix`    | 方向键         | 切换pane                  |
| `prefix`    | 同时按住方向键 | 改变pane的大小            |
| `prefix`    | `q`            | 选择pane                  |
| `prefix`    | `z`            | 最大化/恢复pane           |
| `prefix`    | `x`            | 关闭pane                  |
| `prefix`    | `w`            | 查看所有window            |
| `prefix`    | `d`            | 挂起session               |

### 4.3 tmux的配置
| 配置内容                                              | 作用                     |
|-------------------------------------------------------|--------------------------|
| `unbind c-b`                                          | 取消默认prefix           |
| `set -g prefix C-Space`                               | 设置prefix               |
| `bind -n M-v copy-mode`                               | 设置复制模式的快捷键     |
| `bind -T copy-mode-vi v send-keys -X begin-selection` | 在复制模式中使用vi快捷键 |
| `prefix="#{?client_prefix,⚡,}"`                      | 设置prefix提示符         |


## 5 进阶命令（常用命令，管道和环境变量）

### 5.1 常用命令
| 命令       | 参数  | 作用                    |
|------------|-------|-------------------------|
| `top`      |       | 显示进程信息            |
| `kill pid` |       | 关闭进程号为`pid`的进程 |
| `w`        |       | 显示当前正在登录的用户  |
| `find`     |       | 查找文件                |
| `find`     | -name | 查找特定文件            |
| `wc`       | -l    | 统计文件行数            |
| `wc`       | -w    | 统计文件单词数          |
| `wc`       | -c    | 统计文件字节数          |

### 5.2 管道
> 利用`|`字符可以将前一个命令的输出作为后一个命令的输入，称为管道。利用管道可以灵活地将多个命令链式执行

| 命令                                    | 作用                                     |
|-----------------------------------------|------------------------------------------|
| `echo {something} |  cut -d '=' -f 1,4` | 输出`{something}`用`=`分割后的1和4个数据 |
| `echo {something} |  cut -d '=' -f 1-4` | 输出`{something}`用`=`分割后的1到4个数据 |

### 5.3 环境变量
```shell
env #显示当前用户的变量
export #设置环境变量
```

## 6 写shell脚本

[菜鸟教程](https://www.runoob.com/linux/linux-shell.html)

## 7 ssh基本使用

### 7.1 创建ssh密钥
> 使用命令`ssh-keygen`创建密钥，结束后会在`~/.ssh`目录中多出两个文件：
- `id_rsa`：私钥
- `id_rsa.pub`：公钥

### 7.2 利用ssh登录服务器
| 命令                          | 作用                                                               |
|-------------------------------|--------------------------------------------------------------------|
| `ssh {user}@{hostname}`       | 登录服务器，{user}表示用户名，{hostname}表示服务器的ip地址或者域名 |
| `ssh {user}@{hostname} -p 22` | 登录服务器的22端口                                                 |

### 7.3 快速登录配置
1. 在`~/.ssh/`中创建文件`config`
2. 编辑`config`文件：
```conf
Host servername1
  HostName {hostname}
  User {user}

Host servername2
  HostName {hostname}
  User {user}
```

之后就能通过`ssh servername1`来快速连接相关的服务器

### 7.4 免密登录
> 将公钥中的内容复制到服务器的`~/.ssh/authorized_keys`文件里

### 7.5 scp传输文件
| 命令                               | 作用                                             |
|------------------------------------|--------------------------------------------------|
| `scp {file} {hostname}`            | 将文件{file}复制到{hostname}中                   |
| `scp -r {folder} {hostname}`       | 将文件夹{folder}复制到{hostname}中               |
| `scp {file} {hostname}:/home/user` | 将文件{file}复制到{hostname}的`/home/user`目录中 |

## 8 git的基本命令

### 8.1 初始化设置
| 命令                                            | 作用                 |
|-------------------------------------------------|----------------------|
| `git config --global user.name "{username}"`    | 设置全局的用户名     |
| `git config --global user.email "{email}"`      | 设置全局的邮箱       |
| `git config --global init.defaultBranch 'main'` | 设置默认分支为`main` |

### 8.2 常用命令
| 命令                                                   | 作用                                                       |
|--------------------------------------------------------|------------------------------------------------------------|
| `git init`                                             | 将当前目录设置成git仓库                                    |
| `git add {file}`                                       | 将{file}文件加入缓存区                                     |
| `git add .`                                            | 将所有文件加入暂存区                                       |
| `git commit -m "{something}"`                          | 将缓存区的内容提交，{someting}是备注                       |
| `git status`                                           | 查看仓库状态                                               |
| `git diff {file}`                                      | 查看{file}文件的修改内容                                   |
| `git log`                                              | 查看当前分支的所有版本                                     |
| `git reflog`                                           | 查看HEAD指针移动历史                                       |
| `git reset --hard HEAD~`                               | 回滚到上一版本                                             |
| `git reset --hard HEAD~n`                              | 回滚到上n个版本                                            |
| `git reset --hard commit_id`                           | 回滚到特定的commit                                         |
| `git restore {file}`                                   | 删除{file}文件的修改                                       |
| `git rm --cached {file}`                               | 将{file}从缓存区中删除                                     |
| `git remote add origin git@github.com:{xxxx/xxxx}.git` | 将本地仓库关联到远程仓库                                   |
| `git push -u`                                          | 将本地仓库提交到远程仓库（从第二次开始就不需要加-u参数）   |
| `git pull`                                             | 将远程仓库的默认分支与本地的当前分支合并                   |
| `git clone {positon}`                                  | 将远程仓库克隆到本地                                       |
| `git branch`                                           | 查看所有分支                                               |
| `git branch {branch_name}`                             | 创建一个名为{branch_name}的分支                            |
| `git chekout {branch_name}`                            | 切换到{branch_name}分支                                    |
| `git branch -d {branch_name}`                          | 删除本地的{branch_name}分支                                |
| `git pull origin {branch_name}`                        | 将远程仓库的{branch_name}分支与本地的{branch_name}分支合并 |
| `git stash`                                            | 将当前未提交的修改存入栈中                                 |
| `git stash apply`                                      | 将栈顶元素恢复到改分支，并且不删除栈顶元素                 |
| `git stash pop`                                        | 将栈顶元素恢复到改分支，并且删除栈顶元素                   |
| `git stash drop`                                       | 删除栈顶元素                                               |
| `git stash list`                                       | 查看栈中所有元素                                           |
