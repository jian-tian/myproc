/***************************
 * krlglobal.c 2016.03.02
 * ************************/
#define KRLGOBAL_HEAD
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

KRL_DEFGLOB_VARIABLE(kmempool_t, oskmempool);
KRL_DEFGLOB_VARIABLE(devtable_t, osdevtable);
KRL_DEFGLOB_VARIABLE(ktime_t, osktime);
KRL_DEFGLOB_VARIABLE(drventyexit_t, osdrvetytabl)[] = 
{
    systick_entry, /*mask systick temporarily*/ 
    NULL
};
