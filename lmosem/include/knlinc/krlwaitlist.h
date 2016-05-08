/*****************************
 * krlwaitlist.h 20160508
 * ***************************/
#ifndef KRL_WAIT_LIST_H
#define KRL_WAIT_LIST_H

void kwlst_t_init(kwlst_t * initp);
void krlwlst_wait(kwlst_t * wlst);
void krlwlst_up(kwlst_t * wlst);
void krlwlst_allup(kwlst_t * wlst);
void krlwlst_add_thread(kwlst_t * wlst, thread_t *tdp);
thread_t * krlwlst_del_thread(kwlst_t * wlst);
#endif
