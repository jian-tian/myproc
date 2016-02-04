/**********************
 * *halmach.c 2016.2.3
 * ******************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void print_mach(mach_t * mchp);

void init_halmach(void)
{
    mach_t_init(&osmach);
    print_mach(&osmach);
    return;
}

void mach_t_init(mach_t * initp)
{
    hal_spinlock_lock(&initp->mh_lock);
    list_init(&initp->mh_list);
    initp->mh_kerinramstart = KRNL_INRAM_START;
    initp->mh_kerinramend = (adr_t)(&__end_kernel);
    initp->mh_mmapdscadr = (mmapdsc_t*)(ALIGN(((uint_t)(&__end_kernel)),4096));
    initp->mh_mmapdscnr = 0;
    initp->mh_spedscnr = PLFM_ADRSPCE_NR;
    initp->mh_spedsc = machadrspce;
    initp->mh_intfltdsc = machintflt;
    initp->mh_intfltnr = IRQ_MAX;
    return;
}

void print_mach(mach_t * mchp)
{
    printfk("mach.mh_kerinramstart:0x%x\n\r",(uint_t)mchp->mh_kerinramstart);
    printfk("mach.mh_kerinramend:0x%x\n\r",(uint_t)mchp->mh_kerinramend);
    printfk("mach.mh_mmapdscadr:0x%x\n\r",(uint_t)mchp->mh_mmapdscadr);
    printfk("mach.mh_mmapdscnr:0x%x\n\r",(uint_t)mchp->mh_mmapdscnr);
    printfk("mach.mh_intfltdsc:0x%x\n\r",(uint_t)mchp->mh_intfltdsc);
    printfk("mach.mh_intfltnr:0x%x\n\r",(uint_t)mchp->mh_intfltnr);
}
