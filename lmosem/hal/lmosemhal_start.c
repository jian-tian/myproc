#include "lmosemtypes.h"
#include "lmosemmctrl.h"

LKHEAD_T void lmosemhal_start()
{
    init_hal();
    init_krl();
    return;
}


LKHEAD_T void raise(uint_t signum)
{
    return;
} 
