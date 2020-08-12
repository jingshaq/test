#include <linux/init.h>             
#include <linux/module.h>          
#include <linux/kernel.h>   

MODULE_LICENSE("GPL");              

static int __init hello_world_init(void)
{
    printk(KERN_DEBUG "hello world!!!\n");
    return 0;
}

static void __exit hello_world_exit(void)
{
    printk(KERN_DEBUG "goodbye world!!!\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);
