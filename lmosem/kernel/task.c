/********************
 * task.c 2016.05.13
 * *****************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void task0_main();
void task1_main();

void task0()
{
    thread_t * thp = krlnew_thread((void *)task0_main, 0, PRILG_USR, PRITY_MIN, 0, 0);
    if(!thp)
    {
	hal_sysdie("task0 err");
    }
    printfk("task 0 id is 0x%x\n\r", (uint_t)thp);
    return;
}

void task1()
{
    thread_t * thp = krlnew_thread((void *)task1_main, 0, PRILG_USR, PRITY_MIN, 0, 0);
    if(!thp)
    {
	hal_sysdie("task1 err");
    }
    printfk("task 1 id is 0x%x\n\r", (uint_t)thp);
    return;
}

void init_task()
{
    task0();
    task1();
    printfk("init_task ok.\n\r");
    return;
}
