/***************************
 * lapimm.h 2016.6.14
 * ***********************/
#ifndef LAPIMM_H
#define LAPIMM_H

void * api_mallocblk(size_t blksz);
sysstus_t api_mfreeblk(void * fradr, size_t blksz);
void test_api();

#endif
