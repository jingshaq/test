#include <linux/module.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <asm/io.h>
#include <asm/system.h>
#include <asm/uaccess.h>

#define CHARDRIVERDEMO_SIZE    0x1000    /*全局内存最大4K字节*/
#define MEM_CLEAR 0x1  /*清0全局内存*/
#define CHARDRIVERDEMO_MAJOR 211    /*预设的chardriverdemo的主设备号*/

static chardriverdemo_major = CHARDRIVERDEMO_MAJOR;
/*chardriverdemo设备结构体*/
struct chardriverdemo_dev
{
	struct cdev cdev; /*cdev结构体*/
	unsigned char mem[CHARDRIVERDEMO_SIZE]; /*全局内存*/
	struct semaphore sem; /*并发控制用的信号量*/
};

struct chardriverdemo_dev *chardriverdemo_devp; /*设备结构体指针*/

/*文件打开函数*/
int chardriverdemo_open(struct inode *inode, struct file *filp)
{
	/*将设备结构体指针赋值给文件私有数据指针*/
	filp->private_data = chardriverdemo_devp;
	return 0;
}

/*文件释放函数*/
int chardriverdemo_release(struct inode *inode, struct file *filp)
{
	return 0;
}

/* ioctl设备控制函数 */
static int chardriverdemo_ioctl(struct inode *inodep, struct file *filp, unsigned
		int cmd, unsigned long arg)
{
	struct chardriverdemo_dev *dev = filp->private_data; /*获得设备结构体指针*/

	switch (cmd)
	{
	case MEM_CLEAR:
		if (down_interruptible(&dev->sem))
		{
			return  - ERESTARTSYS;
		}
		memset(dev->mem, 0, CHARDRIVERDEMO_SIZE);
		up(&dev->sem); //释放信号量

		printk(KERN_INFO "chardriverdemo is set to zero\n");
		break;

	default:
		return  - EINVAL;
	}
	return 0;
}

/*读函数*/
static ssize_t chardriverdemo_read(struct file *filp, char __user *buf, size_t size,
		loff_t *ppos)
{
	unsigned long p =  *ppos;
	unsigned int count = size;
	int ret = 0;
	struct chardriverdemo_dev *dev = filp->private_data; /*获得设备结构体指针*/

	/*分析和获取有效的写长度*/
	if (p >= CHARDRIVERDEMO_SIZE)
		return count ?  - ENXIO: 0;
	if (count > CHARDRIVERDEMO_SIZE - p)
		count = CHARDRIVERDEMO_SIZE - p;

	if (down_interruptible(&dev->sem))
	{
		return  - ERESTARTSYS;
	}

	/*内核空间->用户空间*/
	if (copy_to_user(buf, (void*)(dev->mem + p), count))
	{
		ret =  - EFAULT;
	}
	else
	{
		*ppos += count;
		ret = count;

		printk(KERN_INFO "read %d bytes(s) from %d\n", count, p);
	}
	up(&dev->sem); //释放信号量

	return ret;
}

/*写函数*/
static ssize_t chardriverdemo_write(struct file *filp, const char __user *buf,
		size_t size, loff_t *ppos)
{
	unsigned long p = *ppos;
	unsigned int count = size;
	int ret = 0;

	struct chardriverdemo_dev *dev = filp->private_data; /*获得设备结构体指针*/

	/*分析和获取有效的写长度*/
	if (p >= CHARDRIVERDEMO_SIZE)
		return count ?  - ENXIO: 0;
	if (count > CHARDRIVERDEMO_SIZE - p)
		count = CHARDRIVERDEMO_SIZE - p;

	if (down_interruptible(&dev->sem))//获得信号量
	{
		return  - ERESTARTSYS;
	}
	/*用户空间->内核空间*/


	if (copy_from_user(dev->mem + p, buf, count))
		ret =  - EFAULT;
	else
	{
		*ppos +=count;
		ret = count;

		printk(KERN_INFO "written %d bytes(s) from %d\n", count, p);
	}
	up(&dev->sem); //释放信号量
	return ret;
}

/* seek文件定位函数 */
static loff_t chardriverdemo_llseek(struct file *filp, loff_t offset, int orig)
{
	loff_t ret = 0;
	switch (orig)
	{
	case 0:   /*相对文件开始位置偏移*/
		if (offset < 0)
		{
			ret =  - EINVAL;
			break;
		}
		if ((unsigned int)offset > CHARDRIVERDEMO_SIZE)
		{
			ret =  - EINVAL;
			break;
		}
		filp->f_pos = (unsigned int)offset;
		ret = filp->f_pos;
		break;
	case 1:   /*相对文件当前位置偏移*/
		if ((filp->f_pos + offset) > CHARDRIVERDEMO_SIZE)
		{
			ret =  - EINVAL;
			break;
		}
		if ((filp->f_pos + offset) < 0)
		{
			ret =  - EINVAL;
			break;
		}
		filp->f_pos += offset;
		ret = filp->f_pos;
		break;
	default:
		ret =  - EINVAL;
		break;
	}
	return ret;
}

/*文件操作结构体*/
static const struct file_operations chardriverdemo_fops =
{
	.owner = THIS_MODULE,
	.llseek = chardriverdemo_llseek,
	.read = chardriverdemo_read,
	.write = chardriverdemo_write,
	.ioctl = chardriverdemo_ioctl,
	.open = chardriverdemo_open,
	.release = chardriverdemo_release,
};

/*初始化并注册cdev*/
static void chardriverdemo_setup_cdev(struct chardriverdemo_dev *dev, int index)
{
	int err, devno = MKDEV(chardriverdemo_major, index);

	cdev_init(&dev->cdev, &chardriverdemo_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &chardriverdemo_fops;
	err = cdev_add(&dev->cdev, devno, 1);
	if (err)
		printk(KERN_NOTICE "Error %d adding LED%d", err, index);
}

/*设备驱动模块加载函数*/
int chardriverdemo_init(void)
{
	int result;
	dev_t devno = MKDEV(chardriverdemo_major, 0);

	/* 申请设备号*/
	if (chardriverdemo_major)
		result = register_chrdev_region(devno, 1, "chardriverdemo");
	else  /* 动态申请设备号 */
	{
		result = alloc_chrdev_region(&devno, 0, 1, "chardriverdemo");
		chardriverdemo_major = MAJOR(devno);
	}
	if (result < 0)
		return result;

	/* 动态申请设备结构体的内存*/
	chardriverdemo_devp = kmalloc(sizeof(struct chardriverdemo_dev), GFP_KERNEL);
	if (!chardriverdemo_devp)    /*申请失败*/
	{
		result =  - ENOMEM;
		goto fail_malloc;
	}
	memset(chardriverdemo_devp, 0, sizeof(struct chardriverdemo_dev));

	chardriverdemo_setup_cdev(chardriverdemo_devp, 0);
	init_MUTEX(&chardriverdemo_devp->sem);   /*初始化信号量*/
	return 0;

fail_malloc: unregister_chrdev_region(devno, 1);
			 return result;
}

/*模块卸载函数*/
void chardriverdemo_exit(void)
{
	cdev_del(&chardriverdemo_devp->cdev);   /*注销cdev*/
	kfree(chardriverdemo_devp);     /*释放设备结构体内存*/
	unregister_chrdev_region(MKDEV(chardriverdemo_major, 0), 1); /*释放设备号*/
}

MODULE_AUTHOR("Song Baohua");
MODULE_LICENSE("Dual BSD/GPL");

module_param(chardriverdemo_major, int, S_IRUGO);

module_init(chardriverdemo_init);
module_exit(chardriverdemo_exit);
