#处理器体系结构

##硬件控制语言HCL
* 组合电路:ALU
* 时序电路:时钟寄存器 随机访问存储器

##SEQ
* 取指 -> icode:ifun(操作) rA:rB(哪个寄存器) valC(常数) valP(下一指令)
* 译码 -> valA(根据rA读取数值) valB
* 执行 -> valE
* 访存 -> 写入存储器或valM(读取存储器)
* 写回 -> 写回寄存器
* 更新 -> PC

##PIPE
* 流水线寄存器
* 分支预测
* 流水线冒险:气泡暂停 转发
* 异常