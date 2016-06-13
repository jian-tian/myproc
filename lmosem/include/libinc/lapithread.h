/**********************
 * lapithread.h 2016.6.13
 * ********************/
#ifndef LAPITHREAD_H
#define LAPITHREAD_H

hand_t api_exel_thread(void * file, uint_t flgs);
void api_exit_thread();
hant_t api_retn_threadhand(void * tname);
sysstus_t api_retn_threadstats(hand_t thand, uint_t scode, uint_t data, buf_t buf);
sysstus_t api_set_threadstats(hant_t thand, uint_t scode, uint_t data, buf_t buf);

#endif
