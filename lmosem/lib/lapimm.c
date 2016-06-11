/********************
 * lapimm.c 2016.06.09
 * *****************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void api_mallocblk(size_t blksz)
{
    void * retadr;
    API_ENTRY_PAPE1(SNR_MM_ALLOC, retadr, blksz);
    return retadr;
}

sysstus_t * api_mfreeblk(void * fradr, size_t blksz)
{
    sysstus_t retstus;
    API_ENTRY_PAPE2(SNR_MM_FREE, retstus, fradr, blksz);
    return retstus;
}
