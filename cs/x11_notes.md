# X11笔记

## 常用函数
| 函数                        | 描述                                               |
|-----------------------------|----------------------------------------------------|
| `Display *XOpenDisplay`     | 打开与X11服务器的连接                              |
| `int XDefaultScreen`        | 返回屏幕编号                                       |
| `Window XDefaultRootWindow` | 返回默认屏幕root window id(unsigned long类型)      |
| `Visual *DefaultVisual`     | 获取屏幕颜色信息的相关数据                         |
| `int DefaultDepth`          | 获取屏幕的默认颜色深度                             |
| `Colormap DefaultColormap`  | 获取屏幕默认visual的颜色映射                       |
| `Window RootWindow`         | 返回指定屏幕的root window id                       |
| `Screen *ScreenOfDisplay`   | 返回指定屏幕的相关的属性                           |
| `XUniqueContext`            | 唯一上下文标识符，防止在多线程或者多模块中发生冲突 |
| `<++>`                      | <++>                                               |
| `<++>`                      | <++>                                               |
| `<++>`                      | <++>                                               |
| `<++>`                      | <++>                                               |
