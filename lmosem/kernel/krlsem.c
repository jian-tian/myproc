/*********************************
 * krlsem.c 2016.03.14
 * *****************************/
#include "lmosemstype.h"
#include "lmosemmctrl.h"

void krlsem_t_init(sem_t * initp)
{
    hal_spinlock_init(&initp->sem_lock);
    initp->sem_flg = 0;
    initp->sem_count = 0;
    kwlst_t_init(&initp->sem_waitlst);
    return;
}

void krlsem_set_sem(sem_t * setsem, uint_t flg, size_t count)
{
    cpuflg_t cpufg;
    hal_spinlock_saveflg_cli(&setsem->sem_lock, &cpufg);
    setsem->sem_flg = flg;
    setsem->sem_count = count;
    hal_spinunlock_restflg_sti(&setsem->sem_lock, &cpufg);
    return;
}

void krlsem_down(sem_t * sem)
{
    cpuflg_t cpufg;
start_step:
    hal_spinlock_saveflg_cli(&sem->sem_lock, &cpufg);
    if(sem->sem_count < 1)
    {
	/*将当前进程挂入等待队列*/
	krlwlst_wait(&sem->sem_waitlst);
	hal_spinunlock_restflg_sti(&sem->sem_lock, &cpufg);
	/*调度并切换到新的进程运行，下次运行时从goto开始*/
	krlschedul();
	/*重新检查信号量*/
	goto start_step;
    }
    sem->sem_count--;
    hal_spinunlock_restflg_sti(&sem->sem_lock, &cpufg);
    return;
}

void krlsem_up(sem_t * sem)
{
    cpuflg_t cpufg;
    hal_spinlock_saveflg_cli(&sem->lock, &cpufg);
    sem->sem_count++;
    if(sem->sem_count < 1)
    {
	/*信号量出了问题*/
	hal_spinunlock_restflg_sti(&sem->sem_lock, &cpufg);
	hal_sysdie("sem up err");
    }
    /*唤醒等待队列上所有进程*/
    krlwlst_allup(&sem->sem_waitlst);
    hal_spinunlock_restflg_sti(&sem->sem_lock, &cpufg);
    /*设置需要调度标志*/
    krlsched_set_schedflgs();
    return;
}
