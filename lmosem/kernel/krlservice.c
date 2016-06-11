/*******************
 * krlservice.c 2016.6.9
 * ****************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

sysstus_t krlservice(uint_t swinr, void * sframe)
{
    return osscalltab[swinr](swinr, (stkparme_t *)sframe);
}
