/*************************
 * krlthread.c 2016.04.12
 * **********************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void krlthreadkrlsatck_init(thread_t * thdp, void * runadr, reg_t cpsr, reg_t spsr)
{
    thdp->td_krlstktop &= (~0xF);
    thdp->td_usrstktop &= (~0xF);
    /*栈顶存放寄存器值*/
    armregs_t * arp = (armregs_t *)(thdp->td_krlstktop - sizeof(armregs_t));
    arp->r0 = 0;
    arp->r1 = 0;
    arp->r2 = 0;
    arp->r3 = 0;
    arp->r4 = 0;
    arp->r5 = 0;
    arp->r6 = 0;
    arp->r7 = 0;
    arp->r8 = 0;
    arp->r9 = 0;
    arp->r10 = 0;
    arp->r11 = 0;
    arp->r12 = 0;
    arp->r13 = (reg_t)(thdp->td_usrstktop);
    arp->r14 = (reg_t)(runadr);

    /*用户进程栈顶*/
    thdp->td_context.ctx_usrsp = (reg_t)(thdp->td_usrstktop);
    /*svcsp 为arp地址*/
    thdp->td_context.ctx_svcsp = (reg_t)(arp);
    /*svcspsr 为spsr*/
    thdp->td_context.ctx_svcspsr = spsr;
    /*cpsr 为cpsr*/
    thdp->td_context.ctx_cpsr = cpsr;
    /*lr 为runadr*/
    thdp->td_context.ctx_lr = (reg_t)runadr;
    return;
}
