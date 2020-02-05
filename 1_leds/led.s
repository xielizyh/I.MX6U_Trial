.global _start  @ 全局标号

_start:
ldr r0, =0x020C4068
ldr r1, =0xFFFFFFFF
str r1, [r0]

ldr r0, =0x020C406C
str r1, [r0]

ldr r0, =0x020C4070
str r1, [r0]

ldr r0, =0x020C4074
str r1, [r0]

ldr r0, =0x020C4078
str r1, [r0]

ldr r0, =0x020C407C
str r1, [r0]

ldr r0, =0x020C4080
str r1, [r0]

ldr r0, =0x020E0068
ldr r1, =0x5
str r1, [r0]

ldr r0, =0x020E02F4
ldr r1, =0x10B0
str r1, [r0]

ldr r0, =0x0209C004
ldr r1, =0x00000008
str r1, [r0]

loop:
    bl led_on
    bl delay
    bl led_off
    bl delay
    b loop

led_on:
    ldr r0, =0x0209C000
    ldr r1, =0x0
    str r1, [r0]
    mov pc, lr

led_off:
    ldr r0, =0x0209C000
    ldr r1, =0x8
    str r1, [r0]
    mov pc, lr

delay:
    ldr r0, =0xFFFFF @延时约500ms
delay_loop:
    sub r0, r0, #1 @减1
    mov r2, #0
    cmp r0, r2 @减到0
    bne delay_loop @r0!=0,则继续循环
    mov pc, lr
