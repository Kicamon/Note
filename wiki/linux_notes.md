# linux笔记
> linux使用过程中的一些小笔记

## 网络
检测网络是否连接
```shell
nmcli -t -f NAME,DEVICE,STATE connection show --active
```

输出（有网络）
```shell
网络名:网卡名:activated
```
