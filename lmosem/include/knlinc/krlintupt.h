/*********************
 * krlintupt.h 2016.03.10
 * ******************/
#ifndef _KRLINTPUT_H
#define _KRLINTPUT_H
intserdsc_t * krladd_irqhandle(void * device, intflthandle_t handle, uint_t phyline);
drvstus_t krlenable_intline(uint_t ifdnr);
drvstus_t krldisable_intline(uint_t ifdnr);
#endif
