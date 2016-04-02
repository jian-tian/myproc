/*****************************
 * krltime.c 2016.3.30
 * **************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void ktime_t_init(ktime_t * initp)
{
    hal_spinlock_init(&initp->kt_lock);
    initp->kt_year  = 0;
    initp->kt_mon   = 0;
    initp->kt_day   = 0;
    initp->kt_date  = 0;
    initp->kt_hour  = 0;
    initp->kt_min   = 0;
    initp->kt_sec   = 0;
    initp->kt_datap = NULL;
    return;
}

void init_ktime()
{
    ktime_t_init(&osktime);
    return;
}

void krlupdate_times(uint_t year, uint_t mon, uint_t day, uint_t date, uint_t hour, uint_t min, uint_t sec)
{
    ktime_t * initp = &osktime;
    cpuflg_t cpufg;
    hal_spinlock_saveflg_cli(&initp->kt_lock, &cpufg);
    initp->kt_year = year;
    initp->kt_mon = mon;
    initp->kt_day = day;
    initp->kt_date = date;
    initp->kt_hour = hour;
    initp->kt_min = min;
    initp->kt_sec = sec;
    hal_spinunlock_restflg_sti(&initp->kt_lock, &cpufg);
    return;
}
