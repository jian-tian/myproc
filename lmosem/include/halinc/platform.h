/***************************
 * platform.h 2016.01.04
 * ************************/
#ifndef _PLATFORM_H
#define _PLATFORM_H

void init_platform();

#ifdef CFG_s3c2440_PLATFORM
LKHEAD_T void s3c2440mmu_init();
LKHEAD_T void s3c2440mmu_invalid_dicache();
LKHEAD_T void s3c2440mmu_set_domain(u32_t domain);
LKHEAD_T void s3c2440mmu_set_tblbass(u32_t tblbphyadr);
LKHEAD_T void s3c2440mmu_enable();
LKHEAD_T void s3c2440vector_init();
LKHEAD_T void s3c2440vector_copy();
extern void vector();
#endif

#endif
