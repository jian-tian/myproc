/****************************
 * lapitime.c 2016.6.11
 * *************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

sysstus_t api_time(buf_t ttime)
{
    sysstus_t rets;
    API_ENTRY_PARE1(SNR_TIME, rets, ttime);
    return rets;
}
