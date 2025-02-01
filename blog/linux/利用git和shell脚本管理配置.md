> 作为一名linux用户，我对系统本身进行了一定的定制，包括主题、软件等。如果拥有多个电脑，每次配置文件的更改在电脑之间的同步都很麻烦。那么，可以利用shell脚本和git来对配置文件进行管理。

## shell脚本
### update脚本
#### 确定需要同步的配置，比如我的需求：
1. 系统：我是用的是X11，需要同步一些x的配置
    1. .xinitrc：`~/.xinitrc`
    2. .Xresources：`~/.Xresources`
2. 主题
    1. gtk主题：`~/.config/gtk-*`
    2. qt主题
        1. Kvantum：`~/.config/Kvantum`
        2. qt6ct：`~/.config/qt6ct`
3. 程序：这里指像`yazi`, `kitty`等程序的配置，都在`~/.config`下，不一一列出，根据自己的需要来选择即可
4. 其他：有些在`~/.local/share`下的文件也需要备份，比如fcitx5的符号映射，gtk，字体以及图标等

#### 根据上述需求，可以在shell脚本中添加一个函数，名为update，内容如下
```shell
update() {
    cp -rp ~/.config/Kvantum \
        ~/.config/dunst \
        ~/.config/fcitx5 \
        ~/.config/fish \
        ~/.config/fontconfig \
        ~/.config/gtk-* \
        ~/.config/i3 \
        ~/.config/kitty \
        ~/.config/neofetch \
        ~/.config/picom \
        ~/.config/polybar \
        ~/.config/qt6ct \
        ~/.config/ranger \
        ~/.config/rofi \
        ~/.config/starship.toml \
        ~/.config/tmux \
        ~/.config/vim \
        ~/.config/yazi \
        ~/.config/zsh \
        ./config
    cp ~/.xinitrc \
        ~/.Xresources \
        ./user
    cp -rp ~/.local/share/fcitx5 \
        ~/.local/share/fonts \
        ~/.local/share/themes \
        ./local
}
```

- 该脚本将`~/.config`中的配置复制到了`config`文件夹中，将x的配置复制到`user`文件夹中，将`~/.local/share`的配置复制到了`.local`中

- 调用这个函数，可以将配置文件复制到当前文件夹中，进行统一管理

- 有些临时文件会存在于我们需要备份的配置文件的目录中，我们可以写一些函数将其删除，如：
```shell
remove_file() {
    local dir=$1
    for file in ${dir}/.; do
        if [[ -f ${file} && ${file} == "./local/fonts/"*".uuid" ]]; then
            rm ${file}
        elif [[ -d ${file} ]]; then
            remove_file ${file}
        fi
    done
}

remove_dir() {
    rm -rf ./local/fcitx5/pinyin ./local/icons/hicolor ./config/tmux/plugins
}
```

- 随后调用函数：
```shell
update
remove_file ./local
remove_dir
```

最后在备份完成后，输出一句话即可，提醒我们备份完成。

上述脚本详见：[备份脚本](https://github.com/Kicamon/dotfile/blob/main/update.sh)

### git同步
> 这部分内容需要学习git的使用，如果不会git需要先去学习一下，教学视频：[再也不丢文件的方法～ Git从入门到精通](https://b23.tv/ahaNEB9)

在gitee或者github之类的代码托管网站上创建dotfile仓库与文件夹同步即可，如我的dotfile仓库：[dotfile](https://github.com/Kicamon/dotfile)
