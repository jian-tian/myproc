/********************
 * drvfs.c 2016.05.22
 * *****************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void rfsdir_t_init(rfsdir_t * initp)
{
    initp->rdr_stus = 0;
    initp->rdr_type = RDR_NUL_TYPE;
    initp->rdr_blknr = 0;
    for(uint_t i=0; i<DR_NM_MAX; i++)
    {
	initp->rdr_name[i] = 0;
    }
    return;
}

void rfssublk_t_init(rfssublk_t * initp)
{
    hal_spinlock_init(&initp->rsb_lock);
    initp->rsb_mgic = 0x142422;
    initp->rsb_vec = 1;
    initp->rsb_flg = 0;
    initp->rsb_stus = 0;
    initp->rsb_sz = sizeof(rfssublk_t);
    initp->rsb_sblksz = 1;
    initp->rsb_dblksz = FSYS_ALCBLKSZ;
    initp->rsb_bmpbks = 1;
    initp->rsb_bmpbknr = 0;
    initp->rsb_fsysallblk = 0;
    rfsdir_t_init(&initp->rsb_rootdir);
    return;
}

rfsdevext_t * ret_rfsdevext(device_t * devp)
{
    return (rfsdevext_t *)devp->dev_extdata;
}

void * ret_rfsdevblk(device_t * devp, uint_t blknr)
{
    rfsdevext_t * rfsexp = ret_rfsdevext(devp);
    void * blkp = rfsexp->rde_mstart + (blknr * FSYS_ALCBLKSZ);
    if(blkp >= (void *)((size_t)rfsexp->rde_mstart + rfsexp->rde_msize))
    {
	printfk("blkp error\n\r");
	return NULL;
    }
    return blkp;
}

uint_t ret_rfsdevmaxblknr(device_t * devp)
{
    rfsdevext_t * rfsexp = ret_rfsdevext(devp);
    return (uint_t)(((size_t)rfsexp->rde_msize)/FSYS_ALCBLKSZ);
}

drvstus_t write_rfsdevblk(device_t * devp, void *weadr, uint_t blknr)
{
    void * p = ret_rfsdevblk(devp, blknr);
    if(!p)
    {
	printfk("%s error\n\r", __func__);
	return DFCERRSTUS;
    }
    hal_memcpy(weadr, p, FSYS_ALCBLKSZ);
    return DFCOKSTUS;
}

drvstus_t read_rfsdevblk(device_t * devp, void * rdadr, uint_t blknr)
{
    void * p = ret_rfsdevblk(devp, blknr);
    if(!p)
    {
	printfk("%s error \n\r", __func__);
	return DFCERRSTUS;
    }
    hal_memcpy(p, rdadr, FSYS_ALCBLKSZ);
    return DFCOKSTUS;
}

rfssublk_t * get_superblk(device_t * devp)
{
    void * buf = new_buf(FSYS_ALCBLKSZ);
    if(!buf)
    {
	printfk("%s alloc failed\n\r", __func__);
	return NULL;
    }

    hal_memset(buf, FSYS_ALCBLKSZ, 0);

    if(read_rfsdevblk(devp, buf, 0)==DFCERRSTUS)
    {
	del_buf(buf, FSYS_ALCBLKSZ);
	return NULL;
    }

    return (rfssublk_t *)buf;
}

void del_superblk(device_t * devp, rfssublk_t * sbp)
{
    if(write_rfsdevblk(devp, (void *)sbp, 0) == DFCERRSTUS)
    {
	hal_sysdie("del superblk err\n\r");
    }
    del_buf((void *)sbp, FSYS_ALCBLKSZ);
    return;
}

void *new_buf(size_t bufsz)
{
    return (void *)krlnew(bufsz);
}

void del_buf(void * buf, size_t bufsz)
{
    if(krldelete((adr_t)buf, bufsz) == FALSE)
    {
	hal_sysdie("del buf err");
    }
    return;
}

bool_t create_superblk(device_t * devp)
{
    void *buf = new_buf(FSYS_ALCBLKSZ);
    if(!buf)
    {
	printfk("alloc failed\n\r");
	return FALSE;
    }
    hal_memset(buf, FSYS_ALCBLKSZ, 0);
    rfssublk_t * sbp = (rfssublk_t *)buf;
    rfssublk_t_init(sbp);
    sbp->rsb_fsysallblk = ret_rfsdevmaxblknr(devp);
    if(write_rfsdevblk(devp, buf, 0) == DFCERRSTUS)
    {
	printfk("write_rfsdevblk failed\n\r");
	return FALSE;
    }
    del_buf(buf, FSYS_ALCBLKSZ);
    return TRUE;
}

bool_t create_bitmap(device_t * devp)
{
    bool_t rets = FALSE;
    rfssublk_t * sbp = get_superblk(devp);
    if(!sbp)
    {
	return FALSE;
    }
    void * buf = new_buf(FSYS_ALCBLKSZ);
    if(!buf)
    {
	printfk("%s alloc failed\n\r", __func__);
	return FALSE;
    }

    uint_t bitmapblk = sbp->rsb_bmpbks;
    uint_t devmaxblk = sbp->rsb_fsysallblk;
    if(devmaxblk > FSYS_ALCBLKSZ)
    {
	rets = FALSE;
	goto errlable;
    }

    hal_memset(buf, FSYS_ALCBLKSZ, 1);
    u8_t * bitmap = (u8_t *)buf;
    for(uint_t bi=2; bi<devmaxblk; bi++)
    {
	bitmap[bi] = 0;
    }
    /*缓冲区数据回写到存储介质的第bitmapblk存储块中*/
    if(write_rfsdevblk(devp, buf, bitmapblk) == DFCERRSTUS)
    {
	rets = FALSE;
	goto errlable;
    }

    rets = TRUE;
errlable:
    del_superblk(devp, sbp);
    del_buf(buf, FSYS_ALCBLKSZ);

    return rets;
}

void filblks_t_init(filblks_t * initp)
{
    initp->fb_blkstart = 0;
    initp->fb_blknr = 0;
    return;
}

void fimgrhd_t_init(fimgrhd_t * initp)
{
    initp->fmd_stus = 0;
    initp->fmd_type = FMD_NUL_TYPE;
    initp->fmd_flg = 0;
    initp->fmd_sfblk = 0;
    initp->fmd_acss = 0;
    initp->fmd_newtime = 0;
    initp->fmd_acstime = 0;
    initp->fmd_fileallbk = 0;
    initp->fmd_filesz = 0;
    initp->fmd_fileifstbkoff = 0x200;
    initp->fmd_fileiendbkoff = 0;
    initp->fmd_curfwritebk = 0;

    for(uint_t i=0; i<FBLKS_MAX; i++)
    {
	filblks_t_init(&initp->fmd_fleblk[i]);
    }

    initp->fmd_linkpblk = 0;
    initp->fmd_linknblk = 0;
    return;
}

u8_t * get_bitmapblk(device_t * devp)
{
    rfssublk_t * sbp = get_superblk(devp);
    if(!sbp)
    {
	printfk("%s get_superblk failed\n\r", __func__);
	return NULL;
    }
    void *buf = new_buf(FSYS_ALCBLKSZ);
    if(!buf)
    {
	return NULL;
    }
    hal_memset(buf, FSYS_ALCBLKSZ, 0);
    if(read_rfsdevblk(devp, buf, sbp->rsb_bmpbks))
    {
	del_buf(buf, FSYS_ALCBLKSZ);
	del_superblk(devp, sbp);
	return NULL;
    }

    del_superblk(devp, sbp);
    return (u8_t *)buf;
}

void del_bitmapblk(device_t * devp, u8_t * bitmap)
{
    rfssublk_t * sbp = get_superblk(devp);
    if(!sbp)
    {
	hal_sysdie("get superblk err");
	return;
    }
    if(write_rfsdevblk(devp, (void *)bitmap, sbp->rsb_bmpbks) == DFCERRSTUS)
    {
	del_superblk(devp, sbp);
	hal_sysdie("del superblk err");
    }

    del_superblk(devp, sbp);
    del_buf((void *)bitmap, FSYS_ALCBLKSZ);

    return;
}

uint_t rfs_new_blk(device_t * devp)
{
    uint_t retblk = 0;
    u8_t * bitmap = get_bitmapblk(devp);
    if(!bitmap)
    {
	printfk("%s get_bitmapblk failed\n\r", __func__);
	return 0;
    }

    for(uint_t blknr=2; blknr<FSYS_ALCBLKSZ; blknr++)
    {
	if(bitmap[blknr] == 0)
	{
	    bitmap[blknr] = 1;
	    retblk = blknr;
	    goto ret1;
	}
    }
    retblk = 0;
ret1:
    del_bitmapblk(devp, bitmap);
    return retblk;
}

bool_t create_rootdir(device_t * devp)
{
    bool_t rets = FALSE;
    rfssublk_t * sbp = get_superblk(devp);
    if(!sbp)
    {
	printfk("%s get_superblk failed\n\r");
	return FALSE;
    }

    void * buf = new_buf(FSYS_ALCBLKSZ);
    if(!buf)
    {
	rets = FALSE;
	goto errlable1;
    }
    hal_memset(buf, FSYS_ALCBLKSZ, 0);
    uint_t blk = rfs_new_blk(devp);
    if(blk == 0)
    {
	rets = FALSE;
	printfk("%s rfs_new_blk failed\n\r");
	goto errlable;
    }

    sbp->rsb_rootdir.rdr_name[0] = '/';
    sbp->rsb_rootdir.rdr_type = RDR_DIR_TYPE;
    sbp->rsb_rootdir.rdr_blknr = blk;

    fimgrhd_t * fmp = (fimgrhd_t *)buf;
    fimgrhd_t_init(fmp);
    fmp->fmd_type = FMD_DIR_TYPE;
    fmp->fmd_sfblk = blk;
    fmp->fmd_curfwritebk = blk;
    fmp->fmd_curfinwbkoff = 0x200;
    fmp->fmd_fleblk[0].fb_blkstart = blk;
    fmp->fmd_fleblk[0].fb_blknr = 1;

    if(write_rfsdevblk(devp, buf, blk) == DFCERRSTUS)
    {
	rets = FALSE;
	goto errlable;
    }
    rets = TRUE;
errlable:
    del_buf(buf, FSYS_ALCBLKSZ);
errlable1:
    del_superblk(devp, sbp);
    
    return rets;
}

void init_rfs(device_t * devp)
{
    rfs_fmat(devp);
    return;
}

void rfs_fmat(device_t * devp)
{
    if(create_superblk(devp) == FALSE)
    {
	hal_sysdie("create superblk failed");
    }

    if(create_bitmap(devp) == FALSE)
    {
	hal_sysdie("create bitmap failed");
    }

    if(create_rootdir(devp) == FALSE)
    {
	hal_sysdie("create rootdir failed");
    }

    return;
}
