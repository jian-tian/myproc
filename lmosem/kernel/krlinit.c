/***************************
 * ***krlinit.c 2016.02.19
 * ************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

extern void testpgmpool();
extern void testpagemgr();
extern void testobjsmgr();
void init_krl()
{
    init_krlmm();
    //testpagemgr();
    //testpgmpool();
    testobjsmgr();
    init_krldevice();
    init_krldriver();
    hal_enable_irq();
    for(;;);
    hal_sysdie("LMOSEM RUN!");
}
