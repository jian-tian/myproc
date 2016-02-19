/****************************
 * halintrupt.c 2016.02.17
 * *************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void init_halintupt()
{
    init_intfltdsc(&osmach);
}

void init_intfltdsc(mach_t * machp)
{
    intfltdsc_t * ifdp = machp->mh_intfltdsc;
    uint_t ifdnr = machp->mh_intfltnr;

    if(ifdnr > IRQ_MAX)
    {
	hal_sysdie("init intflt err");
    }

    for(uint_t i=MINTNR_START; i<=MINTNR_END; i++)
    {
	intfltdsc_t_init(&ifdp[i], MINT_FLG, 0, i-MINT_OFFSET, i);
    }

    for(uint_t i=SINTNR_START; i<=SINTNR_END; i++)
    {
	intfltdsc_t_init(&ifdp[i], SINT_FLG, 0, i-SINT_OFFSET, i);
    }

    for(uint_t i=EINTNR_START; i<=EINTNR_END; i++)
    {
	intfltdsc_t_init(&ifdp[i], EINT_FLG, 0, i-EINT_OFFSET, i);
    }

    return;
}

void intfltdsc_t_init(intfltdsc_t * initp, u32_t flg, u32_t stus,u32_t pbitnr, uint_t irqnr)
{
    hal_spinlock_init(&initp->i_lock);
    list_init(&initp->i_serlist);
    initp->i_sernr = 0;
    initp->i_flg = flg;
    initp->i_stus = stus;
    initp->i_pndbitnr = pbitnr;
    initp->i_irqnr = irqnr;
    initp->i_deep = 0;
    initp->i_indx = 0;

    return;
}
