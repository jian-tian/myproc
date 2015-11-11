#ifndef __KERNEL__
#define __KERNEL__
#endif

#ifndef MODULE
#define MODULE
#endif

#define __KERNEL_SYSCALLS__

#include <linux/module.h>

#include <linux/init.h>     //宏 module_init()和module_exit()在头文件linux/init.h定义
MODULE_LICENSE("GPL");

int init_module(void)
{
    printk("hello world!\n");
    return 0;
}

void cleanup_module(void)
{
    printk("Goodbye!\n");
}

