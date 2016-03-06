/***********************
 * krlpagempol.c 2016.02.26
 * ********************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

typedef struct s_adrsz
{
    adr_t adr;
    size_t sz;
}adrsz_t;

/*alloc 地址范围比较*/
void cmp_adrsz(adrsz_t * assp, uint_t nr)
{
    uint_t i,j;
    for(i=0; i<nr; i++)
    {
	for(j=0; j<nr; j++)
	{
	    if(i != j)
	    {
		if(assp[i].adr == assp[j].adr)
		{
		    hal_sysdie("cmp adr start err");
		}
	    }
	}
    }
    for(i=0; i<nr; i++)
    {
	for(j=0; j<nr; j++)
	{
	    if(i != j)
	    {
		if(assp[i].adr + assp[i].sz == assp[j].adr + assp[j].sz)
		{
		    hal_sysdie("cmp adr end err");
		}
	    }
	}
    }
    for(i=0; i<nr; i++)
    {
	for(j=0; j<nr; j++)
	{
	    if(i != j)
	    {
		if((assp[i].adr >= assp[j].adr) && ((assp[i].adr + assp[i].sz) <= assp[j].adr + assp[j].sz))
		{
		    hal_sysdie("cmp adr in err");
		}
	    }
	}
    }
    return;
}

void testpagemgr()
{
#define TEST_COUNT 2
    adrsz_t adsz[TEST_COUNT];
    size_t alcsz = 0x1000;
    uint_t i;
    for(; alcsz < 0x19000; alcsz += 0x1000)
    {
	/*分配空间*/
	for(i=0; i<TEST_COUNT; i++)
	{
	    adsz[i].sz = alcsz;
	    adsz[i].adr = kmempool_new(alcsz);
	    if(adsz[i].adr == NULL)
	    {
		hal_sysdie("testpagemgr kmempool_new err");
	    }
	    printfk("adsz[%d] sz: 0x%x adr: 0x%x\n\r", i, adsz[i].sz, adsz[i].adr); 
	}
	/*比较*/
	 cmp_adrsz(adsz, TEST_COUNT);
	/*释放空间*/
	for(i = 0; i<TEST_COUNT; i++)
	{
	    if(kmempool_delete(adsz[i].adr, adsz[i].sz) == FALSE)
	    {
		hal_sysdie("testpagemgr kmempool_delete err");
	    }
	    printfk("delete adsz[%d] sz: 0x%x adr: 0x%x\n\r", i, adsz[i].sz, adsz[i].adr); 
	}
    }
    printfk("oskmempool.mp_pgmplnr: 0x%x\n\r", oskmempool.mp_pgmplnr);
    return;
}

void testpgmpool()
{
    adrsz_t adsz[10];
    size_t alcsz = 0x1000;
    adsz[0].sz = alcsz;
    adsz[0].adr = kmempool_new(alcsz);
    adsz[1].sz = alcsz;
    adsz[1].adr = kmempool_new(alcsz);
    alcsz = 0x1500;
    adsz[2].sz = alcsz;
    adsz[2].adr = kmempool_new(alcsz);
    adsz[3].sz = alcsz;
    adsz[3].adr = kmempool_new(alcsz);
    alcsz = 0x3000;
    adsz[4].sz = alcsz;
    adsz[4].adr = kmempool_new(alcsz);
    adsz[5].sz = alcsz;
    adsz[5].adr = kmempool_new(alcsz);
    alcsz = 0x3200;
    adsz[6].sz = alcsz;
    adsz[6].adr = kmempool_new(alcsz);
    adsz[7].sz = alcsz;
    adsz[7].adr = kmempool_new(alcsz);
    alcsz = 0x7000;
    adsz[8].sz = alcsz;
    adsz[8].adr = kmempool_new(alcsz);
    adsz[9].sz = alcsz;
    adsz[9].adr = kmempool_new(alcsz);

    for(int i=0; i<10; i++)
    {
	printfk("adsz[%d] sz: 0x%x adr: 0x%x\n\r", i, adsz[i].sz, adsz[i].adr); 
    }

    mplhead_t * retmhp;
    list_h_t * list;
    list_for_each(list, &oskmempool.mp_pgmplmheadl)
    {
	retmhp = list_entry(list, mplhead_t, mh_list);
	printfk("mph_t_adr:0x%x mph_t.mh_end:0x%x mph_t.mh_objsz:0x%x mph_t.mh_objnr:0x%x\n\r", retmhp, retmhp->mh_end, retmhp->mh_objsz, retmhp->mh_objnr);
    }

    return;
}

void init_krlpagempol()
{
    kmempool_t_init(&oskmempool);
    return; 
}

void kmempool_t_init(kmempool_t * initp)
{
    hal_spinlock_init(&initp->mp_lock);
    list_init(&initp->mp_list);
    initp->mp_stus = 0;
    initp->mp_flgs = 0;
    hal_spinlock_init(&initp->mp_pglock);
    hal_spinlock_init(&initp->mp_oblock);
    initp->mp_pgmplnr = 0;
    initp->mp_obmplnr = 0;
    list_init(&initp->mp_pgmplmheadl);
    list_init(&initp->mp_obmplmheadl);
    initp->mp_pgmplmhcach = NULL;
    initp->mp_obmplmhcach = NULL;
    return;
}

adr_t kmempool_new(size_t msize)
{
    //printfk("%s\n\r", __func__);
    if(msize < KMEMPALCSZ_MIN || msize > KMEMPALCSZ_MAX)
	return NULL;

    return kmempool_onsize_new(msize);
}

bool_t kmempool_delete(adr_t fradr, size_t frsz)
{
    //printfk("%s\n\r", __func__);
    if(fradr == NULL || frsz < KMEMPALCSZ_MIN || frsz > KMEMPALCSZ_MAX)
	return NULL;

    return kmempool_onsize_delete(fradr, frsz);
}

adr_t kmempool_onsize_new(size_t msize)
{
    //printfk("%s\n\r", __func__);
    if(msize > OBJSORPAGE)
	return kmempool_pages_new(msize);

    return kmempool_objsz_new(msize);
}

adr_t kmempool_objsz_new(size_t msize)
{
    return NULL;
}

bool_t kmempool_onsize_delete(adr_t fradr, size_t frsz)
{
    //printfk("%s\n\r", __func__);
    if(frsz > OBJSORPAGE)
	return kmempool_pages_delete(fradr, frsz);

    return kmempool_objsz_delete(fradr, frsz);
}

bool_t kmempool_objsz_delete(adr_t fradr, size_t frsz)
{
    return TRUE;
}

adr_t kmempool_pages_new(size_t msize)
{
    //printfk("%s\n\r", __func__);
    size_t sz = PAGE_ALIGN(msize);
    if(sz > KPMPORHALM)
	return kmempool_page_new_callhalmm(sz);

    return kmempool_pages_core_new(sz);
}

bool_t kmempool_pages_delete(adr_t fradr, size_t frsz)
{
    //printfk("%s\n\r", __func__);
    size_t sz = PAGE_ALIGN(frsz);
    if(sz > KPMPORHALM)
	return kmempool_page_delete_callhalmm(fradr, sz);

    return kmempool_pages_core_delete(fradr, sz);
}

adr_t kmempool_page_new_callhalmm(size_t msize)
{
    if(msize <= BLK128KB_SIZE)
	return hal_memallocblks(BLK128KB_SIZE);
    if(msize <= BLK256KB_SIZE)
	return hal_memallocblks(BLK256KB_SIZE);
    if(msize <= BLK512KB_SIZE)
	return hal_memallocblks(BLK512KB_SIZE);
    if(msize <= BLK1MB_SIZE)
	return hal_memallocblks(BLK1MB_SIZE);
    if(msize <= BLK2MB_SIZE)
	return hal_memallocblks(BLK2MB_SIZE);
    if(msize <= BLK4MB_SIZE)
	return hal_memallocblks(BLK4MB_SIZE);

    return NULL;
}

bool_t kmempool_page_delete_callhalmm(adr_t fradr, size_t frsz)
{
    if(frsz <= BLK128KB_SIZE)
	return hal_memfreeblks(fradr, BLK128KB_SIZE);
    if(frsz <= BLK256KB_SIZE)
	return hal_memfreeblks(fradr, BLK256KB_SIZE);
    if(frsz <= BLK512KB_SIZE)
	return hal_memfreeblks(fradr, BLK512KB_SIZE);
    if(frsz <= BLK1MB_SIZE)
	return hal_memfreeblks(fradr, BLK1MB_SIZE);
    if(frsz <= BLK2MB_SIZE)
	return hal_memfreeblks(fradr, BLK2MB_SIZE);
    if(frsz <= BLK4MB_SIZE)
	return hal_memfreeblks(fradr, BLK4MB_SIZE);

    return FALSE;
}

mplhead_t * pagenew_mplhead_isok(mplhead_t * mhp, size_t msize)
{
    if(mhp->mh_firtpmap == NULL)
	return NULL;

    if(mhp->mh_hedty != MPLHTY_PAGE)
	return NULL;

    if(mhp->mh_aliobsz != msize)
	return NULL;

    if(mhp->mh_afindx >= mhp->mh_objnr)
	return NULL;

    return mhp;
}

mplhead_t * pagedel_mplhead_isok(mplhead_t * mhp, adr_t fradr, size_t msize)
{
    if(mhp->mh_hedty != MPLHTY_PAGE)
	return NULL;

    if(mhp->mh_aliobsz != msize)
	return NULL;

    if(mhp->mh_afindx == 0)
	return NULL;

    if(fradr < (mhp->mh_start + PAGE_SIZE) || (fradr + msize - 1) > mhp->mh_end)
    return NULL;

    return mhp;
}

/*在内存池中查找合适大小的mplhead_t结构*/
mplhead_t * kmemplpg_retn_mplhead(kmempool_t * kmplockp, size_t msize)
{
    //printfk("%s %d\n\r", __func__, __LINE__);
    mplhead_t * retmhp;
    list_h_t * list;
    /*检查上次操作的mplhead_t是否符合要求，以缩短查找时间*/
    if(kmplockp->mp_pgmplmhcach != NULL)
    {
	retmhp = kmplockp->mp_pgmplmhcach;
	retmhp = pagenew_mplhead_isok(retmhp, msize);
	if(retmhp != NULL)
	    return retmhp;
    }
    //printfk("%s %d\n\r", __func__, __LINE__);
    /*否则遍历链表，寻址合适结构*/
    list_for_each(list, &kmplockp->mp_pgmplmheadl)
    {
	//printfk("list is 0x%x, list->next is 0x%x\n\r", list, list->next);
	retmhp = list_entry(list, mplhead_t, mh_list);
	retmhp = pagenew_mplhead_isok(retmhp, msize);
	if(retmhp != NULL)
	{
	    kmplockp->mp_pgmplmhcach = retmhp;
	    return retmhp;
	}
    }
    //printfk("%s %d\n\r", __func__, __LINE__);
    return NULL;
}

mplhead_t * kmempldelpg_retn_mplhead(kmempool_t * kmplockp, adr_t fradr, size_t msize)
{
    //printfk("%s\n\r", __func__);
    mplhead_t * retmhp;
    list_h_t * list;

    if(kmplockp->mp_pgmplmhcach != NULL)
    {
	retmhp = kmplockp->mp_pgmplmhcach;
	retmhp = pagedel_mplhead_isok(retmhp, fradr, msize);
	if(retmhp != NULL)
	{
	    return retmhp;
	}
    }
    list_for_each(list, &kmplockp->mp_pgmplmheadl)
    {
	retmhp = list_entry(list, mplhead_t, mh_list);
	retmhp = pagedel_mplhead_isok(retmhp, fradr, msize);
	if(retmhp != NULL)
	{
	    return retmhp;
	}
    }
    return NULL;
}

mplhead_t * new_page_mpool(kmempool_t * kmplockp, size_t msize)
{
    mplhead_t * mphdp = NULL;
    size_t pgnr = msize >> 12;
    adr_t blkadr = NULL;

    if(pgnr < 1)
	return NULL;
    if(pgnr < 2)
    {
	blkadr = hal_memallocblks(BLK128KB_SIZE);
	if(blkadr == NULL)
	    return NULL;
	mphdp = page_mpool_init(kmplockp, (mplhead_t *)blkadr, msize, \
                                blkadr, (blkadr + BLK128KB_SIZE -1));
	if(mphdp == NULL)
	    hal_sysdie("new pg mpool err 1");
	return mphdp;
    }

    if(pgnr <= 31)
    {
	
	blkadr = hal_memallocblks(BLK256KB_SIZE);
	if(blkadr == NULL)
	    return NULL;
	mphdp = page_mpool_init(kmplockp, (mplhead_t *)blkadr, msize, \
                                blkadr, (blkadr + BLK256KB_SIZE -1));
	if(mphdp == NULL)
	    hal_sysdie("new pg mpool err 2");
	return mphdp;
    }
    return NULL;
}

bool_t del_page_mpool(kmempool_t * kmplockp, mplhead_t * mphdp)
{
    if(mphdp->mh_afindx > 0)
	return TRUE;
    size_t frsz = mphdp->mh_end - mphdp->mh_start + 1;
    adr_t fradr = mphdp->mh_start;
    list_del(&mphdp->mh_list);
    if(kmplockp->mp_pgmplnr < 1)
    {
	hal_sysdie("del_page_mpool kmplockp->mp_pgmplnr < 1");
    }
    kmplockp->mp_pgmplnr--;
    /*如果上次使用mphdp,一定要将cach置空*/
    if(kmplockp->mp_pgmplmhcach == mphdp)
    {
	kmplockp->mp_pgmplmhcach = NULL;
    }
    /*删除块内存*/
    if(hal_memfreeblks(fradr, frsz) == NULL)
    {
	hal_sysdie("del_page_mpool hal_memfreeblks err");
    }
    return TRUE;
}

void mplhead_t_init(mplhead_t * initp)
{
    hal_spinlock_init(&initp->mh_lock);
    list_init(&initp->mh_list);
    initp->mh_hedty = 0;
    initp->mh_start = 0;
    initp->mh_end = 0;
    initp->mh_firtfreadr = NULL;
    initp->mh_firtpmap = NULL;
    initp->mh_objnr = 0;
    initp->mh_aliobsz = 0;
    initp->mh_objsz = 0;
    initp->mh_nxtpsz = 0;
    initp->mh_afindx = 0;
    initp->mh_pmnr = 0;
    initp->mh_pmap = (pglmap_t *)(((uint_t)initp) + sizeof(mplhead_t));
    return;
}

mplhead_t * page_mpool_init(kmempool_t * kmplockp, mplhead_t * initp, size_t msize, adr_t start, adr_t end)
{
    if(((start & 0xFFF)!=0 || ((end-start)<(PAGE_SIZE*2)-1)))
	return NULL;

    adr_t sadr = start + PAGE_SIZE;
    uint_t pi=0,pnr=0;

    mplhead_t_init(initp);
    initp->mh_hedty = MPLHTY_PAGE;
    initp->mh_start = start;
    initp->mh_end = end;
    initp->mh_aliobsz = msize;
    initp->mh_objsz = msize;

    for(;;)
    {
	if((sadr+msize-1) > end)
	    break;
	initp->mh_pmap[pi].pgl_start = sadr;
	initp->mh_pmap[pi].pgl_next = &(initp->mh_pmap[pi+1]);
	sadr += msize;
	pi++;
    }
    if(pi > 0)
    {
	initp->mh_pmap[pi-1].pgl_next = NULL;
	pnr = pi;
	initp->mh_firtpmap = &(initp->mh_pmap[0]);
	goto add_step;
    }
    initp->mh_pmap[pi].pgl_next = NULL;
    initp->mh_pmap[pi].pgl_start = NULL;
    pnr = pi;
add_step:
    initp->mh_objnr = pnr;
    initp->mh_pmnr = pnr;
    list_add(&initp->mh_list, &kmplockp->mp_pgmplmheadl);
    kmplockp->mp_pgmplnr++;
    return initp;
}

adr_t page_new_on_mplhead(mplhead_t * mplhdp)
{
    pglmap_t * map;
    if(mplhdp->mh_afindx >= mplhdp->mh_objnr)
	return NULL;
    if(mplhdp->mh_firtpmap != NULL)
    {
	map = mplhdp->mh_firtpmap;
	mplhdp->mh_firtpmap = map->pgl_next;
	map->pgl_next = NULL;
	mplhdp->mh_afindx++;
	return map->pgl_start;
    }
    return NULL;
}

bool_t page_delete_on_mplhead(mplhead_t * mplhdp, adr_t fradr)
{
    pglmap_t * map;
    /*没有分配过，没有pglmap_t数据结构*/
    if(mplhdp->mh_afindx < 1 || mplhdp->mh_pmnr < 1)
    {
	return FALSE;
    }

    for(uint_t i=0; i<mplhdp->mh_pmnr; i++)
    {
	if(fradr == mplhdp->mh_pmap[i].pgl_start)
	{
	    map = &mplhdp->mh_pmap[i];
	    if(map->pgl_next != NULL)
	    {
		return FALSE;
	    }
	    goto del_step;
	}
    }
    return FALSE;
del_step:
    map->pgl_next = mplhdp->mh_firtpmap;
    mplhdp->mh_firtpmap = map;
    mplhdp->mh_afindx--;
    return TRUE;
}

adr_t kmempool_pages_core_new(size_t msize)
{
    //printfk("%s begin\n\r", __func__);
    cpuflg_t cpufg;
    mplhead_t * mplhdp;
    adr_t retadr = NULL;
    kmempool_t * kmplp = &oskmempool;
    hal_spinlock_saveflg_cli(&kmplp->mp_pglock, &cpufg);
    mplhdp = kmemplpg_retn_mplhead(kmplp, msize);
    if(mplhdp == NULL)
    {
	//printfk("kmemplpg_retn_mplhead get NULL\n\r");
	mplhdp = new_page_mpool(kmplp, msize);
	if(mplhdp == NULL)
	{
	    printfk("new_page_mpool failed\n\r");
	    retadr = NULL;
	    goto return_step;
	}
    }
    retadr = page_new_on_mplhead(mplhdp);
return_step:
    hal_spinunlock_restflg_sti(&kmplp->mp_pglock, &cpufg);
    return retadr;
}

bool_t kmempool_pages_core_delete(adr_t fradr, size_t frsz)
{
    //printfk("%s\n\r", __func__);
    cpuflg_t cpuflg;
    mplhead_t * mplhdp;
    bool_t rets = FALSE;
    kmempool_t * kmplp = &oskmempool;
    hal_spinlock_saveflg_cli(&kmplp->mp_pglock, &cpuflg);
    mplhdp = kmempldelpg_retn_mplhead(kmplp, fradr, frsz);
    if(mplhdp == NULL)
    {
	rets = FALSE;
	goto return_step;
    }
    if(page_delete_on_mplhead(mplhdp, fradr) == FALSE)
    {
	rets = FALSE;
	goto return_step;
    }
    if(del_page_mpool(kmplp, mplhdp) == FALSE)
    {
	rets = FALSE;
	goto return_step;
    }
    rets = TRUE;
return_step:
    hal_spinunlock_restflg_sti(&kmplp->mp_pglock, &cpuflg);
    return rets;
}
