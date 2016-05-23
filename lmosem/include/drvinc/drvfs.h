/***********************
 * drvfs.h 2016.05.22
 * ********************/
#ifndef DRVFS_H
#define DEVFS_H

void rfsdevext_t_init(rfsdevext_t * initp);
void rfsdir_t_init(rfsdir_t * initp);
void filblks_t_init(filblks_t * initp);
void rfssublk_t_init(rfssublk_t * initp);
void fimgrhd_t_init(fimgrhd_t * initp);
drvstus_t new_rfsdevext_mmblk(device_t * devp, size_t blksz);
rfsdevext_t * ret_rfsdevext(device_t * devp);
void * ret_rfsdevblk(device_t * devp, uint_t blknr);
uint_t ret_rfsdevmaxblknr(device_t * devp);
drvstus_t read_rfsdevblk(device_t * devp, void * rdadr, uint_t blknr);
drvstus_t write_rfsdevblk(device_t * devp, void * weadr, uint_t blknr);
void * new_buf(size_t bufsz);
void del_buf(void * buf, size_t bufsz);
void rfs_set_driver(driver_t * drvp);
void rfs_set_device(device_t devp, driver_t drvp);
drvstus_t rfs_entry(driver_t * drvp, uint_t val, void * p);
drvstus_t rfs_exit(driver_t * drvp, uint_t val, void * p);
drvstus_t rfs_open(device_t * devp, void * iopack);
drvstus_t rfs_close(device_t * devp, void * iopack);
drvstus_t rfs_read(device_t * devp, void * iopack);
drvstus_t rfs_write(device_t * devp, void * iopack);
drvstus_t rfs_lseek(device_t * devp, void * iopack);
drvstus_t rfs_ioctrl(device_t * devp, void * iopack);
drvstus_t rfs_dev_start(device_t * devp, void * iopack);
drvstus_t rfs_dev_stop(device_t * devp, void * iopack);
drvstus_t rfs_set_powerstus(device_t * devp, void * iopack);
drvstus_t rfs_enum_dev(device_t * devp, void * iopack);
drvstus_t rfs_flush(device_t * devp, void * iopack);
drvstus_t rfs_new_file(device_t *devp, char_t * fname, uint_t flg);
drvstus_t rfs_del_file(device_t *devp, char_t * fname, uint_t flg);
drvstus_t rfs_read_file(device_t * devp, void * iopack);
drvstus_t rfs_write_file(device_t * devp, void * iopack);
drvstus_t rfs_open_file(device_t * devp, void * iopack);
drvstus_t rfs_close_file(device_t * devp, void * iopack);
sint_t rfs_strcmp(char_t * str_s, char_t * str_d);
sint_t rfs_strlen(char_t * str_s);
sint_t rfs_strcpy(char_t * str_s, char_t * str_d);
void init_rfs(device_t * devp);
void rfs_fmat(device_t * devp);
drvstus_t rfs_writefileblk(device_t * devp, fimgrhd_t fmp, void * buf, uint_t len);
drvstus_t rfs_readfileblk(device_t * devp, fimgrhd_t fmp, void * buf, uint_t len);
drvstus_t rfs_closefileblk(device_t * devp, void * fblkp);
void * rfs_openfileblk(device_t * devp, char_t * fname);
drvstus_t rfs_new_dirfileblk(device_t * devp, char_t * fname, uint_t filetype, uint_t val);
drvstus_t rfs_del_dirfileblk(device_t * devp, char_t * fname, uint_t filetype, uint_t val);
sint_t del_dirfileblk_core(device_t * devp, char_t * fname);
void * get_rootdirfile_blk(device_t * devp);
void del_rootdirfile_blk(device_t * devp, void * blkp);
rfsdir_t * get_rootdir(device_t * devp);
void del_rootdir(device_t * devp, rfsdir_t * rdir);
void del_superblk(device_t * devp, rfssublk_t * sbp);
u8_t * get_bitmapblk(device_t * devp);
void del_bitmapblk(device_t * devp, u8_t * bitmap);
uint_t rfs_new_blk(device_t * devp);
void rfs_del_blk(device_t * devp, uint_t blknr);
sint_t rfs_chkfilepath(char_t * fname);
sint_t rfs_ret_fname(char_t * buf, char_t * fpath);
sint_t rfs_chkfileisindev(device_t * devp, char_t * fname);
bool_t create_superblk(device_t * devp);
bool_t create_bitmap(device_t * devp);
bool_t create_rootdir(device_t * devp);
void chk_rfsbitmap(device_t * devp);
void test_allocblk(device_t * devp);
void test_dir(device_t * devp);
void test_rfs(device_t * devp);
void test_file(device_t * devp);

#endif
