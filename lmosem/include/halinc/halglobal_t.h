/*************************
 * halglobal_t.h 2016.01.24
 * **********************/
#ifndef _HALGLOBAL_T_H
#define _HALGLOBAL_T_H

#define HAL_DEFGLOB_VARIABLE(vartype, varname) \
EXTERN __attribute__((section(".data"))) vartype varname

#endif
