/*******************
 * halinit.c 2016.01.06
 * ***************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void init_hal()
{
    init_platform();
    init_haluart();
    init_halmach();
    init_halmm();
    init_halintupt();
    return;
}
