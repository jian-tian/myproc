/***********************
 * krlcpuidle.c 2016.04.14
 * *********************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void init_krlcpuidle()
{
    new_cpuidle();
    krlcpuidle_start();
    return;
}

void krlcpuidle_start()
{
    /*获取CPUid*/
    uint_t cpuid = hal_retn_cpuid();
    /*获取当前CPU的调度数据指针*/
    schdata_t * schdap = &osschedcls.scls_schda[cpuid];
    /*获取空转进程*/
    thread_t * tdp = schdap->sda_cpuidle;
    /*设置为RUN*/
    tdp->td_stus = TDSTUS_RUN;
    /*开始运行*/
    retnfrom_first_sched(tdp);
    return;
}

thread_t * new_cpuidle_thread()
{
    thread_t * ret_td = NULL;
    size_t usrstksz = DAFT_TDUSRSTKSZ;
    size_t krlstksz = DAFT_TDKRLSTKSZ;
    adr_t usrstkadr = NULL;
    adr_t krlstkadr = NULL;

    usrstkadr = krlnew(usrstksz);
    if(!usrstkadr)
    {
	printfk("alloc for usrstk failed\n\r");
	return NULL;
    }

    krlstkadr = krlnew(krlstksz);
    if(!krlstkadr)
    {
	if(krldelete(usrstkadr, usrstksz) == FALSE)
	{
	    printfk("free space for usrstk failed\n\r");
	}
	printfk("alloc for krlstk failed\n\r");
	return NULL;
    }

    ret_td = krlnew_thread_dsc();
    if(!ret_td)
    {
	if(FALSE == krldelete(usrstkadr, usrstksz))
	{
	    printfk("free space for usrstksz failed\n\r");
	}
	if(FALSE == krldelete(krlstkadr, krlstksz))
	{
	    printfk("free space for krlstk failed\n\r");
	}
	return NULL;
    }

    ret_td->td_privilege = PRILG_USR;
    ret_td->td_priority	= PRITY_MAX;
    ret_td->td_krlstktop = krlstkadr + (adr_t)(krlstksz -1);
    ret_td->td_krlstkstart = krlstkadr;
    ret_td->td_usrstktop = usrstkadr + (adr_t)(usrstksz - 1);
    ret_td->td_usrstkstart = usrstkadr;

    krlthreadkrlsatck_init(ret_td, (void *)krlcpuidle_main, DAFT_CPSR, DAFT_CIDLESPSR);

    uint_t cpuid = hal_retn_cpuid();
    /*获取当前CPU的数据调度结构*/
    schdata_t * schdap = &osschedcls.scls_schda[cpuid];
    /*空转进程地址赋值给sda_cpuidle*/
    schdap->sda_cpuidle = ret_td;
    /*当前进程为空转进程*/
    schdap->sda_currtd = ret_td;
    return ret_td;
}

void new_cpuidle()
{
    thread_t * thp = new_cpuidle_thread();

    if(!thp)
    {
	printfk("create cpuidle thread failed\n\r");;
	hal_sysdie("newcpuidle err");
    }
    /*输出空转线程地址，表示成功*/
    printfk("CPUIDLETASK: %x\n\r", (uint_t)thp);
}

void krlcpuidle_main()
{
    for(;;)
    {
	printfk("cpuidle is run!!\n\r");
	krlschedul();
    }
}
