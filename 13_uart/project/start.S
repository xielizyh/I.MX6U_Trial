.global _start  /*!< 全局标号 */

/**
 * @brief _start函数，创建中断向量表
 * @note  当中断产生时，ARM内部硬件机制将强制把PC指针定位到“中断向量表”处，
 *        并根据中断源取出对应的中断向量执行中断服务程序
 */
_start:
    LDR PC, =Reset_Handler      /*!< 复位中断 */
    LDR PC, =Undefined_Handler  /*!< 未定义中断 */
    LDR PC, =SVC_Handler        /*!< SVC中断 */
    LDR PC, =PrefAbort_Handler  /*!< 预取终止中断 */
    LDR PC, =DataAbort_Handler  /*!< 数据终止中断 */
    LDR PC, =NotUsed_Handler    /*!< 未使用中断 */
    LDR PC, =IRQ_Handler        /*!< IRQ中断 */
    LDR PC, =FIQ_Handler        /*!< FIQ中断 */

/**
 * @brief 复位中断
 */
Reset_Handler:
    CPSID I                     /*!< 关闭全局中断 */

    /* 关闭I，DC Cache和MMU */
    MRC P15, 0, R0, C1, C0, 0   /*!< 读取CP15寄存器到R0中 */
    BIC R0, R0, #(1 << 12)      /*!< 关闭I Cache */
    BIC R0, R0, #(1 << 2)       /*!< 关闭D Cache */
    BIC R0, R0, #(1 << 1)       /*!< 关闭对齐检查 */
    BIC R0, R0, #(1 << 11)      /*!< 关闭分支预测 */
    BIC R0, R0, #(1 << 12)      /*!< 关闭MMU */
    MCR P15, 0, R0, C1, C0, 0   /*!< 将R0写入到CP15寄存器中 */

#if 0
    /* 设置中断向量表偏移 */
    LDR R0, =0x87800000
    DSB
    ISB
    MCR P15, 0, R0, C12, C0, 0
    DSB
    ISB
#endif

    /* 设置各个模式下的栈指针 */
    /* 进入IRQ模式 */
    MRS R0, CPSR                /* 读取CPSR到R0 */
    BIC R0, R0, #0x1F           /* 将CPSR的M[4:0]清零 */
    ORR R0, R0, #0x12           /* CRSR的M[4:0]=0x12，表示使用IRQ模式 */
    MSR CPSR, R0                /* 将R0写入CPSR */
    LDR SP, =0x80600000         /* 设置栈指针 */

    /* 进入SYS模式 */
    MRS R0, CPSR                /* 读取CPSR到R0 */
    BIC R0, R0, #0x1F           /* 将CPSR的M[4:0]清零 */
    ORR R0, R0, #0x1F           /* CRSR的M[4:0]=0x1F，表示使用SYS模式 */
    MSR CPSR, R0                /* 将R0写入CPSR */
    LDR SP, =0x80400000         /* 设置栈指针 */

    /* 进入SVC模式 */
    MRS R0, CPSR                /* 读取CPSR到R0 */
    BIC R0, R0, #0x1F           /* 将CPSR的M[4:0]清零 */
    ORR R0, R0, #0x13           /* CRSR的M[4:0]=0x13，表示使用SVC模式 */
    MSR CPSR, R0                /* 将R0写入CPSR */
    LDR SP, =0x80200000         /* 设置栈指针 */

    CPSIE I                     /*!< 关闭全局中断 */

    B main                      /*!< 跳转到main函数 */

/**
 * @brief 未定义中断
 */
Undefined_Handler:
    LDR R0, =Undefined_Handler
    BX R0

/**
 * @brief SVC中断
 */
SVC_Handler:
    LDR R0, =SVC_Handler
    BX R0

/**
 * @brief 预取终止中断
 */
PrefAbort_Handler:
    LDR R0, =PrefAbort_Handler
    BX R0  

/**
 * @brief 数据终止中断
 */
DataAbort_Handler:
    LDR R0, =DataAbort_Handler
    BX R0  

/**
 * @brief 未使用中断
 */
NotUsed_Handler:
    LDR R0, =NotUsed_Handler
    BX R0   

/**
 * @brief IRQ中断
 */
IRQ_Handler:    
    PUSH {LR}           /*!< 保存LR地址 */
    PUSH {R0-R3, R12}   /*!< 保存R0-R3，R12寄存器 */

    MRS R0, SPSR        /*!< 读取SPSR寄存器 */
    PUSH {R0}           /*!< 保存SPSR寄存器 */

    MRC P15, 4, R1, C15, C0, 0      /*!< 读取CP15寄存器的C0到R0中，即获取GIC基地址 */
    ADD R1, R1, #0x2000             /*!< GIC基地址+0x2000得到CPU端口寄存器起始地址 */
    LDR R0, [R1, #0xC]              /*!< 得到GIC_IAR寄存器值，GICC_IAR保存当前发生中断的中断号 */

    PUSH {R0, R1}       /*!< 保存R0和R1 */

    CPS #0x13           /*!< 进入SVC模式，允许其他中断再次进去 */

    PUSH {LR}           /*!< 保存SVC模式的LR寄存器 */
    LDR R2, =system_irqhandler  /*!< 加载C语言中断处理函数到R2寄存器 */
    BLX R2              /*!< 运行C语言中断处理函数，带一个参数(R0存的是中断ID号) */

    POP {LR}            /*!< 执行C语言中断处理函数，LR出栈 */
    CPS #0x12           /*!< 进入IRQ模式 */
    POP {R0, R1}
    STR R0, [R1, $0x10] /*!< 中断执行完成，写EOIR */

    POP {R0}
    MSR spsr_cxsf, R0   /*!< 恢复SPSR */

    POP {R0-R3, R12}   /*!< R0-R3,R12出栈 */
    POP {LR}            /*!< LR出栈 */
    SUBS PC, LR, #4     /*!< 将LR-4赋值给PC */

/**
 * @brief FRQ中断
 */
FIQ_Handler:
    LDR R0, =FIQ_Handler
    BX R0