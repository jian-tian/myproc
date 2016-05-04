/*************************
 * krlthread.c 2016.04.12
 * **********************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void context_t_init(context_t * initp)
{
    initp->ctx_usrsp = 0;
    initp->ctx_svcsp = 0;
    initp->ctx_cpsr = 0;
    initp->ctx_lr = 0;
}

uint_t krlretn_thread_id(thread_t * tdp)
{
    return (uint_t)tdp;
}

void thread_t_init(thread_t * initp)
{
    hal_spinlock_init(&initp->td_lock);
    list_init(&initp->td_list);
    initp->td_flgs = 0;
    initp->td_stus = TDSTUS_NEW;
    initp->td_cpuid = hal_retn_cpuid();
    initp->td_id = krlretn_thread_id(initp);
    initp->td_tick = 0;
    initp->td_privilege = PRILG_USR;
    initp->td_priority = PRITY_MIN;
    initp->td_runmode = 0;
    initp->td_krlstktop = NULL;
    initp->td_krlstkstart = NULL;
    initp->td_usrstktop = NULL;
    initp->td_usrstkstart = NULL;

    initp->td_mmdsc = NULL;
    initp->td_resdsc = NULL;
    initp->td_privtep = NULL;
    initp->td_extdatap = NULL;
    context_t_init(&initp->td_context);
    for(uint_t hand = 0; hand < TD_HAND_MAX; hand++)
    {
	initp->td_handtbl[hand] = NULL;
    }

    return;
}

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

thread_t * krlnew_thread_dsc()
{
    thread_t * rettdp = (thread_t *)(krlnew((size_t)(sizeof(thread_t))));
    if (!rettdp)
    {
	printfk("rettdp alloc failed\n\r");
	return NULL;
    }
    thread_t_init(rettdp);
    return rettdp;
}

thread_t * krlnew_thread_core(void * filerun, uint_t flg, uint_t prilg, uint_t prity, size_t usrstksz, size_t krlstksz)
{
    thread_t * ret_td = NULL;
    bool_t  acs = FALSE;
    adr_t   usrstkadr = NULL;
    adr_t   krlstkadr = NULL;

    usrstkadr = krlnew(usrstksz);
    if(!usrstkadr)
    {
	printfk("alloc for usrstk failed\n\r");
	return NULL;
    }

    krlstkadr = krlnew(krlstksz);
    if(!krlstksz)
    {
	printfk("alloc for krlstk failed\n\r");
	if(krldelete(usrstkadr, usrstksz) == NULL)
	{
	    printfk("delete usrstk failed\n\r");
	}
	return NULL;
    }

    ret_td = krlnew_thread_dsc();
    if(!ret_td)
    {
	printfk("krlnew thread dsc failed\n\r");
	if(krldelete(usrstkadr, usrstksz) == NULL)
	{
	    printfk("delete usrstk failed\n\r");
	}
	if(krldelete(krlstkadr, krlstksz) == NULL)
	{
	    printfk("delete usrstk failed\n\r");
	}
	return NULL;
    }

    ret_td->td_privilege = prilg;
    ret_td->td_priority = prity;
    ret_td->td_krlstktop = krlstkadr + (adr_t)(krlstksz - 1);
    ret_td->td_krlstkstart = krlstkadr;
    ret_td->td_usrstktop = usrstkadr + (adr_t)(usrstksz - 1);
    ret_td->td_usrstkstart = usrstkadr;

    krlthreadkrlsatck_init(ret_td, filerun, DAFT_CPSR, DAFT_SPSR);

    krlschdclass_add_thread(ret_td);

    return ret_td;
}

void krlthd_inc_tick(thread_t * thdp)
{
    cpuflg_t cpufg;
    hal_spinlock_saveflg_cli(&thdp->td_list, &cpufg);
    thdp->td_tick++;
    if(thdp->td_tick > TDRUN_TICK)
    {
	thdp->td_tick = 0;
	krlsched_set_schedflgs();
    }
    hal_spinunlock_restflg_sti(&thdp->td_lock, &cpufg);
    return;
}

void krlsched_set_schedflgs(void)
{
    cpuflg_t cpufg;
    uint_t cpuid = hal_retn_cpuid();
    /*获取当前CPU的schdata_t结构指针*/
    schdata_t * schdap = &osschedcls.scls_schda[cpuid];
    hal_spinlock_saveflg_cli(&schdap->sda_lock, &cpufg);
    schdap->sda_schdflgs = NEED_SCHED_FLGS;
    hal_spinunlock_restflg_sti(&schdap->sda_lock, &cpufg);
    return;
}

/*获取当前运行的进程*/
thread_t * krlsched_retn_currthread()
{
    uint_t cpuid = hal_retn_cpuid();
    schdata_t * schdap = &osschedcls.scls_schda[cpuid];
    if(schdap->sda_currtd == NULL)
    {
	hal_sysdie("schdap->sda_currtd NULL\n\r");
    }
    return schdap->sda_currtd;
}
