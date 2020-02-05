.global _start /* 全局标号 */
.global _bss_start  /* BSS段起始 */
_bss_start:
    .word __bss_start
.global _bss_end    /* BSS段结束 */
_bss_end:
    .word __bss_end

/*
 * 描述：_start函数，程序从此函数开始执行，此函数主要功能是设置C运行环境。
 *
*/
_start:
    /* 进入SVC模式 */
    MRS R0, CPSR        /* 读取CPSR到R0 */
    BIC R0, R0, #0x1F   /* 将CPSR的M[4:0]清零 */
    ORR R0, R0, #0x13   /* CRSR的M[4:0]=0x13，表示使用SVC模式 */
    MSR CPSR, R0        /* 将R0写入CPSR */

    /* 清除BSS段 */
    LDR R0, =_bss_start
    LDR R1, =_bss_end
    MOV R2, #0
bss_loop:
    STMIA R0!, {R2}     /* 将寄存器R2的值存到R0的地址上；IA:先传后加;!:最后的地址写到R0中 */
    CMP R0, R1          /* 比较R0和R1值 */
    BLE bss_loop        /* 如果R1地址小于R1，继续 */

    /* 设置SP指针 */
    LDR SP, =0x80200000 /* 设置栈指针 */

    /* 跳转到主函数 */
    B main              /* 跳转到main函数 */

