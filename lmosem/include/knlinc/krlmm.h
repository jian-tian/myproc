/*********************
 * krlmm.h 2016.03.03
 * ******************/
#ifndef _KRLMM_H
#define _KRLMM_H

void init_krlmm();
adr_t krlnew(size_t mmsize);
bool_t krldelete(adr_t fradr, size_t frsz);

#endif
