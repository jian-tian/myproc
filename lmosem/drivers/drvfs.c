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

void rfs_del_blk(device_t * devp, uint_t blknr)
{
    if(blknr > FSYS_ALCBLKSZ)
    {
	hal_sysdie("rfs del blk err");
	return;
    }
    u8_t * bitmap = get_bitmapblk(devp);
    if(bitmap == NULL)
    {
	hal_sysdie("ref del blk err1");
	return;
    }
    bitmap[blknr] = 0;
    del_bitmapblk(devp, bitmap);
    return;
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

/*获取根目录文件数据结构*/
rfsdir_t * get_rootdir(device_t * devp)
{
    rfsdir_t * retptr = NULL;
    rfssublk_t * sbp = get_superblk(devp);
    if(!sbp)
    {
	return NULL;
    }
    void * buf = new_buf(sizeof(rfsdir_t));
    if(!buf)
    {
	printfk("new_buf failed\n\r");
	retptr = NULL;
	goto err1;
    }

    hal_memcpy((void *)(&sbp->rsb_rootdir), buf, sizeof(rfsdir_t));
    retptr = (rfsdir_t *)buf;

err1:
    del_superblk(devp, sbp);
    return retptr;
}

void del_rootdir(device_t * devp, rfsdir_t * rdir)
{
    del_buf((void *)rdir, sizeof(rfsdir_t));
    return;
}

void * get_rootdirfile_blk(device_t * devp)
{
    void * retptr = NULL;
    rfsdir_t * rtdir = get_rootdir(devp);
    if(!rtdir)
    {
	printfk("get_rootdir failed\n\r");
	return NULL;
    }
    void * buf = new_buf(FSYS_ALCBLKSZ);
    if(!buf)
    {
	printfk("new_buf failed\n\r");
	retptr = NULL;
	goto err2;
    }
    hal_memset(buf, FSYS_ALCBLKSZ, 0);
    if(read_rfsdevblk(devp, buf, rtdir->rdr_blknr) == DFCERRSTUS)
    {
	printfk("read_rfsdevblk failed\n\r");
	retptr = NULL;
	goto err1;
    }
    retptr = buf;
    goto err2;

err1:
    del_buf(buf, FSYS_ALCBLKSZ);
err2:
    del_rootdir(devp, rtdir);
    return retptr;
}

void del_rootdirfile_blk(device_t * devp, void *blkp)
{
    fimgrhd_t * fmp = (fimgrhd_t *)blkp;
    if(write_rfsdevblk(devp, blkp, fmp->fmd_sfblk) == DFCERRSTUS)
    {
	hal_sysdie("del_rootfile_blk err");
    }
    del_buf(blkp, FSYS_ALCBLKSZ);
    return;
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

sint_t rfs_strcmp(char_t * str_s, char_t * str_d)
{
    for(;;)
    {
	if(*str_s != *str_d)
	{
	    return 0;
	}
	if(*str_s == 0)
	{
	    break;
	}
	str_s++;
	str_d++;
    }
    return 1;
}

sint_t rfs_strlen(char * str_s)
{
    sint_t chaidx = 0;
    while(*str_s != 0)
    {
	str_s++;
	chaidx++;
    }
    return chaidx;
}

sint_t rfs_strcpy(char_t * str_s, char_t * str_d)
{
    sint_t chaidx = 0;
    while(*str_s != 0)
    {
	*str_d = *str_s;
	str_s++;
	str_d++;
	chaidx++;
    }
    *str_d = *str_s;
    return chaidx;
}

sint_t rfs_chkfilepath(char_t * fname)
{
    char_t * chp = fname;

    if(chp[0] != '/')
    {
	return 2;
    }

    for(uint_t i=1; ; i++)
    {
	if(chp[i] == '/')
	{
	    return 3;
	}
	if(i >= DR_NM_MAX)
	{
	    return 4;
	}
	if(chp[i] == 0 && i>1)
	{
	    break;
	}
    }
    return 0;
}

sint_t rfs_ret_fname(char_t * buf, char_t * fpath)
{
    if(NULL == buf || NULL == fpath)
    {
	return 6;
    }

    sint_t stus = rfs_chkfilepath(fpath);
    if(stus != 0)
    {
	return stus;
    }

    rfs_strcpy(&fpath[1], buf);
    return 0;
}

sint_t rfs_chkfileisindev(device_t * devp, char_t * fname)
{
    sint_t rets = 6;
    sint_t ch = rfs_strlen(fname);
    if(ch<1 || ch>(sint_t)DR_NM_MAX)
    {
	return 4;
    }

    void * rdblkp = get_rootdirfile_blk(devp);
    if(rdblkp == NULL)
    {
	printfk("get_rootdirfile_blk failed\n\r");
	return 2;
    }

    fimgrhd_t *fmp = (fimgrhd_t *)rdblkp;
    if(fmp->fmd_type != FMD_DIR_TYPE)
    {
	rets = 3;
	goto err;
    }
    if(fmp->fmd_curfwritebk == fmp->fmd_fleblk[0].fb_blkstart 
       && fmp->fmd_curfinwbkoff == fmp->fmd_fileifstbkoff)
    {
	rets = 0;
	goto err;
    }
    rfsdir_t * dirp = (rfsdir_t *)((uint_t)(fmp) + fmp->fmd_fileifstbkoff);
    void * maxchkp = (void *)((uint_t)rdblkp + FSYS_ALCBLKSZ - 1);
    for(; (void *)dirp<maxchkp; )
    {
	if(dirp->rdr_type == RDR_FIL_TYPE)
	{
	    if(rfs_strcmp(dirp->rdr_name, fname) == 1)
	    {
		rets = 1;
		goto err;
	    }
	}
	dirp++;
    }
    rets = 0;

err:
    del_rootdirfile_blk(devp, rdblkp);
    return rets;
}

drvstus_t rfs_new_file(device_t * devp, char_t * fname, uint_t flg)
{
    char_t fne[DR_NM_MAX];
    hal_memset((void *)fne, DR_NM_MAX, 0);
    if(rfs_ret_fname(fne, fname) != 0)
    {
	return DFCERRSTUS;
    }

    if(rfs_chkfileisindev(devp, fne) != 0)
    {
	printfk("file exist already\n\r");
	return DFCERRSTUS;
    }

    return rfs_new_dirfileblk(devp, fne, RDR_FIL_TYPE, 0);
}

drvstus_t rfs_new_dirfileblk(device_t * devp, char_t * fname, uint_t flgtype, uint_t val)
{
    drvstus_t rets = DFCERRSTUS;

    if(flgtype != RDR_FIL_TYPE)
    {
	printfk("file type error\n\r");
	return DFCERRSTUS;
    }

    void * buf = new_buf(FSYS_ALCBLKSZ);
    if(buf == NULL)
    {
	printfk("alloc buf failed\n\r");
	return DFCERRSTUS;
    }
    hal_memset(buf, FSYS_ALCBLKSZ, 0);

    uint_t fblk = rfs_new_blk(devp);
    if(fblk == 0)
    {
	printfk("rfs new blk failed\n\r");
	rets = DFCERRSTUS;
	goto err1;
    }

    void * rdirblk = get_rootdirfile_blk(devp);
    if(rdirblk == NULL)
    {
	rets = DFCERRSTUS;
	goto err1;
    }

    fimgrhd_t * fmp = (fimgrhd_t *)rdirblk;
    rfsdir_t * wrdirp = (rfsdir_t *)((uint_t)rdirblk + fmp->fmd_curfinwbkoff);
    if(((uint_t)wrdirp) >= ((uint_t)rdirblk + FSYS_ALCBLKSZ))
    {
	rets = DFCERRSTUS;
	printfk("wrdirp error\n\r");
	goto err;
    }
    wrdirp->rdr_stus = 0;
    wrdirp->rdr_type = flgtype;
    wrdirp->rdr_blknr = fblk;
    rfs_strcpy(fname, wrdirp->rdr_name);
    fmp->fmd_filesz += (uint_t)(sizeof(rfsdir_t));
    fmp->fmd_curfinwbkoff += (uint_t)(sizeof(rfsdir_t));
    fimgrhd_t * ffmp = (fimgrhd_t *)buf;
    fimgrhd_t_init(ffmp);
    ffmp->fmd_type = FMD_FIL_TYPE;
    ffmp->fmd_sfblk = fblk;
    ffmp->fmd_curfwritebk = fblk;
    ffmp->fmd_curfinwbkoff = 0x200;
    ffmp->fmd_fleblk[0].fb_blkstart = fblk;
    ffmp->fmd_fleblk[0].fb_blknr = 1;
    if(write_rfsdevblk(devp, buf, fblk) == DFCERRSTUS)
    {
	printfk("write rfsdevblk failed\n\r");
	rets = DFCERRSTUS;
	goto err;
    }
    rets = DFCOKSTUS;

err1:
    del_rootdirfile_blk(devp, rdirblk);
err:
    del_buf(buf, FSYS_ALCBLKSZ);
    return rets;
}

drvstus_t rfs_del_file(device_t * devp, char_t * fname, uint_t flg)
{
    if(flg != 0)
    {
	printfk("flg error\n\r");
	return DFCERRSTUS;
    }
    drvstus_t rets = rfs_del_dirfileblk(devp, fname, RDR_FIL_TYPE, 0);
    return rets;
}

drvstus_t rfs_del_dirfileblk(device_t * devp, char_t * fname, uint_t flgtype, uint_t val)
{
    if((flgtype != RDR_FIL_TYPE) || (val != 0))
    {
	printfk("input error\n\r");
	return DFCERRSTUS;
    }

    char_t fne[DR_NM_MAX];
    hal_memset((void *)fne, DR_NM_MAX, 0);
    if(rfs_ret_fname(fne, fname) != 0)
    {
	printfk("fname error\n\r");
	return DFCERRSTUS;
    }

    if(del_dirfileblk_core(devp, fne) != 0)
    {
	printfk("del_dirfileblk_core failed\n\r");
	return DFCERRSTUS;
    }

    return DFCOKSTUS;
}

drvstus_t del_dirfileblk_core(device_t * devp, char_t * fname)
{
    sint_t rets = 6;
    void * rblkp = get_rootdirfile_blk(devp);
    if(rblkp == NULL)
    {
	printfk("get rootdirfileblk failed\n\r");
	return 5;
    }

    fimgrhd_t * fmp = (fimgrhd_t *)rblkp;
    if(fmp->fmd_type != FMD_DIR_TYPE)
    {
	rets = 4;
	goto err;
    }
    if(fmp->fmd_curfwritebk == fmp->fmd_fleblk[0].fb_blkstart &&
	fmp->fmd_curfinwbkoff == fmp->fmd_fileifstbkoff)
    {
	rets = 3;
	goto err;
    }

    rfsdir_t * dirp = (rfsdir_t *)((uint_t)(fmp) + fmp->fmd_fileifstbkoff);
    void * maxchkp = (void *)((uint_t)rblkp + FSYS_ALCBLKSZ - 1);
    for(;(void *)dirp<maxchkp;)
    {
	if(dirp->rdr_type == RDR_FIL_TYPE)
	{
	    if(rfs_strcmp(dirp->rdr_name, fname) == 1)
	    {
		rfs_del_blk(devp, dirp->rdr_blknr);
		rfsdir_t_init(dirp);
		dirp->rdr_type = RDR_DEL_TYPE;
		rets = 0;
		goto err;
	    }
	}
	dirp++;
    }
    rets = 1;

err:
    del_rootdirfile_blk(devp, rblkp);
    return rets;
}

drvstus_t rfs_open_file(device_t * devp, void * iopack)
{
    objnode_t * obp = (objnode_t *)iopack;
    if(obp->on_fname == NULL)
    {
	printfk("name err\n\r");
	return DFCERRSTUS;
    }
    void * fmdp = rfs_openfileblk(devp, (char_t *)obp->on_fname);
    if(fmdp == NULL)
    {
	printfk("open fileblk failed\n\r");
	return DFCERRSTUS;
    }
    obp->on_finode = fmdp;
    return DFCOKSTUS;
}

void * rfs_openfileblk(device_t * devp, char_t * fname)
{
    char_t fne[DR_NM_MAX];
    void * rets = NULL;
    void * buf = NULL;

    hal_memset((void *)fne, DR_NM_MAX, 0);
    if(rfs_ret_fname(fne, fname) != 0)
    {
	printfk("name err\n\r");
	return NULL;
    }

    void * rblkp = get_rootdirfile_blk(devp);
    if(rblkp == NULL)
    {
	printfk("get rootdirfilebk failed\n\r");
	return NULL;
    }

    fimgrhd_t * fmp = (fimgrhd_t *)rblkp;
    if(fmp->fmd_type != FMD_DIR_TYPE)
    {
	printfk("fmd type err\n\r");
	rets = NULL;
	goto err;
    }
    if(fmp->fmd_curfwritebk == fmp->fmd_fleblk[0].fb_blkstart &&
	fmp->fmd_curfinwbkoff == fmp->fmd_fileifstbkoff)
    {
	rets = NULL;
	goto err;
    }

    rfsdir_t * dirp = (rfsdir_t *)((uint_t)(fmp) + fmp->fmd_fileifstbkoff);
    void * maxchkp = (void *)((uint_t)rblkp + FSYS_ALCBLKSZ - 1);
    for(; (void *)dirp<maxchkp; )
    {
	if(dirp->rdr_type == RDR_FIL_TYPE)
	{
	    if(rfs_strcmp(dirp->rdr_name, fne) == 1)
	    {
		goto opfblk;
	    }
	}
	dirp++;
    }
    rets = NULL;
    goto err;

opfblk:
    buf = new_buf(FSYS_ALCBLKSZ);
    if(buf == NULL)
    {
	printfk("alloc buf failed\n\r");
	rets = NULL;
	goto err;
    }
    if(read_rfsdevblk(devp, buf, dirp->rdr_blknr) == DFCERRSTUS)
    {
	printfk("read rfsdevblk failed\n\r");
	rets = NULL;
	goto err1;
    }
    fimgrhd_t * ffmp = (fimgrhd_t *)buf;
    if(ffmp->fmd_type == FMD_FIL_TYPE || ffmp->fmd_fileifstbkoff != 0x200)
    {
	printfk("ffmp err\n\r");
	rets = NULL;
	goto err1;
    }
    rets = buf;
    goto err;

err1:
    del_buf(buf, FSYS_ALCBLKSZ);
err:
    del_rootdirfile_blk(devp, rblkp);
    return rets;
}

drvstus_t rfs_read_file(device_t * devp, void * iopack)
{
    objnode_t * obp = (objnode_t *)iopack;
    if(obp->on_finode == NULL || obp->on_buf == NULL ||
	obp->on_bufsz != FSYS_ALCBLKSZ)
    {
	printfk("iopack input err\n\r");
	return DFCERRSTUS;
    }

    return rfs_readfileblk(devp, (fimgrhd_t *)obp->on_finode, obp->on_buf, obp->on_len);
}

drvstus_t rfs_readfileblk(device_t * devp, fimgrhd_t * fmp, void * buf, uint_t len)
{
    if(fmp->fmd_sfblk != fmp->fmd_curfwritebk ||
	fmp->fmd_curfwritebk != fmp->fmd_fleblk[0].fb_blkstart)
    {
	printfk("fmp err\n\r");
	return DFCERRSTUS;
    }
    if(len > (FSYS_ALCBLKSZ - fmp->fmd_fileifstbkoff))
    {
	printfk("len err\n\r");
	return DFCERRSTUS;
    }

    void * wrp = (void *)((uint_t)fmp + fmp->fmd_fileifstbkoff);
    hal_memcpy(wrp, buf, len);
    return DFCOKSTUS;
} 
