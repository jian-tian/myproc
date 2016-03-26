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

void testobjsmgr()
{
#define OBJTESTCOUNT	2
    adrsz_t adsz[OBJTESTCOUNT];
    size_t alcsz = 0x20;
    u8_t * adrbytp = NULL;
    u8_t bytval = 0;

    for(; alcsz < 0x800; alcsz += 0x10)
    {
	/*alloc*/
	for(uint_t i=0; i<OBJTESTCOUNT; i++)
	{
	    adsz[i].sz = alcsz;
	    adsz[i].adr = kmempool_new(alcsz);
	    if(adsz[i].adr == NULL)
	    {
		hal_sysdie("testobjsmgr kmempool_new err");
	    }
	    printfk("objs alloc adsz[%x] sz:0x%x adr:0x%x\n\r", i, adsz[i].sz, adsz[i].adr);
	    adrbytp = (u8_t *)adsz[i].adr;
	    bytval = (u8_t)(adsz[i].adr & 0xff);
	    for(uint_t k=0; k<adsz[i].sz; k++)
	    {
		adrbytp[k] = bytval;
	    }
	}
	/*cmp*/
	cmp_adrsz(adsz, OBJTESTCOUNT);
	/*delete*/
	for(uint_t j=0; j<OBJTESTCOUNT; j++)
	{
	    if(kmempool_delete(adsz[j].adr, adsz[j].sz) == FALSE)
	    {
		hal_sysdie("testobjsmgr kmempool_delete err");
	    }
	    printfk("objs delete adsz[%x] sz:0x%x adr:0x%x\n\r", j, adsz[j].sz, adsz[j].adr);
	}
	printfk("oskmempool.mp_pgmplnr:%x\n\r", oskmempool.mp_pgmplnr);
    }
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

void show_mplhead()
{
    list_h_t * list;
    mplhead_t * mplhdp;
    kmempool_t * kmplockp = &oskmempool;

    list_for_each(list, &kmplockp->mp_obmplmheadl)
    {
	mplhdp = list_entry(list, mplhead_t, mh_list);
	printfk("mplhdp->mh_aliobsz is 0x%x, mplhdp->mh_start is 0x%x, mplhdp->mh_end is 0x%x\n\r", mplhdp->mh_aliobsz, mplhdp->mh_start, mplhdp->mh_end);
    }

    return;
}
void init_krlpagempol()
{
    kmempool_t_init(&oskmempool);
    return; 
}

void kmempool_t_init(kmempool_t * mph)
{
    hal_spinlock_init(&mph->mp_lock);
    list_init(&mph->mp_list);
    mph->mp_stus = 0;
    mph->mp_flgs = 0;
    hal_spinlock_init(&mph->mp_pglock);
    hal_spinlock_init(&mph->mp_oblock);
    mph->mp_pgmplnr = 0;
    mph->mp_obmplnr = 0;
    list_init(&mph->mp_pgmplmheadl);
    list_init(&mph->mp_obmplmheadl);
    mph->mp_pgmplmhcach = NULL;
    mph->mp_obmplmhcach = NULL;
    return;
}

adr_t kmempool_new(size_t msize)
{
    //printfk("%s\n\r", __func__);
    if(msize < KMEMPALCSZ_MIN || msize > KMEMPALCSZ_MAX)
    {
	printfk("msize error in kmempool_new\n\r");
	return NULL;
    }

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
    //printfk("%s\n\r", __func__);
    size_t sz = OBJS_ALIGN(msize);

    if(sz > OBJSORPAGE)
    {
	printfk("sz > OBJS_ALIGN\n\r");
	return NULL;
    }

    return kmempool_objsz_core_new(sz);
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
    size_t sz = OBJS_ALIGN(frsz);

    if(sz > OBJSORPAGE)
	return NULL;

    return kmempool_objsz_core_delete(fradr, frsz);
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

mplhead_t * objsnew_mplhead_isok(mplhead_t * mph, size_t msize)
{
    if(mph->mh_firtfreadr == NULL)
	return NULL;
    if(mph->mh_hedty != MPLHTY_OBJS)
	return NULL;
    if(mph->mh_aliobsz != msize)
	return NULL;
    if(mph->mh_afindx >= mph->mh_objnr)
	return NULL;

    return mph;
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

mplhead_t * objdel_mplhead_isok(mplhead_t * mhp, adr_t fradr, size_t msize)
{
    if(mhp->mh_hedty != MPLHTY_OBJS)
	return NULL;
    if(mhp->mh_aliobsz != msize)
	return NULL;
    if(mhp->mh_afindx == 0)
	return NULL;
    if(fradr < (mhp->mh_start + sizeof(mplhead_t)) || (fradr + msize - 1) > mhp->mh_end)
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

mplhead_t * kmemplob_retn_mplhead(kmempool_t * kmplockp, size_t msize)
{
    //printfk("%s %d\n\r", __func__, __LINE__);
    mplhead_t * retmhp;
    list_h_t * list;
    if(kmplockp->mp_obmplmhcach != NULL)
    {
	retmhp = kmplockp->mp_obmplmhcach;
	retmhp = objsnew_mplhead_isok(retmhp, msize);
	if(retmhp != NULL)
	{
	    return retmhp;
	}
    }
    //printfk("%s %d\n\r", __func__, __LINE__);
    list_for_each(list, &kmplockp->mp_obmplmheadl)
    {
	retmhp = list_entry(list, mplhead_t, mh_list);
	retmhp = objsnew_mplhead_isok(retmhp, msize);
	if(retmhp != NULL)
	{
	    kmplockp->mp_obmplmhcach = retmhp;
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

mplhead_t * kmempldelob_retn_mplhead(kmempool_t * kmplockp, adr_t fradr, size_t msize)
{
    mplhead_t * retmhp;
    list_h_t * list;
    if(kmplockp->mp_obmplmhcach != NULL)
    {
	retmhp = kmplockp->mp_obmplmhcach;
	retmhp = objdel_mplhead_isok(retmhp, fradr, msize);
	if(retmhp != NULL)
	{
	    return retmhp;
	}
    }
    list_for_each(list, &kmplockp->mp_obmplmheadl)
    {
	retmhp = list_entry(list, mplhead_t, mh_list);
	retmhp = objdel_mplhead_isok(retmhp, fradr, msize);
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

mplhead_t * new_objs_mpool(kmempool_t * kmplockp, size_t msize)
{
    //printfk("%s\n\r", __func__);
    mplhead_t * mphdp = NULL;
    adr_t pgadr = kmempool_pages_new(0x4000);
    //printfk("%s %d\n\r", __func__, __LINE__);
    if(pgadr == NULL)
    {
	return NULL;
    }
    mphdp = (mplhead_t *)pgadr;
    mphdp = objs_mpool_init(kmplockp, mphdp, msize, pgadr, (pgadr + 0x4000 - 1));
    //show_mplhead();
    //printfk("%s %d\n\r", __func__, __LINE__);
    if(mphdp == NULL)
    {
	hal_sysdie("new objs mpool err");
    }
    //printfk("%s %d\n\r", __func__, __LINE__);
    return mphdp;
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

bool_t del_objs_mpool(kmempool_t * kmplockp, mplhead_t * mphdp)
{
    if(mphdp->mh_afindx > 0)
	return TRUE;
    /*计算需要释放内存大小*/
    size_t frsz = mphdp->mh_end - mphdp->mh_start + 1;
    adr_t fradr = mphdp->mh_start;
    /*从链表中删除*/
    list_del(&mphdp->mh_list);
    if(kmplockp->mp_obmplnr < 1)
    {
	hal_sysdie(" kmplockp->mp_obmplnr < 1");
    }
    /*内存池计数减少*/
    kmplockp->mp_obmplnr--;
    /*注意obmplhcach的处理*/
    if(kmplockp->mp_obmplmhcach == mphdp)
    {
	kmplockp->mp_obmplmhcach = NULL;
    }
    /*释放内存池占用的页面*/
    if(kmempool_pages_delete(fradr, frsz) == FALSE)
    {
	hal_sysdie(" page delete err");
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

mplhead_t * page_mpool_init(kmempool_t * kmplockp, mplhead_t * mph, size_t msize, adr_t start, adr_t end)
{
    if(((start & 0xFFF)!=0 || ((end-start)<(PAGE_SIZE*2)-1)))
	return NULL;

    adr_t sadr = start + PAGE_SIZE;
    uint_t pi=0,pnr=0;

    mplhead_t_init(mph);
    mph->mh_hedty = MPLHTY_PAGE;
    mph->mh_start = start;
    mph->mh_end = end;
    mph->mh_aliobsz = msize;
    mph->mh_objsz = msize;

    for(;;)
    {
	if((sadr+msize-1) > end)
	    break;
	mph->mh_pmap[pi].pgl_start = sadr;
	mph->mh_pmap[pi].pgl_next = &(mph->mh_pmap[pi+1]);
	sadr += msize;
	pi++;
    }
    if(pi > 0)
    {
	mph->mh_pmap[pi-1].pgl_next = NULL;
	pnr = pi;
	mph->mh_firtpmap = &(mph->mh_pmap[0]);
	goto add_step;
    }
    mph->mh_pmap[pi].pgl_next = NULL;
    mph->mh_pmap[pi].pgl_start = NULL;
    pnr = pi;
add_step:
    mph->mh_objnr = pnr;
    mph->mh_pmnr = pnr;
    list_add(&mph->mh_list, &kmplockp->mp_pgmplmheadl);
    kmplockp->mp_pgmplnr++;
    return mph;
}

mplhead_t * objs_mpool_init(kmempool_t * kmplockp, mplhead_t * mph, size_t msize, adr_t start, adr_t end)
{
    /*入参合法性检查*/
    if(((start & 0xfff)!=0) || ((end-start) < (PAGE_SIZE - 1)))
    {
	return NULL;
    }
    /*计算第一个对象开始地址,四字节对其*/
    adr_t sadr = start + sizeof(mplhead_t);
    if((sadr & 3) != 0)
    {
	hal_sysdie("objs_mpool_init: sadr not align dword");
	return NULL;
    }
    /*初始化mplhead_t数据结构*/
    uint_t objnr = 0;
    mplhead_t_init(mph);
    mph->mh_hedty = MPLHTY_OBJS;
    mph->mh_start = start;
    mph->mh_end = end;
    mph->mh_firtfreadr = sadr;
    mph->mh_aliobsz = msize;/*本内存池中所有对象大小都为msize*/
    mph->mh_objsz = msize;
    mph->mh_nxtpsz = msize + sizeof(adr_t);/*每个对象后有个head，每个对象实际占用空间*/

    adr_t * nexp = NULL;
    adr_t adrsz = msize;
    adr_t npsz = mph->mh_nxtpsz;/*每个对象大小*/
    if((mph->mh_nxtpsz & 3) != 0)
    {
	hal_sysdie("objs_mpool_init:mph->mh_nxtpsz not align dword");
	return NULL;
    }

    for(;;)
    {
	//printfk("sadr is 0x%x, npsz is 0x%x, end is 0x%x\n\r", sadr, npsz, end);
	if((sadr + npsz - 1) > end)
	    break;
	nexp = (adr_t *)(sadr + adrsz);//下一个对象地址
	*nexp = (sadr + npsz);//先放对象指针
	sadr += npsz;         //sadr变为下一个对象实际开始地址
	objnr++;
    }
    /*r如果对象计数为0，表示没有初始化内存池对象，卡死*/
    if(objnr == 0)
    {
	hal_sysdie("objs_mpool_init: objnr err");
	return NULL;
    }
    /*取出最后一个对象,其下一个对象指针为NULL，表示没有对象了*/
    sadr -= npsz;
    nexp = (adr_t *)(sadr + adrsz);
    *nexp = NULL;
    /*设置内存池对象个数，并加入到kmempool_t全局数据链中*/
    mph->mh_objnr = objnr;
    list_add(&mph->mh_list, &kmplockp->mp_obmplmheadl);
    kmplockp->mp_obmplnr++;
    //printfk("mph->mh_objnr is 0x%x, initp->mh_afindx is 0x%x, kmplockp->mp_obmplnr is 0x%x\n\r", mph->mh_objnr, mph->mh_afindx, kmplockp->mp_obmplnr);
    
    return mph;
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

adr_t objs_new_on_mplhead(mplhead_t * mplhdp)
{
    //printfk("%s %d\n\r", __func__, __LINE__);
    if(mplhdp->mh_afindx >= mplhdp->mh_objnr || mplhdp->mh_firtfreadr == NULL)
    {
	printfk("%s: mh_afindx, mh_firtfreadr failed\n\r", __func__);
	return NULL;
    }
    //printfk("%s %d\n\r", __func__, __LINE__);
    adr_t retadr = NULL;
    adr_t *nextp = NULL;
    /*实际对象大小*/
    adr_t adrsz = (adr_t)(mplhdp->mh_aliobsz);
    /*获取对象地址*/
    retadr = mplhdp->mh_firtfreadr;
    /*mh_firtfreadr指向下一个未分配对象，切获取到对象从链表中断开*/
    nextp = (adr_t *)(retadr + adrsz);
    mplhdp->mh_firtfreadr = *nextp;
    *nextp = NULL;
    /*对象分配数增加*/
    mplhdp->mh_afindx++;
    return retadr;
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

bool_t objs_delete_on_mplhead(mplhead_t * mplhdp, adr_t fradr)
{
    /*入参检查*/
    if(mplhdp->mh_afindx < 1 || fradr < (mplhdp->mh_start + sizeof(mplhead_t)) || (fradr + mplhdp->mh_aliobsz) >= mplhdp->mh_end)
	return FALSE;
    adr_t retadr = NULL;
    adr_t *nextp = NULL;
    adr_t adrsz = (adr_t)(mplhdp->mh_aliobsz);
    /*计算释放对象的下一个对象指针域的地址*/
    nextp = (adr_t *)(fradr + adrsz);
    if(*nextp != NULL)
    {
	return FALSE;
    }
    /*将firt_freadr的值赋值给retadr*/
    retadr = mplhdp->mh_firtfreadr;
    *nextp = retadr;
    /*被释放的地址入链*/
    mplhdp->mh_firtfreadr = fradr;
    /*计数器递减*/
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
	printfk("kmemplpg_retn_mplhead get NULL\n\r");
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

adr_t kmempool_objsz_core_new(size_t msize)
{
    //printfk("%s\n\r", __func__);
    adr_t retadr = NULL;
    cpuflg_t cpuflg;
    mplhead_t * mplhdp;
    kmempool_t * kmplp = &oskmempool;
    hal_spinlock_saveflg_cli(&kmplp->mp_oblock, &cpuflg);
    //show_mplhead();
    mplhdp = kmemplob_retn_mplhead(kmplp, msize);
    if(mplhdp == NULL)
    {
	//printfk("%s get NULL\n\r", __func__);
	mplhdp = new_objs_mpool(kmplp, msize);
	if(mplhdp == NULL)
	{
	    printfk("new_objs_mpool failed\n\r");
	    retadr = NULL;
	    goto return_step;
	}
    }
    retadr = objs_new_on_mplhead(mplhdp);
return_step:
    hal_spinunlock_restflg_sti(&kmplp->mp_oblock, &cpuflg);
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

bool_t kmempool_objsz_core_delete(adr_t fradr, size_t frsz)
{
    bool_t rets = FALSE;
    cpuflg_t cpufg;
    kmempool_t * kmplp = &oskmempool;
    mplhead_t * mplhdp;

    hal_spinlock_saveflg_cli(&kmplp->mp_oblock, &cpufg);
    mplhdp = kmempldelob_retn_mplhead(kmplp, fradr, frsz);
    if(mplhdp == NULL)
    {
	rets = FALSE;
	goto return_step;
    }
    if(objs_delete_on_mplhead(mplhdp, fradr) == NULL)
    {
	rets = FALSE;
	goto return_step;
    }
    if(del_objs_mpool(kmplp, mplhdp) == NULL)
    {
	rets = FALSE;
	goto return_step;
    }
    rets = TRUE;
return_step:
    hal_spinunlock_restflg_sti(&kmplp->mp_oblock, &cpufg);
    return rets;
}
