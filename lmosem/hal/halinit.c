/*******************
 * halinit.c 2016.01.06
 * ***************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

LKHEAD_T void init_hal()
{
    init_platform();
    init_haluart();
    return;
}
