/********************
 * utask.c 2016.05.13
 * *****************/
//#include "stdio.h"
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

uint_t g_i_1 = 0;
uint_t g_i_0 = 0;
void task1_main()
{
    int i = 0;
    for(;;)
    {
	i++;
	g_i_1++;
	//printfk("task1 run %d, %d\n\r", i, g_i_1);
    }
    return;
}

void task0_main()
{
    int i = 0;
    for(;;)
    {
	i++;
	g_i_0++;
	//printfk("task0 run %d ,%d\n\r", i, g_i_0);
    }
}
