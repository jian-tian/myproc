#include "config.h"
#include "platform_t.h"

.equ WTCON, 0x53000000
.equ INTMASK, 0x4a000008
.equ INTSUBMASK, 0x4a00001c

.section .text
.code 32 
.extern lmosemhal_start
.extern char __begin_bss
.extern char __end_bss
.global _start
.global lmde

.align 4
    b reset                                                                       
    ldr pc, = _undefined_struction
    ldr pc, = _software_struction
    ldr pc, = _prefetch_abort
    ldr pc, = _data_abort
    ldr pc, = _not_used
    ldr pc, = _irq
    ldr pc, = _fiq

reset:
_start:
    bic r0,r0,#0x1f
    orr	r0,r0,#0xd3
    msr	cpsr,r0

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
    
clear_bss:
    ldr	r0, tstbb/* find start of bss segment        */
    ldr	r1, tstbe/* stop here                        */
    ldr	r2, =0x0	    /* clear                            */
clbss_l:
    str r2, [r0]	    /* clear loop...                    */
    add	r0, r0, #4
    cmp	r0, r1
    ble	clbss_l
/*
    ldr r1, =0x50000020
    ldr r0, =0x41 //A
    str r0, [r1]
    bl test
    ldr r1, =0x50000020
    ldr r0, =0x45 //E
    str r0, [r1]
    bl test
    ldr r1, =0x50000020
    ldr r0, =0x46 //F
    str r0, [r1]
    //mov r0, pc
    //str r0, [r3]
*/
    ldr r0,=0
    ldr r1,=0
    ldr r2,=0
    ldr r3,=0
    ldr r4,=0
    ldr r5,=0
    ldr r6,=0
    ldr r7,=0
    ldr r8,=0
    ldr r9,=0
    ldr r10,=0
    ldr fp,=0
    ldr ip,=0
    
    bl test

    ldr r0, tstw
    bl lmosemhal_start

lmde:
    ldr r3, =0x50000020
    ldr r0, =0x47
    str r0, [r3]
    b .

.align 4                                                                          
   
 _undefined_struction:
     b lmde
 _software_struction:
     b lmde
 _prefetch_abort:
     b lmde
 _data_abort:
     b lmde
 _not_used:
     b lmde 
 _irq:
     b lmde 
 _fiq:
     b lmde 

test:
    push {r4,lr}
    nop
    ldr r1, [pc,#20]
    ldr r2, [pc,#20]
    bl test1
    nop
    pop {r4, lr}
    bx lr

test1:
    push {r4,lr}
    nop
    ldr r1, [pc,#20]
    bl test2
    ldr r2, [pc,#20]
    nop
    pop {r4, lr}
    bx lr

test2:
    push {r4,lr}
    nop
    ldr r1, [pc,#20]
    bl test3
    ldr r2, [pc,#20]
    nop
    pop {r4, lr}
    bx lr

test3:
    push {r4,lr}
    nop
    ldr r1, [pc,#20]
    ldr r2, [pc,#20]
    nop
    pop {r4, lr}
    bx lr


.global tstw
.global tstbb
.global tstbe

tstw: .word __end_lmosem_hal_vector
tstbb: .word __begin_bss
tstbe: .word __end_bss
