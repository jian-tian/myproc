/***************************
 * krlglobal.c 2016.03.02
 * ************************/
#define KRLGOBAL_HEAD
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

KRL_DEFGLOB_VARIABLE(kmempool_t, oskmempool);
KRL_DEFGLOB_VARIABLE(drventyexit_t, osdrvetytable)[] = 
{
    systick_entry, 
    uart_entry, 
    rtc_entry, 
    rfs_entry,
    NULL
};
