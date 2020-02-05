.global _start /* 全局标号 */
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

    /* 设置SP指针 */
    LDR SP, =0x80200000 /* 设置栈指针 */

    /* 跳转到主函数 */
    B main              /* 跳转到main函数 */

