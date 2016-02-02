/********************************
 *  s3c2440平台相关的宏定义文件platform_t.h
 ********************************/

#ifndef _PLATFORM_T_H
#define _PLATFORM_T_H

#ifdef CFG_s3c2440_PLATFORM

#define CPUCORE_MAX 1
#define SDRAM_MAPVECTPHY_ADDR	0x30000000
#define KRNL_INRAM_START    0x30008000
#define LINK_VIRT_ADDR	    0x30008000
#define LINK_LINE_ADDR	    0x30008000
#define KERNEL_VIRT_ADDR    0x30008000
#define KERNEL_PHYI_ADDR    0x30008000
#define PAGE_TLB_DIR	    0x30004000
#define PAGE_TLB_SIZE	    4096
//#define INIT_HEAD_STACK_ADDR	0x30100000
#define INIT_HEAD_STACK_ADDR	0x34000000

#define CPU_VECTOR_PHYADR   0x30000000
#define CPU_VECTOR_VIRADR   0

#define PTE_SECT_AP	    (3<<10)
#define PTE_SECT_DOMAIN	    (0<<5)
#define PTE_SECT_NOCW	    (0<<2)
#define PTE_SECT_BIT	    (2)

#define PLEM_ADRSPCE_NR	    (29)

#define INTSRC_MAX	    32

#endif

#endif
 
