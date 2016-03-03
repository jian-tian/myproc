/***************************
 * ***krlinit.c 2016.02.19
 * ************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

extern void testpgmpool();
void init_krl()
{
    init_krlmm();
    testpgmpool();
    hal_sysdie("LMOSEM RUN!");
}
