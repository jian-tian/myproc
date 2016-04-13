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
