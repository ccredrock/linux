#程序的机器级表示

##寄存器(IA32)
* 程序计数器 eip
* 8个存储32位值的寄存器 eax ecx edx ebx esi edi esp ebp
* 一组单个位的条件码寄存器 CF ZF SF OF
* 一组浮点寄存器

##操作(IA32)
* mov cmp test set jmp cmov
* pop push
* leal inc dec neg not add sub imul xor or and sal shl sar shr
* imull mull cltd idivl divl
* call leave ret

##寄存器(x86-64)
* 程序计数器 rip
* 16个存储64位值的寄存器 rax rbx rcx rdx rsi rdi rbp rsp r8-17
* 一组单个位的条件码寄存器 CF ZF SF OF
* 一组浮点寄存器

##操作(x86-64)
* movs movz cmp test set jmp
* pop push
* leal inc dec neg not add sub imul xor or and sal shl sar shr
* imull mull cltd idivl divl
* call leave ret

##优化
* 乘法 -> 成加法&&移位
* 2幂除法 -> 移位
* switch -> 跳转表

