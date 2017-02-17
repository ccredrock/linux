#计算机系统漫游
##C程序生成
* hello.c ~ hello.i: 预处理 gcc -E hello.c -o hello.i
* hello.i ~ hello.s: 编译器 gcc -S hello.i -o hello.s
* hello.s ~ hello.o: 汇编器 gcc -c hello.s -o hello.o
* hello.o ~ hello:   链接器 gcc hello.o -o hello

##系统硬件组成
> CPU ~ _系统总线_ ~ I/O桥 ~ _存储器总线_ ~ 主存储器
>                   |
>                  I/O总线
>                   |
> ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
>    |           |            |         |
> USB控制 ~ 图形适配器 ~ 磁盘控制器 ~ 扩展槽

