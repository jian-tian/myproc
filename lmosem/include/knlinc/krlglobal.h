/**************************
 * krlglobal.h 2016.03.02
 * **********************/
#ifndef KRLGLOBAL_H_
#define KRLGLOBAL_H_

#ifdef KRLGOBAL_HEAD
#undef KEXTERN
#define KEXTERN
#endif

KRL_DEFGLOB_VARIABLE(kmempool_t, oskmempool);
KRL_DEFGLOB_VARIABLE(schedclass_t, osschedcls);
KRL_DEFGLOB_VARIABLE(devtable_t, osdevtable);
KRL_DEFGLOB_VARIABLE(ktime_t, osktime);
KRL_DEFGLOB_VARIABLE(syscall_t, osscalltab)[SWINR_MAX];
KRL_DEFGLOB_VARIABLE(drventyexit_t,osdrvetytabl)[];
#endif
