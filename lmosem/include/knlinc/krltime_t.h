/***************************
 * ktime_t.h 2016.3.30
 * ************************/
#ifndef KTIME_T_H
#define KTIME_T_H

typedef struct s_KTIME
{
    spinlock_t	kt_lock;
    uint_t	kt_year;
    uint_t	kt_mon;
    uint_t	kt_day;
    uint_t	kt_date;
    uint_t	kt_hour;
    uint_t	kt_min;
    uint_t	kt_sec;
    void *	kt_datap;
}ktime_t;

typedef struct s_TIME
{
    uint_t  year;
    uint_t  mon;
    uint_t  day;
    uint_t  date;
    uint_t  hour;
    uint_t  min;
    uint_t  sec;
}time_t;
#endif
