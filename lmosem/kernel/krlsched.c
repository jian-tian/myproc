/*****************************
 * krlsched.c 2016.04.12
 * **************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void thrdlst_t_init(thrdlst_t * initp)
{
    list_init(&initp->tdl_lsth);
    initp->tdl_curruntd = NULL;
    initp->tdl_nr = 0;
}

void schdata_t_init(schdata_t * initp)
{
    hal_spinlock_lock(&initp->sda_lock);
    initp->sda_cpuid = hal_retn_cpuid();
    /*初始化时候不调度*/
    initp->sda_schdflgs = NOTS_SCHED_FLGS;
    initp->sda_premptidx = 0;
    initp->sda_threadnr = 0;
    initp->sda_prityidx = 0;
    initp->sda_cpuidle = NULL;
    initp->sda_currtd = NULL;

    for(uint_t ti=0; ti<PRITY_MAX; ti++)
    {
	thrdlst_t_init(&initp->sda_thdlst[ti]);
    }

    return;
}

void schedclass_t_init(schedclass_t * initp)
{
    hal_spinlock_init(&initp->scls_lock);
    initp->scls_cpunr = CPUCORE_MAX;
    initp->scls_threadnr = 0;
    initp->scls_threadid_inc = 0;

    for(uint_t si=0; si<CPUCORE_MAX; si++)
    {
	schdata_t_init(&initp->scls_schda[si]);
    }

    return;
}

void init_krlsched()
{
    schedclass_t_init(&osschedcls);
    return;
}

void retnfrom_first_sched(thread_t * thrdp)
{
    __asm__ __volatile__(
	"msr spsr, %[svcspsr]\n\r"
	"mov sp, %[svcsp]\n\r"
	"mov lr, %[usrlr]\n\r"
	"ldmia sp, {r0-lr}\n\r"
	"add sp, sp, #60\n\r"
	"movs pc, lr\n\r"
	:
	:[svcsp]"r"(thrdp->td_context.ctx_svcsp),[svcspsr]"r"(thrdp->td_context.ctx_svcspsr), [usrlr]"r"(thrdp->td_context.ctx_lr)
	:"cc","memory"
    );
}

void krlschdclass_add_thread(thread_t * thdp)
{
    uint_t cpuid = hal_retn_cpuid();
    schdata_t * schdap = &osschedcls.scls_schda[cpuid];
    cpuflg_t cpufg;

    hal_spinlock_saveflg_cli(&schdap->sda_lock, &cpufg);
    /*将进程添加入对应优先级的thdlst_t结构的链表中*/
    list_add(&thdp->td_list, &schdap->sda_thdlst[thdp->td_priority].tdl_lsth);
    schdap->sda_thdlst[thdp->td_priority].tdl_nr++;
    schdap->sda_threadnr++;
    hal_spinunlock_restflg_sti(&schdap->sda_lock, &cpufg);
    /*增加全局进程计数*/
    hal_spinlock_saveflg_cli(&osschedcls.scls_lock, &cpufg);
    osschedcls.scls_threadnr++;
    hal_spinunlock_restflg_sti(&osschedcls.scls_lock, &cpufg);
    return;
}

thread_t * krlnew_thread(void * filerun, uint_t flg, uint_t prilg, uint_t prity, size_t usrstksz, size_t krlstksz)
{
    size_t tustksz = 0;
    size_t tkstksz = 0;

    if((flg & 0x1) != 0 || filerun == NULL || usrstksz > DAFT_TDUSRSTKSZ || krlstksz > DAFT_TDKRLSTKSZ)
    {
	printfk("input error\n\r");
	return NULL;
    }
    if((prilg != PRILG_USR && prilg != PRILG_SYS) || prity > PRITY_MAX)
    {
	printfk("input pri error\n\r");
	return NULL;
    }
    if(usrstksz < DAFT_TDUSRSTKSZ)
    {
	tustksz = DAFT_TDUSRSTKSZ;
    }
    if(krlstksz < DAFT_TDKRLSTKSZ)
    {
	tkstksz = DAFT_TDKRLSTKSZ;
    }

    return krlnew_thread_core(filerun, flg, prilg, prity, tustksz, tkstksz);
}

void krlsched_chkneed_pmptsched(void)
{
    cpuflg_t cpufg;
    uint_t schd =0;
    uint_t cpuid = hal_retn_cpuid();

    schdata_t * schdap = &osschedcls.scls_schda[cpuid];
    hal_spinlock_saveflg_cli(&schdap->sda_lock, &cpufg);
    if(schdap->sda_schdflgs == NEED_SCHED_FLGS && schdap->sda_premptidx == PMPT_FLGS)
    {
	schdap->sda_schdflgs = NOTS_SCHED_FLGS;
	schd = 1;
    }
    hal_spinunlock_restflg_sti(&schdap->sda_lock, &cpufg);
    if(1 == schd)
    {
	krlschedul();
    }

    return;
}

thread_t * krlsched_retn_idlethread(void)
{
    uint_t cpuid = hal_retn_cpuid();
    schdata_t * schdap = &osschedcls.scls_schda[cpuid];
    if(schdap->sda_cpuidle == NULL)
    {
	hal_sysdie("schdap->sda_cpuidle NULL\n\t");
    }

    return schdap->sda_cpuidle;
}

thread_t * krlsched_select_thread(void)
{
    thread_t * retthd, * tdtmp;
    cpuflg_t cpufg;
    uint_t cpuid = hal_retn_cpuid();
    schdata_t * schdap = &osschedcls.scls_schda[cpuid];

    hal_spinlock_saveflg_cli(&schdap->sda_lock, &cpufg);
    for(uint_t pity = 0; pity < PRITY_MAX; pity++)
    {
	if(schdap->sda_thdlst[pity].tdl_nr > 0)
	{
	    if(list_is_empty_careful(&(schdap->sda_thdlst[pity].tdl_lsth)) == FALSE)
	    {
		tdtmp = list_entry(schdap->sda_thdlst[pity].tdl_lsth.next, thread_t, td_list);
		list_del(&tdtmp->td_list);
		if(schdap->sda_thdlst[pity].tdl_curruntd != NULL)
		{
		    list_add_tail(&(schdap->sda_thdlst[pity].tdl_curruntd->td_list), 
				    &(schdap->sda_thdlst[pity].tdl_lsth));
		}
		schdap->sda_thdlst[pity].tdl_curruntd = tdtmp;
		retthd = tdtmp;
		goto return_step;
	    }

	    if(schdap->sda_thdlst[pity].tdl_curruntd != NULL)
	    {
		retthd = schdap->sda_thdlst[pity].tdl_curruntd;
		goto return_step;
	    }
	}
    }

    schdap->sda_prityidx = PRITY_MIN;
    retthd = krlsched_retn_idlethread();
return_step:
    hal_spinunlock_restflg_sti(&schdap->sda_lock, &cpufg);
    return retthd;
}

void save_to_new_contex(thread_t * next, thread_t * prev)
{
    cpuflg_t cpufg;
    hal_disableirq_savecpuflg(&cpufg);

    __asm__ __volatile__("stmfd sp!, {r0-r12, lr} \n\t"
			 ::: "memory"
    );

    __asm__ __volatile__(
	"mrs lr, spsr\n\t"
	"str lr, [%[PREV_SPSR]] \n\t"
	"mrs lr, cpsr\n\t"
	"str lr, [%[PREV_CPSR]] \n\t"

	"msr spsr, %[NEXT_SPSR] \n\t"
	"msr cpsr, %[NEXT_CPSR] \n\t"

	"str sp, [%[PREV_SVCSP]] \n\t"
	"ldr sp, [%[NEXT_SVCSP]] \n\t"

	"mov r0, %[NEXT_TD] \n\t"
	"mov r1, %[PREV_TD] \n\t"
	"bl __to_new_contex \n\t"
	:
	:[PREV_TD] "r" (prev), [NEXT_TD] "r" (next), [PREV_SVCSP] "r" (&prev->td_context.ctx_svcsp), [PREV_SPSR] "r" (&prev->td_context.ctx_svcspsr), [PREV_CPSR] "r" (&prev->td_context.ctx_cpsr), [NEXT_SVCSP] "r" (&next->td_context.ctx_svcsp), [NEXT_SPSR] "r" (next->td_context.ctx_svcspsr), [NEXT_CPSR] "r" (next->td_context.ctx_cpsr)
	:"lr", "cc", "memory"
    );

    __asm__ __volatile__(
	"ldmfd sp!, {r0-r12, lr} \n\t"
	:::"memory"
    );

    hal_enableirq_restcpuflg(&cpufg);
    return;
}

void __to_new_contex(thread_t * next, thread_t * prev)
{
    uint_t cpuid = hal_retn_cpuid();
    schdata_t * schdap = &osschedcls.scls_schda[cpuid];
    schdap->sda_currtd = next;
    if(next->td_stus == TDSTUS_NEW)
    {
	next->td_stus = TDSTUS_RUN;
	retnfrom_first_sched(next);
    }
    return;
}

void krlschedul(void)
{
    thread_t * prev = krlsched_retn_currthread();
    thread_t * next = krlsched_select_thread();
    save_to_new_contex(next, prev);
    return;
}

void krlsched_wait(kwlst_t * wlst)
{
    cpuflg_t cpufg, tcufg;
    uint_t cpuid = hal_retn_cpuid();
    schdata_t * schdap = &osschedcls.scls_schda[cpuid];
    /*获取当前进程*/
    thread_t * tdp = krlsched_retn_currthread();
    uint_t pity = tdp->td_priority;
    if(pity > PRITY_MAX || wlst == NULL)
    {
	goto err_step;
    }
    if(schdap->sda_thdlst[pity].tdl_nr < 1)
    {
	goto err_step;
    }
    
    hal_spinlock_saveflg_cli(&schdap->sda_lock, &cpufg);
    hal_spinlock_saveflg_cli(&tdp->td_lock, &tcufg);
    /*将当前进程设置为等待*/
    tdp->td_stus = TDSTUS_WAIT;
    /*井进程从调度进程表中相关链表上拿出来*/
    list_del(&tdp->td_list);
    hal_spinunlock_restflg_sti(&tdp->td_lock, &tcufg);
    /*如果拿出的进程和当前优先级链表上正在运行的进程相同，让其为NULL*/
    if(schdap->sda_thdlst[pity].tdl_curruntd == tdp)
    {
	schdap->sda_thdlst[pity].tdl_curruntd = NULL;
    }
    /*进程数减一*/
    schdap->sda_thdlst[pity].tdl_nr--;
    hal_spinunlock_restflg_sti(&schdap->sda_lock, &cpufg);
    /*进程加入到相关的kwlst_t结构中*/
    krlwlst_add_thread(wlst, tdp);
    return;
err_step:
    hal_sysdie("krlsched_wait err");
    return;
}

void krlsched_up(kwlst_t *wlst)
{
    cpuflg_t cpufg, tpufg;
    uint_t cpuid = hal_retn_cpuid();
    schdata_t *schdap = &osschedcls.scls_schda[cpuid];
    thread_t * tdp;
    uint_t pity;
    if(wlst == NULL)
    {
	goto err_step;
    }
    tdp = krlwlst_del_thread(wlst);
    if(tdp == NULL)
    {
	goto err_step;
    }
    pity = tdp->td_priority;
    if(pity > PRITY_MAX)
    {
	goto err_step;
    }

    hal_spinlock_saveflg_cli(&schdap->sda_lock, &cpufg);
    hal_spinlock_saveflg_cli(&tdp->td_lock, &tpufg);
    tdp->td_stus = TDSTUS_RUN;
    hal_spinunlock_restflg_sti(&tdp->td_lock, &tpufg);
    list_add_tail(&tdp->td_list, &(schdap->sda_thdlst[pity].tdl_lsth));
    schdap->sda_thdlst[pity].tdl_nr++;
    hal_spinunlock_restflg_sti(&schdap->sda_lock, &cpufg);
    return;
err_step:
    hal_sysdie("krlschedp_up err");
    return;
}


