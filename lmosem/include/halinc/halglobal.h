/*********************
 * halglobal.h 2016.01.24
 * ******************/
#ifndef HALGLOBAL_H_
#define HALGLOBAL_H_

#ifdef HALGLOBAL_HAED
#undef EXTERN
#define EXTERN
#endif

HAL_DEFGLOB_VARIABLE(mach_t, osmach);
HAL_DEFGLOB_VARIABLE(phymem_t, osphymem);

HAL_DEFGLOB_VARIABLE(phyadrspce_t, machadrspce)[PLFM_ADRSPCE_NR];
HAL_DEFGLOB_VARIABLE(intfltdsc_t, machintflt)[IRQ_MAX];

#endif
