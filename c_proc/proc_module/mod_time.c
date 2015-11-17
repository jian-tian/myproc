#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/unistd.h>
#include <linux/time.h>
#include <asm/uaccess.h>
#include <linux/sched.h>
#include <asm/cacheflush.h>
#include <asm/semaphore.h>
#include <asm/pgtable.h>

#define __NR_pedagogictime 238

MODULE_DESCRIPTION("My sys_pedagogictime()");
MODULE_AUTHOR("Your Name:),(C) 2002, GPLv2 or later");

static unsigned long **sys_call_table;
static int (*anything_saved)(void);

static int sys_pedagogictime(struct timeval *tv)
{
    struct timeval ktv;
    try_module_get(THIS_MODULE);
    do_gettimeofday(&ktv);
    if (copy_to_user(tv, &ktv, sizeof(ktv))) {
	module_put(THIS_MODULE);
	return -EFAULT;
    }
    printk(KERN_ALERT"Pid %ld called sys_gettimeofday().\n", (long)current->pid);
    module_put(THIS_MODULE);

    return 0;
}

static void set_addr_rw(unsigned long addr)
{
    unsigned int level;
    pte_t *pte = lookup_address(addr, &level);
    if (pte->pte &~ _PAGE_RW)
	pte->pte |= _PAGE_RW;
}

static void set_addr_ro(unsigned long addr)
{
    unsigned int level;
    pte_t *pte = lookup_address(addr, &level);
    pte->pte = pte->pte &~ _PAGE_RW;
}

static int set_page_rw(long unsigned int __addr)
{
    struct page *pg;
    pgprot_t prot;
    pg = virt_to_page(__addr);
    prot.pgprot = VM_READ | VM_WRITE;
    //return set_pages_rw(pg, 1);
    return change_page_attr(pg, 1, prot);
}

static int set_page_ro(long unsigned int __addr)
{
    struct page *pg;
    pgprot_t prot;
    pg = virt_to_page(__addr);
    prot.pgprot = VM_READ;
    return change_page_attr(pg, 1, prot);
}

int __init init_addsyscall(void)
{
    sys_call_table = (unsigned long **)0xc0635a20;
    //set_page_rw((long unsigned int)sys_call_table);
    //set_memory_rw((unsigned long)sys_call_table, 1);
    set_addr_rw((unsigned long)sys_call_table);

    anything_saved = (int (*)(void))(sys_call_table[__NR_pedagogictime]);

    sys_call_table[__NR_pedagogictime] = (unsigned long *)sys_pedagogictime;

    printk(KERN_INFO "addsycall init\n");

    return 0;
}

void __exit exit_addsyscall(void)
{
    sys_call_table[__NR_pedagogictime] = (unsigned long *)anything_saved;
    //set_page_ro((long unsigned int)sys_call_table);
    //set_memory_ro((unsigned long)sys_call_table, 1);
    set_addr_ro((unsigned long)sys_call_table);

    printk(KERN_INFO "addsycall exit\n");
}

module_init(init_addsyscall);
module_exit(exit_addsyscall);
