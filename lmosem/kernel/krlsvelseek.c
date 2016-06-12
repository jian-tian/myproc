/*******************************
 * krlsvelseek.c 2016.6.11
 * ***************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"
sysstus_t krlsvetabl_lseek(uint_t swinr,stkparame_t* stkparv)
{
    if(swinr!=SNR_FS_LSEEK)
    {
        return SYSSTUSERR;
    }
    return krlsve_lseek((hand_t)stkparv->parmv1,(uint_t)stkparv->parmv2,
    (uint_t)stkparv->parmv3);
}

sysstus_t krlsve_lseek(hand_t fhand,uint_t lofset,uint_t flgs)
{
    return SYSSTUSERR;
}

sysstus_t krlsve_core_lseek(hand_t fhand,uint_t lofset,uint_t flgs)
{
    return SYSSTUSERR;
}

