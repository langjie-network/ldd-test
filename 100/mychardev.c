#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>

#define DEVICE_NAME "mychardev"
#define BUF_SIZE 1024

static char *buffer;
static int mychardev_major = 0;
static struct cdev *mychardev_cdev;

static int mychardev_open(struct inode *inode, struct file *file)
{
    return 0;
}

static ssize_t mychardev_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
int ret;
if (*ppos >= BUF_SIZE)
return 0;
if (count > BUF_SIZE - *ppos)
count = BUF_SIZE - *ppos;

ret = copy_to_user(buf, buffer + *ppos, count);
if (ret == 0) {
*ppos += count;
return count;
}
return -EFAULT;
}

static struct file_operations mychardev_fops = {
        .owner = THIS_MODULE,
        .open = mychardev_open,
        .read = mychardev_read,
};

static int __init mychardev_init(void)
{
    int result;
    dev_t dev = 0;

    result = alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME);
    if (result < 0) {
        printk(KERN_WARNING "mychardev: can't get major number\n");
        return result;
    }
    mychardev_major = MAJOR(dev);

    mychardev_cdev = cdev_alloc();
    if (!mychardev_cdev) {
        result = -ENOMEM;
        goto fail;
    }
    mychardev_cdev->ops = &mychardev_fops;

    result = cdev_add(mychardev_cdev, dev, 1);
    if (result) {
        printk(KERN_WARNING "mychardev: can't add device\n");
        goto fail;
    }

    buffer = kmalloc(BUF_SIZE, GFP_KERNEL);
    if (!buffer) {
        result = -ENOMEM;
        goto fail;
    }
    memset(buffer, 0, BUF_SIZE);

    printk(KERN_INFO "Mychardev module loaded with major number %d\n", mychardev_major);
    return 0;

    fail:
    if (mychardev_cdev) {
        cdev_del(mychardev_cdev);
    }
    if (buffer) {
        kfree(buffer);
    }
    unregister_chrdev_region(dev, 1);
    return result;
}

static void __exit mychardev_exit(void)
{
    dev_t dev = MKDEV(mychardev_major, 0);

    cdev_del(mychardev_cdev);
    kfree(buffer);
    unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "Mychardev module unloaded\n");
}

module_init(mychardev_init);
module_exit(mychardev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple character device driver");
MODULE_VERSION("0.1");