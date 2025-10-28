# linux笔记
> linux使用过程中的一些小笔记

## 系统

### arch live修系统
```shell
mount -t btrfs -o subvol=/@,compress=zstd /dev/nvmexn1p1 /mnt # 挂载 / 目录
mkdir /mnt/home # 创建 /home 目录
mount -t btrfs -o subvol=/@home,compress=zstd /dev/nvmexn1p1 /mnt/home # 挂载 /home 目录
mkdir -p /mnt/boot # 创建 /boot 目录
mount /dev/nvmexn1p2 /mnt/boot # 挂载 /boot 目录
swapon /dev/nvmexn1p3 # 挂载交换分区
arch-chroot /mnt
```

### 初始化`$HOME`目录
`xdg-user-dirs-update`创建：`Desktop`,`Documents`,`Downloads`,`Music`,`Pictures`,`Videos`目录

### 免密登录
创建文件`/etc/systemd/system/getty@tty1.service.d/autologin.conf`，填写下面内容：
```shell
[Service]
ExecStart=
ExecStart=-/sbin/agetty -o '-p -f -- \\u' --noclear --autologin KicamonIce %I $TERM
```


### 自动启动
1. 启动startx：在bashrc或者zshrc中添加
```shell
[ $(tty) = "/dev/tty1" ] && cd ~ && startx
```

2. 启动图形界面（以dwm为例）：在`~/.xinitrc`末尾添加`exec dwm`

### 持久化互换`ESC`和`Capslock`
创建文件`sudo nano /etc/X11/xorg.conf.d/00-keyboard.conf`，填写下面内容：
```shell
Section "InputClass"
    Identifier "system-keyboard"
    MatchIsKeyboard "on"
    Option "XkbOptions" "caps:swapescape"
EndSection
```

### 关机时间长
1. 更改等待时间
```shell
sudo nvim /etc/systemd/system.conf
```
将`DefaultTimeoutStopSec`这一项取消注释，把时间改成30s

2. 执行
执行`sudo systemctl daemon-reload`

### 同步时间
`sudo timedatectl set-ntp true`


### 网络
检测网络是否连接
```shell
nmcli -t -f NAME,DEVICE,STATE connection show --active
```

输出（有网络）
```shell
网络名:网卡名:activated
```

## 软件设置
### 设置默认文件管理器
```shell
xdg-mime default thunar.desktop inode/directory
```

### 数位板驱动
1. 安装opentabletdriver
2. 启动
```shell
otd-daemon &
otd-gui
```

### 游戏
1. 内核选择：[linux-zen](https://github.com/zen-kernel/zen-kernel)
    - 一些内核黑客合作的结果，是适合日常使用的优秀内核
    - 以吞吐量和功耗为代价来换取性能
    - 相对 linux 内核加入了 Fsync 功能，在一些采用 .Net 的 wine 游戏中会有 明显的性能提升
2. 性能监控：[mangohud](https://github.com/flightlessmango/MangoHud)
    - 常规启动方式`mangohud 游戏`
    - steam：在 Steam 库中右键游戏封面 > 点击 `属性...` > 侧边栏 `通用` > 在 `启动选项` 中添加 `MANGOHUD=1 %command%`

### Podman
1. 拉取镜像：到[docker hub](https://hub.docker.com/)官网上拉取即可，如**debian**：`podman pull docker.io/debian`
2. 查看镜像：`docker images`命令可以列举本地的镜像
3. 创建并运行debian容器：`podman run -it --name debian_dev debian bash`(debian_dev为容器名，可以任意取名)
4. 列举本地容器：
    1. `podman ps`：查看正在运行的容器
    2. `podman ps -a`：查看所有的容器
5. 运行本地容器：
    1. `podman start debian_dev`
    2. `podman attach debian_dev`
