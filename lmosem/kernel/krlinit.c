/***************************
 * ***krlinit.c 2016.02.19
 * ************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

extern void testpgmpool();
extern void testpagemgr();
extern void testobjsmgr();
extern sysstus_t krlsve_time(time_t * time);

void testrtc()
{
    time_t *time_now;
    krlsve_time(time_now);
    printfk("origin time is %d:%d:%d:%d:%d:%d\n\r", time_now->year, time_now->mon, time_now->day,time_now->hour, time_now->min, time_now->sec);

    printfk("reset time\n\r");
    krlupdate_times(1,1,1,0,0,0,0);
    krlsve_time(time_now);
    printfk("new time is %d:%d:%d:%d:%d:%d\n\r", time_now->year, time_now->mon, time_now->day, time_now->hour, time_now->min, time_now->sec); 
    for(uint_t i = 0; i<10000; i++);
    printfk("new time after loop %d:%d:%d:%d:%d:%d\n\r", time_now->year, time_now->mon, time_now->day, time_now->hour, time_now->min, time_now->sec); 
    return;
}

void init_krl()
{
    init_krlmm();
    //testpagemgr();
    //testpgmpool();
    //testobjsmgr();
    init_krldevice();
    init_krldriver();
    init_krlsched();
    printfk("krlsched init ok \n\r");
    init_ktime();
    printfk("init_task init before \n\r");
    init_task();
    printfk("init_task init ok \n\r");
    init_krlcpuidle();
    hal_enable_irq();
    //testrtc();
    for(;;);
    hal_sysdie("LMOSEM RUN!");
}
