/************************
 * drvtick.c 2016.03.15
 * *********************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void init_s3c2440_timer4()
{
    /*读取配置寄存器0*/
    u32_t cfgtmp = hal_io32_read(TCFG0_R);
    /*清除TCFG0_R 8~15bit*/
    cfgtmp &= 0xFFFF00FF;
    cfgtmp |= 0xFF00;
    /*设置第二个预分频为255*/
    hal_io32_write(TCFG0_R, cfgtmp);
    /*读取配置寄存器1*/
    cfgtmp = hal_io32_read(TCFG1_R);
    /*选择定时器4的选通输入为0000=1/2*/
    cfgtmp &= 0xFFF0FFFF;
    /*写入定时器的配置寄存器1*/
    hal_io32_write(TCFG1_R, cfgtmp);
    /*设置定时器4的TCNTB_R*/
    hal_io32_write(TCNTB4_R, 0x41);
    cfgtmp = hal_io32_read(TCON_R);
    /*设置TCON_R 20-22位为1，清零21bit*/
    cfgtmp |= 0x700000;
    hal_io32_write(TCON_R, cfgtmp);
    cfgtmp = hal_io32_read(TCON_R);
    /*设置TCON_R 20bit*/
    cfgtmp &= (~0x200000);
    /*写入TCON_R并启动定时器4*/
    hal_io32_write(TCON_R, cfgtmp);

    return;
}

void systick_set_driver(driver_t *drvp)
{
    drvp->drv_dipfun[IOIF_CODE_OPEN] = systick_open;
    drvp->drv_dipfun[IOIF_CODE_CLOSE] = systick_close;
    drvp->drv_dipfun[IOIF_CODE_READ] = systick_read;
    drvp->drv_dipfun[IOIF_CODE_WRITE] = systick_write;
    drvp->drv_dipfun[IOIF_CODE_LSEEK] = systick_lseek;
    drvp->drv_dipfun[IOIF_CODE_IOCTRL] = systick_ioctrl;
    drvp->drv_dipfun[IOIF_CODE_DEV_START] = systick_dev_start;
    drvp->drv_dipfun[IOIF_CODE_DEV_STOP] = systick_dev_stop;
    drvp->drv_dipfun[IOIF_CODE_SET_POWERSTUS] = systick_set_powerstus;
    drvp->drv_dipfun[IOIF_CODE_ENUM_DEV] = systick_enum_dev;
    drvp->drv_dipfun[IOIF_CODE_FLUSH] = systick_flush;
    drvp->drv_dipfun[IOIF_CODE_SHUTDOWN] = systick_shutdown;
    drvp->drv_name = "systick0drv";
    return;
}

void systick_set_device(device_t * devp, driver_t * drvp)
{
    devp->dev_flgs = DEVFLG_SHARE;
    devp->dev_stus = DEVSTS_NORML;
    devp->dev_id.dev_mtype = SYSTICK_DEVICE;
    devp->dev_id.dev_stype = 0;
    devp->dev_id.dev_nr = 0;
    devp->dev_name = "systick0";
    return;
}

/*入口函数*/
drvstus_t systick_entry(driver_t * drvp, uint_t val, void * p)
{
    printfk("systick_entry start\n");
    if(!drvp)
	return DFCERRSTUS;

    device_t * devp = new_device_dsc();
    if(!devp)
	return DFCERRSTUS;
    /*设置驱动程序数据结构和设备数据结构中的相关域*/
    systick_set_driver(drvp);
    systick_set_device(devp, drvp);
    /*向驱动程序注册设备*/
    if(krldev_add_driver(devp, drvp) == DFCERRSTUS)
    {
	if(del_device_dsc(devp) == DFCERRSTUS)
	    return DFCERRSTUS;
	return DFCERRSTUS;
    }
    /*向内核注册设备*/
    if(krlnew_device(devp) == DFCERRSTUS)
    {
	if(del_device_dsc(devp) == DFCERRSTUS)
	    return DFCERRSTUS;
	return DFCERRSTUS;
    }
    /*注册中断回调函数*/
    if(krlnew_devhandle(devp, systick_handle, MINT_IFDNR(SYSTICK_PHYINTLINE)) == DFCERRSTUS)
    {
	if(del_device_dsc(devp) == DFCERRSTUS)
	    return DFCERRSTUS;
	return DFCERRSTUS;
    }
    /*初始化定时器*/
    init_s3c2440_timer4();
    /*解除中断屏蔽位*/
    if(krlenable_intline(MINT_IFDNR(SYSTICK_PHYINTLINE)) == DFCERRSTUS)
    {
	if(del_device_dsc(devp) == DFCERRSTUS)
	    return DFCERRSTUS;
	return DFCERRSTUS;
    }
    return DFCOKSTUS;
}

/*退出函数*/
drvstus_t systick_exit(driver_t * drvp, uint_t val, void *p)
{
    return DFCERRSTUS;
}


/*中断回调函数*/
drvstus_t systick_handle(uint_t ift_nr, void *devp, void * sframe)
{
    return DFCOKSTUS;
}

/*打开函数*/
drvstus_t systick_open(device_t * devp, void * iopack)
{
    return DFCERRSTUS;
}

/*关闭函数*/
drvstus_t systick_close(device_t * devp, void * iopack)
{
    return DFCERRSTUS;
}

/*读函数*/
drvstus_t systick_read(device_t * devp, void * iopack)
{
    return DFCERRSTUS;
}

/*写函数*/
drvstus_t systick_write(device_t * devp, void * iopack)
{
    return DFCERRSTUS;
}

/*调整读写位置函数*/
drvstus_t systick_lseek(device_t * devp, void * iopack)
{
    return DFCERRSTUS;
}

/*控制函数*/
drvstus_t systick_ioctrl(device_t * devp, void * iopack)
{
    return DFCERRSTUS;
}

/*开始函数*/
drvstus_t systick_dev_start(device_t * devp, void * iopack)
{
    return DFCERRSTUS;
}

/*停止函数*/
drvstus_t systick_dev_stop(device_t * devp, void * iopack)
{
    return DFCERRSTUS;
}

/*设置电源函数*/
drvstus_t systick_set_powerstus(device_t * devp, void * iopack)
{
    return DFCERRSTUS;
}

/*枚举函数*/
drvstus_t systick_enum_dev(device_t * devp, void * iopack)
{
    return DFCERRSTUS;
}

/*刷新缓存函数*/
drvstus_t systick_flush(device_t * devp, void * iopack)
{
    return DFCERRSTUS;
}

/*关机函数*/
drvstus_t systick_shutdown(device_t * devp, void * iopack)
{
    return DFCERRSTUS;
}

