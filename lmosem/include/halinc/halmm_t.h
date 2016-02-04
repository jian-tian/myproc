/***************
 * halmm_t.h
 * ************/
#ifndef _HALMM_T_H
#define _HALMM_T_H

#define DEV_TYPE_NOT	0xfffffff
#define ADRSPCE_NOT	0
#define ADRSPCE_IO	1
#define ADRSPCE_SDRAM	2
#define ADRSPCE_RAM	3
#define ADRSPCE_ROM	4
#define ADRSPCE_NORFLASH    5
#define ADRSPCE_NANDFLASH   6

#define MAPF_SZ_BIT	0
#define MAPF_ACSZ_BIT	4
#define MAPF_SZ_16KB	(1<<MAPF_SZ_BIT)
#define MAPF_SZ_32KB	(2<<MAPF_SZ_BIT)
#define MAPF_SZ_4MB	(8<<MAPF_SZ_BIT)

#define MAPF_ACSZ_128KB	(1<<MAPF_ACSZ_BIT)
#define MAPF_ACSZ_256KB	(2<<MAPF_ACSZ_BIT)
#define MAPF_ACSZ_512KB	(3<<MAPF_ACSZ_BIT)
#define MAPF_ACSZ_1MB	(4<<MAPF_ACSZ_BIT)
#define MAPF_ACSZ_2MB	(5<<MAPF_ACSZ_BIT)
#define MAPF_ACSZ_4MB	(6<<MAPF_ACSZ_BIT)

#define MAPONE_SIZE	(0x400000)
#define MAP_FLAGS_VAL(RV,SALLOCSZ,MSZ)	(RV|SALLOCSZ|MSZ)

#define ADDT_EMTP_FLG	1
#define ADDT_FUEM_FLG	2
#define ADDT_FULL_FLG	3

#define BLK128KB_SIZE	(0x20000)
#define BLK256KB_SIZE	(0x40000)
#define BLK512KB_SIZE	(0x80000)
#define BLK1MB_SIZE	(0x100000)
#define BLK2MB_SIZE	(0x200000)
#define BLK4MB_SIZE	(0x400000)

#define BLK128KB_BITL	(32)
#define BLK256KB_BITL	(16)
#define BLK512KB_BITL	(8)
#define BLK1MB_BITL	(4)
#define BLK2MB_BITL	(2)
#define BLK4MB_BITL	(1)

#define BLK128KB_MASK	(0xFFFFFFFF)
#define BLK256KB_MASK	(0xFFFF)
#define BLK512KB_MASK	(0xFF)
#define BLK1MB_MASK	(0xF)
#define BLK2MB_MASK	(0x3)
#define BLK4MB_MASK	(0x1)

#define BLKSZ_HEAD_MAX	6

typedef struct s_PHYADRSPEC
{
    u32_t ap_flgs;
    u32_t ap_devtype;
    adr_t ap_adrstart;
    adr_t ap_adrend;
}phyadrspce_t;

/*表示内存空间状态的数据结构*/
typedef struct s_MMAPDSC
{
    list_h_t	map_list;
    spinlock_t	map_lock;
    adr_t	map_phyadr;
    adr_t	map_phyadrend;
    u32_t	map_allcount;
    u32_t	map_flg;
}mmapdsc_t;

/*同种大小内存管理链表*/
typedef struct s_ALCFRELST
{
    spinlock_t	afl_lock;
    size_t	afl_sz;
    list_h_t	afl_fulllsth;
    list_h_t	afl_emptlsth;
    list_h_t	afl_fuemlsth;
}alcfrelst_t;

/*所有RAM空间的数据管理*/
typedef struct s_PHYMEM
{
    list_h_t	pmm_list;
    spinlock_t	pmm_lock;
    uint_t	freeblks;
    uint_t	allcblks;
    alcfrelst_t	pmm_sz_lsth[BLKSZ_HEAD_MAX];
}phymem_t;

#endif
