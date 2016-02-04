/***************************
 * halmm.c 2016.02.04
 * ************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void print_mmapdsc(mach_t * mchp);

void init_halmm()
{
    init_mmapdsc(&osmach);
    init_phymem();
    onmmapdsc_inkrlram(&osmach, &osphymem);
    print_mmapdsc(&osmach);
}

void print_mmapdsc(mach_t * mchp)
{
    mmapdsc_t * map = mchp->mh_mmapdscadr;
    uint_t mnr = mchp->mh_spedscnr;
    for(uint_t i=0; i<mnr; i++)
    {
	printfk("mmapdsc[%x].map_phyadr:0x%x,map_phyadrend:0x%x\n\r", i , \
		(uint_t)map[i].map_phyadr, (uint_t)map[i].map_phyadrend);
    }
    return;
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

/*将内存划分为多个内存块*/
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
    //pmmlist_init(&osmach, &osphymem);
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
    mapp[0].map_allcount = cut;
    mapp[0].map_flg = flg;
    mapdsc_addto_memlst(&pmp->pmm_sz_lsth[0], &mapp[0], ADDT_FUEM_FLG);
    return;
}
