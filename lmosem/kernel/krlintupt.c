/*******************
 * 2016.03.10 krlintupt.c
 * ****************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

intserdsc_t * krladd_irqhandle(void * device, intflthandle_t handle, uint_t phyline)
{
    /*如果设备描述符或者中断回调函数地址为NULL，表示错误*/
    if(device == NULL || handle == NULL)
	return NULL;
    /*获取中断源描述符*/
    intfltdsc_t * intp = hal_retn_intfltdsc(phyline);
    if(intp == NULL)
	return NULL;
    /*分配一个中断函数描述符空间*/
    intserdsc_t * serdscp = (intserdsc_t *)krlnew(sizeof(intserdsc_t));
    if(NULL == serdscp)
	return NULL;
    /*初始化中断函数描述符*/
    intserdsc_t_init(serdscp, 0, intp, device, handle);
    if(hal_add_ihandle(intp, serdscp) == FALSE)
    {/*如果中断函数描述符加入到中断源描述符中失败，释放中断函数描述符空间*/
	if(krldelete((adr_t)serdscp, sizeof(intserdsc_t)) == FALSE)
	{
	    hal_sysdie("krladd_irqhandle err");
	}
	return NULL;
    }
    return serdscp;
}

drvstus_t krlenable_intline(uint_t ifdnr)
{
    return hal_enable_intline(ifdnr);
}

drvstus_t krldisable_intline(uint_t ifdnr)
{
    return hal_disable_intline(ifdnr);
}
