/***************************
 * ***krlinit.c 2016.02.19
 * ************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

extern void testpgmpool();
extern void testpagemgr();
void init_krl()
{
    init_krlmm();
    testpagemgr();
    //testpgmpool();
    hal_sysdie("LMOSEM RUN!");
}
