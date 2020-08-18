/*                                                     
 * $Id: hellop.c,v 1.4 2004/09/26 07:02:43 gregkh Exp $ 
 */                                                    
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("Dual BSD/GPL");

/*                                                        
 * These lines, although not shown in the book,           
 * are needed to make hello.c run properly even when      
 * your kernel has version support enabled                
 */                                                       
                                                          

/*
 * single parameter. insmod command line parameter will replace this value.
 */
static char *whom = "world";
module_param(whom, charp, S_IRUGO);

static int howmany = 1;
module_param(howmany, int, S_IRUGO);


/*
 * array parameter. insmod command line parameter will replace this value.
 */
static int array[5] = {10, 100, 1000, 10000, 100000};
static int num = 5;
module_param_array(array, int, &num, S_IRUGO);

static int hello_init(void)
{
	int i;
	for (i = 0; i < howmany; i++)
		printk(KERN_ALERT "(%d) Hello, %s\n", i, whom);

	printk(KERN_ALERT "num = %d", num);
	for (i = 0; i < num; i++)
		printk(KERN_ALERT "array[%d] = %d", i, array[i]);

	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);
