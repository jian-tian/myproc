#include "config.h"
#include "platform_t.h"

.equ WTCON, 0x53000000
.equ INTMASK, 0x4a000008
.equ INTSUBMASK, 0x4a00001c

.section .head.text
.code 32
//.extern lmosemhal_start
.extern hal_undefins_distr 
.global _start
.global lmde

.align 4

_start:
    b reset
    ldr pc, = _undefined_struction
    ldr pc, = _software_struction
    ldr pc, = _prefetch_abort
    ldr pc, = _data_abort
    ldr pc, = _not_used
    ldr pc, = _irq
    ldr pc, = _fiq

reset:
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
    ldr sp, =INIT_HEAD_STACK_ADDR
    nop
    nop
    //bl lmosemhal_start
    //ldr pc, = _undefined_struction
    bl  hal_undefins_distr

lmde:
    b .

.align 4

_undefined_struction:
    b .
_software_struction:
    b .
_prefetch_abort:
    b .
_data_abort:
    b .
_not_used:
    b .
_irq:
    b .
_fiq:
    b .
.global tstw

tstw: .word __end_lmosem_hal_vector
