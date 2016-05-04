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

    hal_spinlock_saveflg_cli(&schdap->sda_lock, cpufg);
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
	//krlschedul();
    }

    return;
}
