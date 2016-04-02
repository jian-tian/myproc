/***************************
 * drvrtc.c 2016.3.26
 * ************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void rtc_set_driver(driver_t * drvp)
{
    drvp->drv_dipfun[IOIF_CODE_OPEN] = rtc_open;
    drvp->drv_dipfun[IOIF_CODE_CLOSE] = rtc_close;
    drvp->drv_dipfun[IOIF_CODE_READ] = rtc_read;
    drvp->drv_dipfun[IOIF_CODE_WRITE] = rtc_write;
    drvp->drv_dipfun[IOIF_CODE_LSEEK] = rtc_lseek;
    drvp->drv_dipfun[IOIF_CODE_IOCTRL] = rtc_ioctrl;
    drvp->drv_dipfun[IOIF_CODE_DEV_START] = rtc_dev_start;
    drvp->drv_dipfun[IOIF_CODE_DEV_STOP] = rtc_dev_stop;
    drvp->drv_dipfun[IOIF_CODE_SET_POWERSTUS] = rtc_set_powerstus;
    drvp->drv_dipfun[IOIF_CODE_ENUM_DEV] = rtc_enum_dev;
    drvp->drv_dipfun[IOIF_CODE_READ] = rtc_read;
    drvp->drv_dipfun[IOIF_CODE_FLUSH] = rtc_flush;
    drvp->drv_dipfun[IOIF_CODE_SHUTDOWN] = rtc_shutdown;
    return;
}

void rtc_set_device(device_t * devp, driver_t * drvp)
{
    devp->dev_flgs = DEVFLG_SHARE;
    devp->dev_stus = DEVSTS_NORML;
    devp->dev_id.dev_mtype = RTC_DEVICE;
    devp->dev_id.dev_stype = 0;
    devp->dev_id.dev_nr = 0;
    devp->dev_name = "rtc";
    return;
}

void init_rtc()
{
    /*开启RTC设备*/
    hal_io8_write(RTCCON_R, 1);
    /*开启节拍中断，节拍时间设置为127*/
    hal_io8_write(TICNT_R, RTCTICK_INT_EN | 127);
    return;
}

drvstus_t rtc_entry(driver_t * drvp, uint_t val, void *p)
{
    if(drvp == NULL)
    {
	printfk("drvp error\n\r");
	return DFCERRSTUS;
    }

    device_t * devp = new_device_dsc();
    if(!devp)
    {
	printfk("new_device_dsc failed\n\r");
	return DFCOKSTUS;
    }

    rtc_set_driver(drvp);
    rtc_set_device(devp, drvp);

    if(DFCERRSTUS == krldev_add_driver(devp, drvp))
    {
	printfk("add driver failed\n\r");
	if(DFCERRSTUS == del_device_dsc(devp))
	{
	    printfk("del device dsc failed\n\r");
	    return DFCERRSTUS;
	}
	return DFCERRSTUS;
    }

    if(DFCERRSTUS == krlnew_device(devp))
    {
	printfk("krlnew device failed\n\r");
	if(DFCERRSTUS == del_device_dsc(devp))
	{
	    printfk("del device dsc failed\n\r");
	    return DFCERRSTUS;
	}
	return DFCERRSTUS;
    }

    if(DFCERRSTUS == krlnew_devhandle(devp, rtc_handle, MINT_IFDNR(RTC_INT_PHYLINE)))
    {
	printfk("krlnew rtc_handle failed\n\r");
	return DFCERRSTUS;
    }

    if(DFCERRSTUS == krlnew_devhandle(devp, rtc_tick_handle, MINT_IFDNR(RTCTICK_INT_PHYLINE)))
    {
	printfk("krlnew rtc_tick_handle failed\n\r");
	return DFCERRSTUS;
    }

    if(DFCERRSTUS == krlenable_intline(MINT_IFDNR(RTC_INT_PHYLINE)))
    {
	printfk("krl enable rtc_int failed\n\r");
	return DFCERRSTUS;
    }

    if(DFCERRSTUS == krlenable_intline(MINT_IFDNR(RTCTICK_INT_PHYLINE)))
    {
	printfk("krl enable rtctick_int failed\n\r");
	return DFCERRSTUS;
    }

    init_rtc();

    return DFCOKSTUS;
}

drvstus_t rtc_tick_handle(uint_t ift_nr, void *devp, void *frame)
{
    uint_t year = hal_io8_read(BCDYER_R);
    uint_t mon = hal_io8_read(BCDMON_R);
    uint_t day = hal_io8_read(BCDDAY_R);
    uint_t date = hal_io8_read(BCDDAT_R);
    uint_t hour = hal_io8_read(BCDHOR_R);
    uint_t min = hal_io8_read(BCDMIN_R);
    uint_t sec = hal_io8_read(BCDSEC_R);

    BCD_TO_BIN(year);
    BCD_TO_BIN(mon);
    BCD_TO_BIN(day);
    BCD_TO_BIN(date);
    BCD_TO_BIN(hour);
    BCD_TO_BIN(min);
    BCD_TO_BIN(sec);

    year += 2000;
    krlupdate_times(year, mon, day, date, hour, min, sec);
    return DFCOKSTUS;
}

drvstus_t rtc_read(device_t * devp, void * iopack)
{
    uint_t len;
    buf_t   retbuf;
    if(DFCERRSTUS == krldev_retn_rqueparm(iopack, &retbuf, NULL, &len, NULL, NULL, NULL))
    {
	printfk("get retbuf failed\n\r");
	return DFCERRSTUS;
    }

    if(!retbuf || len < sizeof(time_t))
    {
	printfk("retbuf or len failed\n\r");
	return DFCERRSTUS;
    }

    uint_t year = hal_io8_read(BCDYER_R);
    uint_t mon = hal_io8_read(BCDMON_R);
    uint_t day = hal_io8_read(BCDDAY_R);
    uint_t date = hal_io8_read(BCDDAT_R);
    uint_t hour = hal_io8_read(BCDHOR_R);
    uint_t min = hal_io8_read(BCDMIN_R);
    uint_t sec = hal_io8_read(BCDSEC_R);

    BCD_TO_BIN(year);
    BCD_TO_BIN(mon);
    BCD_TO_BIN(day);
    BCD_TO_BIN(date);
    BCD_TO_BIN(hour);
    BCD_TO_BIN(min);
    BCD_TO_BIN(sec);

    time_t * times = (time_t *)retbuf;
    times->year = 2000 + year;
    times->mon = mon;
    times->day = day;
    times->date = date;
    times->hour = hour;
    times->min = min;
    times->sec = sec;

    return DFCOKSTUS;
}

drvstus_t rtc_settime(time_t * times)
{
    hal_io8_write(RTCCON_R, 1);
    uint_t year = times->year;
    uint_t mon = times->mon;
    uint_t day = times->day;
    uint_t date = times->date;
    uint_t hour = times->hour;
    uint_t min = times->min;
    uint_t sec = times->sec;
    
    BIN_TO_BCD(year);
    BIN_TO_BCD(mon);
    BIN_TO_BCD(day);
    BIN_TO_BCD(date);
    BIN_TO_BCD(hour);
    BIN_TO_BCD(min);
    BIN_TO_BCD(sec);

    hal_io8_write(BCDYER_R, (u8_t)year);
    hal_io8_write(BCDMON_R, (u8_t)mon);
    hal_io8_write(BCDDAY_R, (u8_t)day);
    hal_io8_write(BCDDAT_R, (u8_t)date);
    hal_io8_write(BCDHOR_R, (u8_t)hour);
    hal_io8_write(BCDMIN_R, (u8_t)min);
    hal_io8_write(BCDSEC_R, (u8_t)sec);

    return DFCOKSTUS;
}

drvstus_t rtc_set_synsecalm(device_t * devp, void * iopack, uint_t sec)
{
    if(sec >= 60)
    {
	printfk("sec >= 60, error\n\r");
	return DFCERRSTUS;
    }

    hal_io8_write(RTCCON_R, 1);
    uint_t year = hal_io8_read(BCDYER_R);
    uint_t mon = hal_io8_read(BCDMON_R);
    uint_t day = hal_io8_read(BCDDAY_R);
    uint_t date = hal_io8_read(BCDDAT_R);
    uint_t hour = hal_io8_read(BCDHOR_R);
    uint_t min = hal_io8_read(BCDMIN_R);
    uint_t tmpsec = hal_io8_read(BCDSEC_R);

    BCD_TO_BIN(tmpsec);
    tmpsec += sec;
    BIN_TO_BCD(tmpsec);

    hal_io8_write(BCDYER_R, (u8_t)year);
    hal_io8_write(BCDMON_R, (u8_t)mon);
    hal_io8_write(BCDDAY_R, (u8_t)day);
    hal_io8_write(BCDDAT_R, (u8_t)date);
    hal_io8_write(BCDHOR_R, (u8_t)hour);
    hal_io8_write(BCDMIN_R, (u8_t)min);
    hal_io8_write(BCDSEC_R, (u8_t)tmpsec);

    if(DFCERRSTUS == krldev_add_request(devp, (objnode_t *)iopack))
    {
	hal_sysdie("rtc setsynalm run\n\r");
	return DFCERRSTUS;
    }

    hal_io8_write(RTCALM_R, RTCALM_EN|RTCSECALM_EN);

    krldev_wait_request(devp, (objnode_t *)iopack);

    return DFCOKSTUS;
}

drvstus_t rtc_ioctrl(device_t * devp, void * iopack)
{
    uint_t retioclde = 0;
    buf_t   retbuf = NULL;

    if(DFCERRSTUS == krldev_retn_rqueparm(iopack, &retbuf, NULL, NULL, &retioclde, NULL, NULL))
    {
	printfk("get retbuf error\n\r");
	return DFCERRSTUS;
    }

    if(!retbuf)
    {
	printfk("retbuf NULL\n\r");
	return DFCERRSTUS;
    }

    if(retioclde == IOCTRCODE_SET_SYNSECALM)
    {
	return rtc_set_synsecalm(devp, iopack, *((uint_t *)(retbuf)));
    }

    if(retioclde == IOCTRCODE_SETTIME)
    {
	return rtc_settime((time_t *)retbuf);
    }

    if(retioclde == IOCTRCODE_SETUPFREQ)
    {
	return rtc_upfreq(*((uint_t *)(retbuf)));
    }
    return DFCERRSTUS;
}

drvstus_t rtc_handle(uint_t ift_nr, void *devp, void * sframe)
{
    objnode_t * request;
    if(((device_t *)devp)->dev_rqlnr > 0)
    {
	hal_sysdie("rtc hand run err no retn request\n\r");
    }

    if(DFCERRSTUS == krldev_complete_request((device_t *)devp, request))
    {
	hal_sysdie("rtc hand run err no compelete_request\n\r");
    }

    return DFCOKSTUS;
}

drvstus_t rtc_open(device_t * devp, void * iopack)
{
    return krldev_inc_devcount(devp);
}
