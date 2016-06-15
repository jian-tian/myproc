/************************
 * libmm.h 2016.6.14
 * *********************/
#ifndef LIBMM_H
#define LIBMM_H

void *mallocblk(size_t blksz);
sysstus_t mfreeblk(void * fradr, size_t blksz);

#endif
