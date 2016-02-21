/***************************
 * halmm.c 2016.02.04
 * ************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void print_mmapdsc(mach_t * mchp);
void print_mminfo(phymem_t * pmp);
void testblkalloc();
void test_blkmm();

/*初始化完成后，内存分为4M大小blk；其中第一个blk细分为128KB，其余blk细分为4MB*/
/*128KB blk第一个已经给kernel使用；4MB blk为空*/
void init_halmm()
{
    init_mmapdsc(&osmach);
    init_phymem();
    onmmapdsc_inkrlram(&osmach, &osphymem);
    print_mmapdsc(&osmach);
    print_mminfo(&osphymem);
    //testblkalloc();
    test_blkmm();
}

void print_mmapdsc(mach_t * mchp)
{
    mmapdsc_t * map = mchp->mh_mmapdscadr;
    uint_t mnr = mchp->mh_mmapdscnr;
    for(uint_t i=0; i<mnr; i++)
    {
	printfk("mmapdsc[%x].map_phyadr:0x%x,map_phyadrend:0x%x\n\r", i , \
		(uint_t)map[i].map_phyadr, (uint_t)map[i].map_phyadrend);
    }
    return;
}

void print_mminfo(phymem_t * pmp)
{
    uint_t blkcnt = BLKSZ_HEAD_MAX;
    uint_t lscnt = 3;
    mmapdsc_t *mmap;
    list_h_t *pos;
    list_h_t *lsth;

    for(uint_t i=0; i< blkcnt; i++)
    {
	switch(i)
	{
	    case 0:
		printfk("blk 128KB is:\r\n");
		break;
	    case 1:
		printfk("blk 256KB is:\r\n");
		break;
	    case 2:
		printfk("blk 512KB is:\r\n");
		break;
	    case 3:
		printfk("blk 1MB is:\r\n");
		break;
	    case 4:
		printfk("blk 2MB is:\r\n");
		break;
	    case 5:
		printfk("blk 4MB is:\r\n");
		break;
	    default:
		break;
	}

	for(uint_t j=0; j<lscnt; j++)
	{
	    if(j==0)
	    {
		printfk("  full blk is:\r\n");
		lsth = &pmp->pmm_sz_lsth[i].afl_fulllsth;
	    }	
	    else if(j==1)
	    {
		printfk("  empty blk is:\r\n");
		lsth = &pmp->pmm_sz_lsth[i].afl_emptlsth;
	    }
	    else
	    {
		printfk("  part blk is:\r\n");
		lsth = &pmp->pmm_sz_lsth[i].afl_fuemlsth;
	    }
	    list_for_each(pos, lsth)
	    {
		//printfk("pos is 0x%x, lsth is 0x%x\r\n", pos, lsth);
		//printfk("pos->next is 0x%x, lsth->next is 0x%x\r\n", pos->next, (lsth)->next);
		mmap = list_entry(pos, mmapdsc_t, map_list);	
		printfk("\tmap_phyadr is 0x%x\r\n", mmap->map_phyadr);
		printfk("\tmap_phyadrend is 0x%x\r\n", mmap->map_phyadrend);
		printfk("\tmap_allcount is 0x%x\r\n", mmap->map_allcount);
		printfk("\tmap_flg is 0x%x\r\n", mmap->map_flg);
	    }
	}
    } 
}

/*初始化存储空间*/
void init_mmapdsc(mach_t * mahp)
{
    phyadrspce_t * adsp = mahp->mh_spedsc;
    uint_t spnr = mahp->mh_spedscnr;
    uint_t mindx = 0;

    for(uint_t i=0; i<spnr; i++)
    {
	if(adsp[i].ap_flgs == ADRSPCE_SDRAM)
	{
	    mindx = init_core_mmapdsc(adsp[i].ap_adrstart, adsp[i].ap_adrend, mahp->mh_mmapdscadr, mindx);
	}
    }
    mahp->mh_mmapdscnr = mindx;
    mahp->mh_kerinramend = (adr_t)((uint_t)mahp->mh_mmapdscadr + (sizeof(mmapdsc_t)*mindx));
    return;
}

/*将内存按4MB大小划分为多个内存块*/
uint_t init_core_mmapdsc(adr_t adrs, adr_t adre, mmapdsc_t * gmmp, uint_t curmindx)
{
    uint_t mindx = curmindx;
    adr_t tmpadr = adre;

    for(;adrs < adre; adrs+=MAPONE_SIZE,mindx++)
    {
	if((adrs + MAPONE_SIZE)<adre)
	{
	    tmpadr = (adrs + MAPONE_SIZE) - 1;
	}
	else
	{
	    tmpadr = adre;
	}
	mmapdsc_t_init(&gmmp[mindx], adrs, tmpadr, 0, MAP_FLAGS_VAL(0, MAPF_ACSZ_4MB, MAPF_SZ_4MB));
    }
    return mindx;
}

/*单个内存块*/
void mmapdsc_t_init(mmapdsc_t * mmp, adr_t phyadrs, adr_t phyadre, u32_t allcount, u32_t flgs)
{
    list_init(&mmp->map_list);
    hal_spinlock_init(&mmp->map_lock);
    mmp->map_phyadr = phyadrs;
    mmp->map_phyadrend = phyadre;
    mmp->map_allcount = allcount;
    mmp->map_flg = flgs;
    return;
}

void init_phymem()
{
    phymem_t_init(&osphymem);
    //print_mminfo(&osphymem);
    pmmlist_init(&osmach, &osphymem);
}

/*初始化时把4-64的内存划分到4M的链表中，即这些内存blk没有再细分*/
void pmmlist_init(mach_t * mahp, phymem_t * pmp)
{
    mmapdsc_t * mapp = mahp->mh_mmapdscadr;
    uint_t mapnr = mahp->mh_mmapdscnr;
    for(uint_t mr=1; mr< mapnr; mr++)
    {
	mapdsc_addto_memlst(&pmp->pmm_sz_lsth[BLKSZ_HEAD_MAX-1], &mapp[mr], ADDT_EMTP_FLG);
    }
    return;
}

void alcfrelst_t_init(alcfrelst_t * initp, size_t bsz)
{
    hal_spinlock_init(&initp->afl_lock);
    initp->afl_sz = bsz;
    list_init(&initp->afl_fulllsth);
    list_init(&initp->afl_emptlsth);
    list_init(&initp->afl_fuemlsth);
    return;
}

/*初始化内存分配结构体，开始时还没有可用的内存保存*/
void phymem_t_init(phymem_t * initp)
{
    list_init(&initp->pmm_list);
    hal_spinlock_init(&initp->pmm_lock);
    alcfrelst_t_init(&initp->pmm_sz_lsth[0], BLK128KB_SIZE);
    alcfrelst_t_init(&initp->pmm_sz_lsth[1], BLK256KB_SIZE);
    alcfrelst_t_init(&initp->pmm_sz_lsth[2], BLK512KB_SIZE);
    alcfrelst_t_init(&initp->pmm_sz_lsth[3], BLK1MB_SIZE);
    alcfrelst_t_init(&initp->pmm_sz_lsth[4], BLK2MB_SIZE);
    alcfrelst_t_init(&initp->pmm_sz_lsth[5], BLK4MB_SIZE);
}

void mapdsc_addto_memlst(alcfrelst_t * aflp, mmapdsc_t * mmp, uint_t aftflg)
{
    switch(aftflg)
    {
	case ADDT_EMTP_FLG:
	    list_add_tail(&mmp->map_list, &aflp->afl_emptlsth);
	    break;
	case ADDT_FUEM_FLG:
	    list_add_tail(&mmp->map_list, &aflp->afl_fuemlsth);
	    break;
	case ADDT_FULL_FLG:
	    list_add_tail(&mmp->map_list, &aflp->afl_fulllsth);
	    break;
	default:
	    break;
    }
    return;
}

/*第一个4Mblk中按128KB划分，第一个blk作为kernel表示已经使用的地址,加到128kb的链表中*/
void onmmapdsc_inkrlram(mach_t * mahp, phymem_t * pmp)
{
    mmapdsc_t * mapp = mahp->mh_mmapdscadr;
    adr_t ker_r_s = mahp->mh_kerinramstart;
    adr_t ker_r_e = mahp->mh_kerinramend;

    if((ker_r_e - ker_r_s) > BLK128KB_SIZE || ker_r_s < mapp[0].map_phyadr)
    {
	hal_sysdie("onmmapdsc_inkrlram err");
    }

    u32_t cut = 1;
    u32_t flg = MAP_FLAGS_VAL(0, MAPF_ACSZ_128KB, MAPF_SZ_4MB);
    mapp[0].map_allcount = cut;/*表示第cut个blk已经分配*/
    mapp[0].map_flg = flg;
    mapdsc_addto_memlst(&pmp->pmm_sz_lsth[0], &mapp[0], ADDT_FUEM_FLG);
    return;
}

adr_t hal_memallocblks(size_t blksz)
{
    if(blksz < BLK128KB_SIZE || blksz > BLK4MB_SIZE)
    {
	return NULL;
    }

    return hal_memallocblks_core(blksz);
}

alcfrelst_t * hal_onblksz_findalcfrelst(alcfrelst_t ** retalcfrl, size_t * retalcsz, size_t blksz)
{
    phymem_t * memp = &osphymem;
    alcfrelst_t * aftp = NULL;
    alcfrelst_t * aft4mbp = &memp->pmm_sz_lsth[BLKSZ_HEAD_MAX - 1];
    for(uint_t bj=0; bj<BLKSZ_HEAD_MAX; bj++)
    {
	if(memp->pmm_sz_lsth[bj].afl_sz == blksz)
	{
	    aftp = &memp->pmm_sz_lsth[bj];
	    *retalcfrl = aftp;
	    *retalcsz = memp->pmm_sz_lsth[bj].afl_sz;
	    goto next_step;
	}
    }
    aftp = NULL;
    *retalcfrl = NULL;
    *retalcsz = 0;
next_step:
    if(!aftp)
    {
	return NULL;
    }
    if(list_is_empty_careful(&aftp->afl_emptlsth)==FALSE)
    {
	return aftp;
    }
    if(list_is_empty_careful(&aftp->afl_fuemlsth)==FALSE)
    {
	return aftp;
    }
    aftp = aft4mbp;
    if(list_is_empty_careful(&aftp->afl_emptlsth)==FALSE)
    {
	return aftp;
    }
    return NULL;
}

adr_t hal_onalcfrel_allocblks(alcfrelst_t * allclh, alcfrelst_t * relalch, size_t relalcsz)
{
    adr_t retadr = NULL;
    switch(relalcsz)
    {
	case BLK128KB_SIZE:
	    retadr = hal_onmapdsc_allcblks(MAPF_ACSZ_128KB, BLK128KB_MASK, BLK128KB_BITL, allclh, relalch);
	    break;
	case BLK256KB_SIZE:
	    retadr = hal_onmapdsc_allcblks(MAPF_ACSZ_256KB, BLK256KB_MASK, BLK256KB_BITL, allclh, relalch);
	    break;
	case BLK512KB_SIZE:
	    retadr = hal_onmapdsc_allcblks(MAPF_ACSZ_512KB, BLK512KB_MASK, BLK512KB_BITL, allclh, relalch);
	    break;
	case BLK1MB_SIZE:
	    retadr = hal_onmapdsc_allcblks(MAPF_ACSZ_1MB, BLK1MB_MASK, BLK1MB_BITL, allclh, relalch);
	    break;
	case BLK2MB_SIZE:
	    retadr = hal_onmapdsc_allcblks(MAPF_ACSZ_2MB, BLK2MB_MASK, BLK2MB_BITL, allclh, relalch);
	    break;
	case BLK4MB_SIZE:
	    retadr = hal_onmapdsc_allcblks(MAPF_ACSZ_4MB, BLK4MB_MASK, BLK4MB_BITL, allclh, relalch);
	    break;
	default:
	    retadr = NULL;
	    break;
    }
    return retadr;
}

/*在allclh中查找下一个有效的mmapdsc_t，没有返回空*/
mmapdsc_t * hal_onalfl_findmapdsc(alcfrelst_t * allclh)
{
    mmapdsc_t * mp = NULL;
    if(list_is_empty_careful(&allclh->afl_fuemlsth) == FALSE)
    {
	mp = list_entry(allclh->afl_fuemlsth.next, mmapdsc_t, map_list);
	return mp;
    }/*先找非满队列，然后找空队列*/
    if(list_is_empty_careful(&allclh->afl_emptlsth) == FALSE)
    {
	mp = list_entry(allclh->afl_emptlsth.next, mmapdsc_t, map_list);
	return mp;
    }
    return NULL;
}

adr_t hal_onmapdsc_allcblks(u32_t mflg, u32_t mask, u32_t bitls, alcfrelst_t * aflp, alcfrelst_t * mvtoaflp)
{
    adr_t retadr = NULL;
    mmapdsc_t * map = NULL;
    uint_t bi = 0;
    u32_t fg = 0xffffff0f;
    if(bitls > 32)
    {
	return NULL;
    }

    map = hal_onalfl_findmapdsc(aflp);
    if(!map)
    {
	return NULL;
    }

    for(; bi<bitls; bi++)
    {
	if(((map->map_allcount>>bi)&1)==0)
	    goto next_step;
    }
    bi = 0xffffffff;
next_step:
    if(bi == 0xffffffff)
	return NULL;
    /*计算返回地址，并且做合法性检查*/
    retadr = map->map_phyadr + (mvtoaflp->afl_sz * bi);
    if(retadr<map->map_phyadr || retadr >=map->map_phyadrend)
	return NULL;
    /*将map_allcount中对应bi位置1，表示已经分配*/
    (map->map_allcount) |= (1<<bi);
    /*清除mmapdsc_t中的标志位*/
    (map->map_flg) &= fg;
    /*设置新的标志位，该标志位表示其中内存细分大小的位*/
    (map->map_flg) |= mflg;
    //如果分配后map_allcount中的位和mask码相等，表示其中没有空闲内存块了，所以需要移动到
    //mvtoaflp->afl_fulllsth队中去
    if((map->map_allcount & mask) == mask)
    {
	list_move_tail(&map->map_list, &mvtoaflp->afl_fulllsth);
	return retadr;
    }
    //否则移动到mvtoaflp->afl_fuemlsth队列中去
    list_move_tail(&map->map_list, &mvtoaflp->afl_fuemlsth);
    return retadr;
}

adr_t hal_memallocblks_core(size_t blksz)
{
    phymem_t * memp = &osphymem;
    size_t retbsz = 0;
    cpuflg_t cpuflg;
    adr_t retadr = NULL;
    alcfrelst_t	* allcflp = NULL;
    alcfrelst_t * aftp = NULL;
    hal_spinlock_saveflg_cli(&memp->pmm_lock, &cpuflg);
    /*allcflp存储想找的alcfrelst_t, aftp表示实际找到的，二者可能不一致*/
    aftp = hal_onblksz_findalcfrelst(&allcflp, &retbsz, blksz);
    if(aftp == NULL || allcflp == NULL || retbsz == 0)
    {
	retadr = NULL;
	goto return_step;
    }
    //afl_sz == retbsz 表示在已有的链表中找到
    //afl_sz = 4MB 表示需要已有的链表中没有，需要将一块4MB的内存细分
    if(aftp->afl_sz != retbsz && aftp->afl_sz != BLK4MB_SIZE)
    {
	retadr = NULL;
	goto return_step;
    }
    retadr = hal_onalcfrel_allocblks(aftp, allcflp, retbsz);
return_step:
    hal_spinunlock_restflg_sti(&memp->pmm_lock, &cpuflg);
    return retadr; 
}

void testblkalloc()
{
    size_t ablksz = 0;
    adr_t retadr = NULL;
    for(uint_t bli = 0; bli<6; bli++)
    {
	ablksz = BLK128KB_SIZE << bli;
	for(uint_t i=0; i<2; i++)
	{
	    retadr = hal_memallocblks(ablksz);
	    if(!retadr)
	    {
		hal_sysdie("NOT MEMBLK;return NULL");
	    }
	    printfk("allocblksz:%x return adrr:%x \n\r", ablksz, retadr);
	}
    }
}

bool_t hal_memfreeblks(adr_t freadr, size_t blksz)
{
    if(freadr == NULL || blksz < BLK128KB_SIZE || blksz >BLK4MB_SIZE)
    {
	return FALSE;
    }

    return hal_memfreeblks_core(freadr, blksz);
}

bool_t hal_memfreeblks_core(adr_t frebadr, size_t blksz)
{
    phymem_t * memp=&osphymem;
    bool_t retstus = FALSE;
    cpuflg_t cpuflg;
    alcfrelst_t * aftp = NULL;
    alcfrelst_t * mvtoaflp = &memp->pmm_sz_lsth[BLKSZ_HEAD_MAX-1];
    hal_spinlock_saveflg_cli(&memp->pmm_lock, &cpuflg);
    for(uint_t fi=0; fi<BLKSZ_HEAD_MAX; fi++)
    {
	if(memp->pmm_sz_lsth[fi].afl_sz == blksz)
	{
	    aftp = &memp->pmm_sz_lsth[fi];
	    goto next_step;
	}
    }
    aftp = NULL;
next_step:
    if(aftp == NULL)
    {
	retstus = FALSE;
	goto return_step;
    } 
    retstus = hal_onalcfre_freeblks(frebadr, aftp, mvtoaflp, blksz);
return_step:
    hal_spinunlock_restflg_sti(&memp->pmm_lock, &cpuflg);
    return retstus;
}

bool_t hal_onalcfre_freeblks(adr_t freadr, alcfrelst_t * allclh, alcfrelst_t * mvaflh, size_t relalcsz)
{
    bool_t retstus = FALSE;
    switch(relalcsz)
    {
	case BLK128KB_SIZE:
	    retstus = hal_onmapdsc_freeblks(freadr, MAPF_ACSZ_4MB, BLK128KB_MASK, allclh, mvaflh);
	    break;
	case BLK256KB_SIZE:
	    retstus = hal_onmapdsc_freeblks(freadr, MAPF_ACSZ_4MB, BLK256KB_MASK, allclh, mvaflh);
	    break;
	case BLK512KB_SIZE:
	    retstus = hal_onmapdsc_freeblks(freadr, MAPF_ACSZ_4MB, BLK512KB_MASK, allclh, mvaflh);
	    break;
	case BLK1MB_SIZE:
	    retstus = hal_onmapdsc_freeblks(freadr, MAPF_ACSZ_4MB, BLK1MB_MASK, allclh, mvaflh);
	    break;
	case BLK2MB_SIZE:
	    retstus = hal_onmapdsc_freeblks(freadr, MAPF_ACSZ_4MB, BLK2MB_MASK, allclh, mvaflh);
	    break;
	case BLK4MB_SIZE:
	    retstus = hal_onmapdsc_freeblks(freadr, MAPF_ACSZ_4MB, BLK4MB_MASK, allclh, mvaflh);
	    break;
	default:
	    retstus = FALSE;
	    break;
    }
    return retstus;
}

bool_t hal_onmapdsc_freeblks(adr_t frebadr, u32_t mflg, u32_t mask, alcfrelst_t * aflp, alcfrelst_t * mvtoaflp)
{
    mmapdsc_t * map = NULL;
    uint_t bitnr;
    u32_t fg = 0xffffff0f;
    /*根据内存空间地址和所在aflp结构，找到mmapdsc_t结构体*/
    map = hal_free_findmapdsc(frebadr, aflp);
    if(map == NULL)
	return FALSE;
    /*根据内存空间块地址计算该空间在map_allcount中的bit位*/
    bitnr = (uint_t)(frebadr-map->map_phyadr)/(uint_t)(aflp->afl_sz);
    if(bitnr > 31)
	return FALSE;
    /*检查对应的bit位是否为0*/
    if(((map->map_allcount>>bitnr)&1)!=1)
	return FALSE;
    /*对应bit位清0，表示空间释放*/
    (map->map_allcount) &= (~(1<<bitnr));
    /*如果map_allcount所有bit都为0，表示一整块空闲内存，需要将该
      mmapdsc 移动到最后一个alcfrelst_t 中*/
    if((map->map_allcount & mask) == 0)
    {
	map->map_flg &= fg;
	map->map_flg |= mflg;
	list_move(&map->map_list, &mvtoaflp->afl_emptlsth);
    }
    return TRUE;
}

mmapdsc_t * hal_free_findmapdsc(adr_t frebadr, alcfrelst_t * allclh)
{
    mmapdsc_t * mp = NULL;
    list_h_t * tmplst = NULL;
    if(list_is_empty_careful(&allclh->afl_fuemlsth) == FALSE)
    {
	list_for_each(tmplst, &allclh->afl_fuemlsth)
	{
	    mp = list_entry(tmplst, mmapdsc_t, map_list);
	    if(frebadr < mp->map_phyadrend && frebadr >= mp->map_phyadr)
	    {
		return mp;
	    }
	}
    }
    if(list_is_empty_careful(&allclh->afl_fulllsth) == FALSE)
    {
	list_for_each(tmplst, &allclh->afl_fulllsth)
	{
	    mp = list_entry(tmplst, mmapdsc_t, map_list);
	    if(frebadr < mp->map_phyadrend && frebadr >= mp->map_phyadr)
	    {
		return mp;
	    }
	}
    }
    return NULL;
}

void test_blkmm()
{
    adr_t retadra[14];
    adr_t retadr = 0;
    adr_t retadrold = 0;
    adr_t retadrend = 0;
    size_t ablksz = 0;
    bool_t retstus = FALSE;

    retadrold = hal_memallocblks(BLK128KB_SIZE);
    if(!retadrold)
	hal_sysdie("blkalloc 128KB failed, return NULL\n\r");
    if(hal_memfreeblks(retadrold, BLK128KB_SIZE) == FALSE)
	hal_sysdie("blkfree 128KB failed, return NULL\n\r");

    for(uint_t bli=0; bli<6; bli++)
    {
	ablksz = BLK128KB_SIZE<<bli;
	for(uint_t i=0; i<14; i++)
	{
	    retadr = hal_memallocblks(ablksz);
	    if(!retadr)
		hal_sysdie("blkalloc failed");
	    printfk("allocblksz:%x return adrr:%x \n\r",ablksz, retadr);
	    retadra[i] = retadr;
	}
	for(uint_t j=0; j<14; j++)
	{
	    retstus = hal_memfreeblks(retadra[j], ablksz);
	    if(retstus == FALSE)
		hal_sysdie("blkfree failed");
	    printfk("freeblksz:%x free adrr:%x\n\r", ablksz, retadra[j]);
	}
    }
    retadrend = hal_memallocblks(BLK128KB_SIZE);
    if(!retadrend)
	hal_sysdie("blkalloc 128 failed");
    if(retadrend == retadrold)
	printfk("Test blkmm OK!!\n\r");

    return;
}
