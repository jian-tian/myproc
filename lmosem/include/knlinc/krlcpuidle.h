/**************************
 * krlcpuidle.h 2016.04.14
 * ***********************/
#ifndef KRLCPUIDLE_H
#define KRLCPUIDLE_H

void init_krlcpuidle();
void krlcpuidle_start();
thread_t * new_cpuidle_thread();
void new_cpuidle();
void krlcpuidle_main();

#endif
