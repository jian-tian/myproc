/******************************
 * krlsched_t.h 2016.04.12
 * ***************************/
#ifndef KRLSCHED_T_H
#define KRLSCHED_T_H

#define NOTS_SCHED_FLGS	0
#define NEED_SCHED_FLGS	1

#define PMPT_FLGS   0

/*进程链表*/
typedef struct s_THRDLST
{
    list_h_t	tdl_lsth;
    thread_t *	tdl_curruntd;
    uint_t	tdl_nr;
}thrdlst_t;

/*进程调度器数据结构，包含进程链表数组，优先级区分*/
typedef struct s_SCHDATA
{
    spinlock_t	sda_lock;
    uint_t	sda_cpuid;
    uint_t	sda_schdflgs;
    uint_t	sda_premptidx;
    uint_t	sda_threadnr;
    uint_t	sda_prityidx;
    thread_t *	sda_cpuidle;
    thread_t *	sda_currtd;
    thrdlst_t	sda_thdlst[PRITY_MAX];
}schdata_t;

/*多cpu用调度数据结构*/
typedef struct s_SCHEDCLASS
{
    spinlock_t	scls_lock;
    uint_t	scls_cpunr;
    uint_t	scls_threadnr;
    uint_t	scls_threadid_inc;
    schdata_t	scls_schda[CPUCORE_MAX];
}schedclass_t;

#endif
