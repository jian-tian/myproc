/**************************
 * krldevice.c 2016.03.11
 * ***********************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

/*初始化设备类型挂载表*/
void devtlst_t_init(devtlst_t * initp, uint_t dtype)
{
    initp->dtl_type = dtype;
    initp->dtl_nr   = 0;
    list_init(&initp->dtl_list);
}

//初始化设备表
void devtable_t_init(devtable_t * initp)
{
    /*链表初始化*/
    list_init(&initp->devt_list);
    hal_spinlock_init(&initp->devt_lock);
    /*链表*/
    list_init(&initp->devt_devlist);
    list_init(&initp->devt_drvlist);
    initp->devt_devnr = 0;
    initp->devt_drvnr = 0;
    for(uint_t i=0; i<DEVICE_MAX; i++)
    {
	//依次初始化每个设备类型挂载表
	devtlst_t_init(&initp->devt_devclsl[i], i);
    }
    return;
}

void init_krldevice()
{
    //初始化设备表
    printfk("init_krldevice\n\r");
    devtable_t_init(&osdevtable);
    return;
}

void init_krldriver()
{
    printfk("init_krldriver begin\n\r");
    for(uint_t ei=0; osdrvetytabl[ei] != NULL; ei++)
    {
	printfk("osdrvetytabl[%d] begin\n\r", ei);
	if(krlrun_driverentry(osdrvetytabl[ei]) == DFCERRSTUS)
	{
	    hal_sysdie("init driver err");
	}
    }
    return;
}

/*所有功能操作的默认函数，返回一个错误状态*/
drvstus_t drv_default_func(device_t * devp, void * iopack)
{
    return DFCERRSTUS;
}

/*加载驱动程序数据结构到系统中(其实就是一个链表)*/
drvstus_t krldriver_add_system(driver_t * drvp)
{
    cpuflg_t cpufg;
    devtable_t * dtbp = &osdevtable;

    hal_spinlock_saveflg_cli(&dtbp->devt_lock, &cpufg);
    /*解锁后，添加驱动程序到程序链表中*/
    list_add(&drvp->drv_list, &dtbp->devt_drvlist);
    dtbp->devt_drvnr++;
    /*记得加解锁*/
    hal_spinunlock_restflg_sti(&dtbp->devt_lock, &cpufg);
    return DFCOKSTUS;
}

void krlretn_driverid(driver_t * dverp)
{
    /*每个驱动程序数据的实例变量的地址作为ID(有想法)*/
    dverp->drv_id = (uint_t)dverp;
    return;
}

/*初始化驱动程序数据结构*/
void driver_t_init(driver_t * initp)
{
    hal_spinlock_init(&initp->drv_lock);
    list_init(&initp->drv_list);
    initp->drv_stuts = 0;
    initp->drv_flg = 0;
    krlretn_driverid(initp);
    initp->drv_count = 0;
    initp->drv_safedsc = NULL;
    initp->drv_attrb = NULL;
    initp->drv_privdata = NULL;

    for(uint_t dsi=0; dsi<IOIF_CODE_MAX; dsi++)
    {
	initp->drv_dipfun[dsi] = drv_default_func;
    }

    list_init(&initp->drv_alldevlist);
    initp->drv_entry = NULL;
    initp->drv_exit = NULL;
    initp->drv_userdata = NULL;
    initp->drv_extdata = NULL;
    initp->drv_name = NULL;

    return;
}

driver_t * new_driver_dsc()
{
    /*相当于用个全局变量了*/
    driver_t * dp = (driver_t *)krlnew(sizeof(driver_t));
    if(!dp)
	return NULL;

    driver_t_init(dp);
    return dp;
}

drvstus_t krlrun_driverentry(drventyexit_t drventry)
{
    /*新建驱动程序数据结构实例变量*/
    driver_t * drvp = new_driver_dsc();
    if(!drvp)
    {
	printfk("new_driver_dsc in %s failed\n\r", __func__);
	return DFCERRSTUS;
    }

    /*调用驱动程序的入口函数*/
    if(drventry(drvp, 0, NULL) == DFCERRSTUS)
	return DFCERRSTUS;

    /*加载驱动程序数据结构到系统中*/
    if(krldriver_add_system(drvp) == DFCOKSTUS)
	return DFCERRSTUS;

    return DFCOKSTUS;
}

void devid_t_init(devid_t * initp, uint_t mty, uint_t sty, uint_t nr)
{
    initp->dev_mtype = mty;
    initp->dev_stype = sty;
    initp->dev_nr = nr;
    return;
}

void device_t_init(device_t * initp)
{
    /*三大链表??*/
    list_init(&initp->dev_list);
    list_init(&initp->dev_indrvlst);
    list_init(&initp->dev_intbllst);
    hal_spinlock_init(&initp->dev_lock);
    initp->dev_count = 0;

    /*设备数据结构中信号量*/
    krlsem_t_init(&initp->dev_sem);
    initp->dev_stus = 0;
    initp->dev_flgs = 0;
    devid_t_init(&initp->dev_id, 0, 0, 0);
    initp->dev_intlnenr = 0;

    /*信号量*/
    list_init(&initp->dev_intserlst);
    list_init(&initp->dev_rqlist);
    initp->dev_rqlnr = 0;

    krlsem_t_init(&initp->dev_waitints);
    initp->dev_drv = NULL;
    initp->dev_attrb = NULL;
    initp->dev_privdata = NULL;
    initp->dev_userdata = NULL;
    initp->dev_extdata = NULL;
    initp->dev_name = NULL;
    return;
}

drvstus_t del_device_dsc(device_t * devp)
{
    if(krldelete((adr_t)devp, sizeof(device_t)) == FALSE)
	return DFCOKSTUS;
    return DFCOKSTUS;
}

device_t * new_device_dsc()
{
    device_t * dp = (device_t *)krlnew(sizeof(device_t));
    if(!dp)
	return NULL;

    device_t_init(dp);
    return dp;
}

bool_t krlcmp_devid(devid_t * sdidp, devid_t * cdidp)
{
    if(sdidp->dev_mtype != cdidp->dev_mtype)
	return FALSE;

    if(sdidp->dev_stype != cdidp->dev_stype)
	return FALSE;

    if(sdidp->dev_nr != cdidp->dev_nr)
	return FALSE;

    return TRUE;
}

drvstus_t krldev_add_driver(device_t * devp, driver_t * drvp)
{
    list_h_t * lst;
    device_t * fdevp;
    if(devp == NULL || drvp == NULL)
	return DFCERRSTUS;

    /*遍历driver_t 结构中的drv_alldevlist链表上所有device_t结构，比较
      要加入的设备是否已经存在*/
    list_for_each(lst, &drvp->drv_alldevlist)
    {
	fdevp = list_entry(lst, device_t, dev_indrvlst);
	if(krlcmp_devid(&devp->dev_id, &fdevp->dev_id) == TRUE)
	    return DFCERRSTUS;
    }

    /*将device_t 设备加入到driver_t中的drv_alldevlist上，同时该device_t 
      的dev_drv指向driver_t*/
    list_add(&devp->dev_indrvlst, &drvp->drv_alldevlist);
    devp->dev_drv = drvp;
    return DFCOKSTUS;
}

drvstus_t krlnew_device(device_t * devp)
{
    device_t * findevp;
    drvstus_t rets = DFCERRSTUS;
    cpuflg_t cpufg;
    list_h_t * lstp;
    /*设备表地址*/
    devtable_t * dtbp = &osdevtable;
    uint_t devmty = devp->dev_id.dev_mtype;
    if(!devp)
	return DFCERRSTUS;
    /*设备是否有驱动程序*/
    if(!devp->dev_drv)
	return DFCERRSTUS;

    /*检查设备类型*/
    if(devmty >= DEVICE_MAX)
	return DFCERRSTUS;

    hal_spinlock_saveflg_cli(&dtbp->devt_lock, &cpufg);
    /*检查设备类型是否和设备表元素中类型相同*/
    if(devmty != dtbp->devt_devclsl[devmty].dtl_type)
    {
	rets = DFCERRSTUS;
	goto return_step;
    }
    /*遍历设备，确保没有相同设备ID*/
    list_for_each(lstp, &dtbp->devt_devclsl[devmty].dtl_list)
    {
	findevp = list_entry(lstp, device_t, dev_intbllst);
	if(krlcmp_devid(&devp->dev_id, &findevp->dev_id) == TRUE)
	{
	    rets = DFCERRSTUS;
	    goto return_step;
	}
    }
    /*设备挂入该设备类型的挂载链表中*/
    list_add(&devp->dev_intbllst, &dtbp->devt_devclsl[devmty].dtl_list);
    /*设备挂入设备全局链表中*/
    list_add(&devp->dev_list, &dtbp->devt_devlist);
    /*增加该设备类型挂载体重计数*/
    dtbp->devt_devclsl[devmty].dtl_nr++;
    /*全局设备计数*/
    dtbp->devt_devnr++;
    rets = DFCOKSTUS;
return_step:
    hal_spinunlock_restflg_sti(&dtbp->devt_lock, &cpufg);
    return rets;
}

drvstus_t krlnew_devhandle(device_t * devp, intflthandle_t handle, uint_t phyiline)
{
    /*注册中断回调函数，返回一个数据结构intserdsc_t*/
    intserdsc_t * sdp = krladd_irqhandle(devp, handle, phyiline);
    if(!sdp)
	return DFCERRSTUS;

    cpuflg_t cpufg;
    hal_spinlock_saveflg_cli(&devp->dev_lock, &cpufg);
    /*添加intserdsc_t到device中*/    
    list_add(&sdp->s_indevlst, &devp->dev_intserlst);
    devp->dev_intlnenr++;
    hal_spinunlock_restflg_sti(&devp->dev_lock, &cpufg);
    return DFCOKSTUS;
}

drvstus_t krldev_io(objnode_t * nodep)
{
    //提取要访问的设备数据结构的指针
    device_t * devp = (device_t *)(nodep->on_objadr);
    if(nodep->on_objtype != OBJN_TY_DEV || nodep->on_objadr == NULL)
	return DFCERRSTUS;

    if(nodep->on_opercode < 0 || nodep->on_opercode >= IOIF_CODE_MAX)
	return DFCERRSTUS;
    /*调用设备的驱动程序*/
    return krldev_call_driver(devp, nodep->on_opercode, 0, 0, NULL, nodep);
}

drvstus_t krldev_call_driver(device_t * devp, uint_t iocode, uint_t val1, uint_t val2, void * p1, void * p2)
{
    driver_t * drvp = NULL;
    if(devp == NULL || iocode >= IOIF_CODE_MAX)
	return DFCERRSTUS;

    drvp = devp->dev_drv;

    if(drvp == NULL)
	return DFCERRSTUS;

    return drvp->drv_dipfun[iocode](devp, p2);
}

drvstus_t krldev_add_request(device_t * devp, objnode_t * request)
{
    cpuflg_t cpufg;
    objnode_t * np = (objnode_t *)request;
    hal_spinlock_saveflg_cli(&devp->dev_lock, &cpufg);
    /*把IO包加到当前设备链表中*/
    list_add_tail(&np->on_list, &devp->dev_rqlist);
    devp->dev_rqlnr++;
    hal_spinunlock_restflg_sti(&devp->dev_lock, &cpufg);
    return DFCOKSTUS;
}

drvstus_t krldev_wait_request(device_t *devp, objnode_t * request)
{
    if(devp == NULL || request == NULL)
	return DFCERRSTUS;

    /*操作IO包的on_complesem信号量*/
    krlsem_down(&request->on_complesem);
    return DFCOKSTUS;
}

drvstus_t krldev_retv_request(device_t *devp, uint_t iocode, objnode_t ** retreq)
{
    if(retreq == NULL || iocode >= IOIF_CODE_MAX)
	return DFCERRSTUS;

    cpuflg_t cpufg;
    objnode_t *np;
    list_h_t * list;
    drvstus_t rets = DFCERRSTUS;

    hal_spinlock_saveflg_cli(&devp->dev_lock, &cpufg);
    /*遍历dev_rqlist链表上所有IO包*/
    list_for_each(list, &devp->dev_rqlist)
    {
	np = list_entry(list, objnode_t, on_list);
	/*比较IO操作码是否相同，相同则通过retreq参数返回这个IO包指针*/
	if(np->on_opercode == (sint_t)iocode)
	{
	    *retreq = np;
	    rets = DFCOKSTUS;
	    goto return_step;
	}
    }
    rets = DFCERRSTUS;
    *retreq = NULL;
return_step:
    hal_spinunlock_restflg_sti(&devp->dev_lock, &cpufg);
    return rets;
}

drvstus_t krldev_complete_request(device_t * devp, objnode_t * request)
{
    if(devp == NULL || request == NULL)
	return DFCERRSTUS;

    if(devp->dev_rqlnr < 1)
    {
	hal_sysdie("krldev_complete_request err dev_rqlnr < 1");
    }

    cpuflg_t cpufg;
    hal_spinlock_saveflg_cli(&devp->dev_lock, &cpufg);
    /*从链表中删除IO包*/
    list_del(&request->on_list);
    devp->dev_rqlnr--;
    hal_spinunlock_restflg_sti(&devp->dev_lock, &cpufg);
    /*操作信号量，同时唤醒相关进程*/
    krlsem_up(&request->on_complesem);
    return DFCOKSTUS;
}

drvstus_t krldev_inc_devcount(device_t * devp)
{
    cpuflg_t cpufg;
    hal_spinlock_saveflg_cli(&devp->dev_lock, &cpufg);
    if(devp->dev_count >= (~0UL))
    {
	hal_spinlock_saveflg_cli(&devp->dev_lock, &cpufg);
	return DFCERRSTUS;
    }
    devp->dev_count++;
    hal_spinunlock_restflg_sti(&devp->dev_lock, &cpufg);
    return DFCOKSTUS;
}

drvstus_t krldev_dec_devcount(device_t * devp)
{
    cpuflg_t cpufg;
    hal_spinlock_saveflg_cli(&devp->dev_lock, &cpufg);
    if(devp->dev_count < 1)
    {
	hal_spinunlock_restflg_sti(&devp->dev_lock, &cpufg);
	return DFCERRSTUS;
    }
    devp->dev_count--;
    hal_spinunlock_restflg_sti(&devp->dev_lock, &cpufg);
    return DFCOKSTUS;
}

drvstus_t krldev_retn_rqueparm(void * request, buf_t * retbuf, uint_t * retcops, uint_t * retlen, uint_t * retioclde, uint_t * retbufcops, size_t * retbufsz)
{
    objnode_t * ondep = (objnode_t *)request;
    if(ondep == NULL)
	return DFCERRSTUS;

    if(retbuf)
	*retbuf = ondep->on_buf;

    if(retcops)
	*retcops = ondep->on_currops;

    if(retlen)
	*retlen = ondep->on_len;

    if(retioclde)
	*retioclde = ondep->on_ioctrd;

    if(retbufcops)
	*retbufcops = ondep->on_bufcurops;

    if(retbufsz)
	*retbufsz = ondep->on_bufsz;

    return DFCOKSTUS;
}

device_t * krlonidfl_retn_device(void * dfname, uint_t flgs)
{
    device_t * findevp;
    cpuflg_t cpufg;
    list_h_t * lstp;
    devtable_t * dtbp = &osdevtable;
    /*参数检测*/
    if(dfname == NULL || flgs != DIDFIL_IDN)
	return NULL;
    /*获取devid_t 数据结构指针*/
    devid_t * didp = (devid_t *)dfname;
    uint_t devmty = didp->dev_mtype;
    if(devmty >= DEVICE_MAX)
	return NULL;

    hal_spinlock_saveflg_cli(&dtbp->devt_lock, &cpufg);
    if(devmty != dtbp->devt_devclsl[devmty].dtl_type)
    {
	findevp = NULL;
	goto return_step;
    }
    /*遍历当前设备类型的设备挂载链表上的所有设备，
      每找到一个设备就比较器设备ID*/
    list_for_each(lstp, &dtbp->devt_devclsl[devmty].dtl_list)
    {
	findevp = list_entry(lstp, device_t, dev_intbllst);
	if(krlcmp_devid(didp, &findevp->dev_id) == TRUE)
	{
	    findevp = findevp;
	    goto return_step;
	}
    }

    findevp = NULL;
return_step:
    hal_spinunlock_restflg_sti(&dtbp->devt_lock, &cpufg);
    return findevp;
}
