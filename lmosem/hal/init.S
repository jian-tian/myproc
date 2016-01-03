#include "config.h"
#include "platform_t.h"

.equ WTCON, 0x53000000
.equ INTMASK, 0x4a000008
.equ INTSUBMASK, 0x4a00001c

.section .head.text
.code 32
.extern lmosemhal_start
.global _start
.global lmde
.align 4

_start:
    @close irq and frq,switch to sve
    msr cpsr, #0xc0|0x13

    @close wd
    ldr r0, =WTCON
    mov r1, #0
    str r1, [r0]

    @mask all interrupt
    ldr r0, =INTMASK
    ldr r1, =0xffffffff
    str r1, [r0]

    @mask all sub_interrupt
    ldr r0, =INTSUBMASK
    ldr r1, =0x7fff
    str r1, [r0]
    ldr r0, tstw
    b .
    ldr sp, =INIT_HEAD_STACK_ADDR
    bl lmosemhal_start

lmde:
    b .

.global tstw

tstw: .word __end_lmosem_hal_vector
