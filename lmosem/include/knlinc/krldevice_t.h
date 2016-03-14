/*****************************
 * krldevice_t.h 2016.03.11
 * **************************/
#ifndef _KRLDEVICE_T_H
#define _KRLDEVICE_T_H

#define NOT_DEVICE  0
#define AMBABUS_DEVICE	1
#define AHBBUS_DEVICE	2
#define APBBUS_DEVICE	3
#define BRIDGE_DEVICE	4
#define CPUCORE_DEVICE	5
#define RAMCONTER_DEVICE    6
#define RAM_DEVICE  7
#define USBHOSTCONTER_DEVICE	8
#define INTUPTCONTER_DEVICE	9
#define DMA_DEIVCE  10
#define CLOCKPOWER_DEVICE   11
#define LCDCONTER_DEVICE    12
#define NANDFLASH_DEVICE    13
#define CAMERA_DEVICE	    14
#define UART_DEVICE	    15
#define TIMER_DEVICE	    16
#define USB_DEVICE	    17
#define WATCHDOG_DEVICE	    18
#define IIC_DEVICE	    19
#define IIS_DEVICE	    20
#define GPIO_DEVICE	    21
#define RTC_DEVICE	    22
#define A_DCONVER_DEVICE    23
#define SPI_DEVICE	    24
#define SD_DEVICE	    25
#define AUDIO_DEVICE	    26
#define TOUCH_DEVICE	    27
#define NETWORK_DEVICE	    28
#define VIR_DEVICE	    29
#define FILESYS_DEVICE	    30
#define SYSTICK_DEVICE	    31
#define UNKNOWN_DEVICE	    32

#define DEVICE_MAX  33

#define IOIF_CODE_OPEN	0
#define IOIF_CODE_CLOSE	1
#define IOIF_CODE_READ	2
#define IOIF_CODE_WRITE	3
#define IOIF_CODE_LSEEK	4
#define IOIF_CODE_IOCTRL    5
#define IOIF_CODE_DEV_START 6
#define IOIF_CODE_DEV_STOP  7
#define IOIF_CODE_SET_POWERSTUS	8
#define IOIF_CODE_ENUM_DEV  9
#define IOIF_CODE_FLUSH	10
#define IOIF_CODE_SHUTDOWN  11
#define IOIF_CODE_MAX	12

#define DEVFLG_EXCLU	(1<<0)
#define DEVFLG_SHARE	(1<<1)
#define DEVFLG_NORML	(1<<0)
#define DEVFLG_FAILU	(1<<1)
#define DEVFLG_EXCLU	(1<<0)
#define DIDFIL_IDN  1
#define DIDFIL_FLN  2

#define FSDEV_IOCTRCD_DELFILE	5
#define FSDEV_OPENFLG_NEWFILE	1
#define FSDEV_OPENFLG_OPEFILE	2

typedef struct s_DEVLIST
{
    uint_t	dtl_type;
    uint_t	dtl_nr;
    list_h_t	dtl_list;
}devtlst_t;

typedef struct s_DEVTABLE
{
    list_h_t	devt_list;
    spinlock_t	*devt_lock;
    list_h_t	devt_devlist;//全局设备链表
    list_h_t	devt_drvlist;//全局驱动程序链表
    uint_t	devt_devnr;
    uint_t	devt_drvnr;
    devtlst_t	devt_devclsl[DEVICE_MAX];//分类存放设备数据结构数组
}devtable_t;

typedef struct s_DEVID
{
    uint_t dev_mtype;
    uint_t dev_stype;
    uint_t dev_nr;
}devid_t;

typedef struct s_DEVICE
{
    list_h_t	dev_list;
    list_h_t	dev_indrvlst;//设备驱动程序链表
    list_h_t	dev_intbllst;//设备表链表
    spinlock_t	dev_lock;
    uint_t	dev_count;
    sem_t	dev_sem;
    uint_t	dev_stus;
    uint_t	dev_flgs;
    devid_t	dev_id;
    uint_t	dev_intlnenr;//中断服务例程个数
    list_h_t	dev_intserlst;//中断服务例程链表
    list_h_t	dev_rqlist;   //对设备的请求服务链表
    uint_t	dev_rqlnr;
    sem_t	dev_waitints;
    struct s_DRIVER * dev_drv;//设备驱动程序数据结构
    void * dev_attrb;
    void * dev_privdata;
    void * dev_userdata;
    void * dev_extdata;
    char_t * dev_name; 
}device_t;

/*派发函数指针*/
typedef drvstus_t (*drivcallfun_t)(device_t *, void *);
/*驱动入口、退出函数指针*/
typedef drvstus_t (*drventyexit_t)(struct s_DRIVER *, uint_t, void *);
/*驱动程序数据结构*/
typedef struct s_DRIVER
{
    spinlock_t	drv_lock;
    list_h_t	drv_list;
    uint_t	drv_stuts;
    uint_t	drv_flg;
    uint_t	drv_id;
    uint_t	drv_count;
    sem_t	drv_sem;
    void *	drv_safedsc;
    void *	drv_attrb;
    void *	drv_privdata;
    drivcallfun_t drv_dipfun[IOIF_CODE_MAX];
    list_h_t	drv_alldevlist;
    drventyexit_t drv_entry;
    drventyexit_t drv_exit;
    void * drv_userdata;
    void * drv_extdata;
    char_t * drv_name;
}driver_t;

#endif
