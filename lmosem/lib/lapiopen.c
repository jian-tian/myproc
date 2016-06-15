/***************************
 * lapiopen.c 2016.6.14
 * ***********************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

hand_t api_open(void *file, uint_t flgs, uint_t stus)
{
    hand_t rethand;
    API_ENTRY_PARE3(SNR_FS_OPEN, rethand, file, flgs, stus);
    return rethand;
}
