/**********************************
 * krlsched.h 2016.04.12
 * *******************************/
#ifndef KRLSCHED_H
#define KRLSCHED_H

void thrdlst_t_init(thrdlst_t * initp);
void schdata_t_init(schdata_t * initp);
void schedclass_t_init(schedclass_t * initp);
void init_krlsched();
thread_t * krlsched_retn_currthread();
void krlsched_wait(kwlst_t * wlst);
void krlsched_up(kwlst_t * wlst);
void krlsched_set_schedflgs();
void krlsched_chkneed_pmptsched();
thread_t * krlsched_select_thread();
void krlschedul();
void krlschdclass_add_thread(thread_t * thdp);
void __to_new_context(thread_t * next, thread_t * prev);
void save_to_new_context(thread_t * next, thread_t * prev);
void retnfrom_first_sched(thread_t * thrdp);

#endif
