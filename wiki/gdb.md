# GDB使用入门

## 基础命令
1. 编译：`gcc -g file.c -o file`
2. 进入调试：`gdb file`
3. 运行代码：`r/run`
4. 退出gdb：`quit`
5. 断点：`b/break`
    - 打断点
        1. function：`b functionname`
        2. line：`b linenumber`
    - 查看断点信息：`info b`
    - 继续执行：`n`
    - 打印信息：`p variable`
6. 步入：`s/step`

## 小技巧
1. shell：`shell command`
2. 日志：`set logging on`
3. watchpoint
    - 设置：`watch *address` / `watch variable`
    - 查看：`info watchpoints`
4. 调试正在运行的代码：`gdb -p pid`
