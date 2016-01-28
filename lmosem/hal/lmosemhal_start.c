#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void lmosemhal_start()
{
    __asm__("b .");
    //init_hal();
    //return;
}

LKHEAD_T void raise(uint_t signum)
{
    return;
} 
