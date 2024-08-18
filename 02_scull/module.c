#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/list.h>

#include "fops.h"
#include "module.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ztop");
MODULE_DESCRIPTION("scull char device");

static int dev_major = -1;
static int dev_minor = 1;
static unsigned num_dev = 3;

module_param(dev_major,int,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
module_param(dev_minor,int,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
module_param(num_dev,uint,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

MODULE_PARM_DESC(dev_major, "Major number if not given will be allocated.");
MODULE_PARM_DESC(dev_minor, "Major number");
MODULE_PARM_DESC(num_dev, "Number of devices");

static struct file_operations scull_fops = 
{
    .owner = THIS_MODULE,
    .read = scull_read,
    .write = scull_write,
    .open = scull_open,
    .release = scull_release
};


static struct scull_dev_data scull_dev_data;
static void scull_dev_data__initialize(void)
{
    scull_dev_data.major = dev_major;
    scull_dev_data.minor = dev_minor;
    scull_dev_data.num_devices = num_dev;
    scull_dev_data.dev = 0;
}

static int scull_dev_data__allocate_dev(void)
{
    scull_dev_data.dev = kmalloc(sizeof(struct scull_dev*) * scull_dev_data.num_devices, GFP_KERNEL);
    if(!scull_dev_data.dev)
    {
        printk(KERN_INFO "[%s] unable to allocated devices [scull_dev_data.num_devices:%d]",
            MODULE_NAME,scull_dev_data.num_devices);
        return -1;
    }
    for(int i = 0;i < scull_dev_data.num_devices;i++)
    {
        scull_dev_data.dev[i] = kmalloc(sizeof(struct scull_dev),GFP_KERNEL);
        scull_dev_data.dev[i]->block_counter = 0;
        mutex_init(&(scull_dev_data.dev[i]->mutex));
        cdev_init(&(scull_dev_data.dev[i]->cdev),&scull_fops);
        scull_dev_data.dev[i]->cdev.owner = THIS_MODULE;
        printk(KERN_INFO "[%s] allocated %i",MODULE_NAME,i);
    }
    return 0;
}

static void scull_dev_data__print(void)
{
    printk(KERN_INFO "[%s] scull_dev_data(%d,%d,%d,%p)",
            MODULE_NAME,
            scull_dev_data.major,
            scull_dev_data.minor,
            scull_dev_data.num_devices,
            scull_dev_data.dev);
}

static void scull_dev_data__unregister(void)
{
    dev_t devno;
	devno = MKDEV(scull_dev_data.major, scull_dev_data.minor);
	unregister_chrdev_region(devno, scull_dev_data.num_devices);
}

static void scull_dev_data__deallocate(void)
{
    if(scull_dev_data.dev)
    {
        for(int i = 0;i < scull_dev_data.num_devices;i++)
        {    
            if(scull_dev_data.dev[i])
                kfree(scull_dev_data.dev[i]);
        }
        kfree(scull_dev_data.dev);
        scull_dev_data.dev = 0x0;
    }
}

static __init int initialize(void)
{
    int error = 0;
    dev_t devno;
    scull_dev_data__initialize();
    scull_dev_data__print();
    
    if(scull_dev_data.major == -1)
        error = alloc_chrdev_region(
                &devno, 
                scull_dev_data.minor, 
                scull_dev_data.num_devices, 
                MODULE_NAME);
    else
    {   
        devno = MKDEV(scull_dev_data.major,scull_dev_data.minor); 
        error = register_chrdev_region(devno, scull_dev_data.num_devices, MODULE_NAME);
    }

    if(error)
    {
        printk(KERN_ERR "[%s] unable to get chrdev (error:%d)",MODULE_NAME,error);
        return error;
    }
    

    scull_dev_data.major = MAJOR(devno);
    scull_dev_data.minor = MINOR(devno);

    error = scull_dev_data__allocate_dev();
    if(error)
    {
        scull_dev_data__unregister();
    }

    scull_dev_data__print();
    return error;
}


static __exit void cleanup(void)
{
    printk(KERN_INFO "[%s] cleanup(%s,%d)",MODULE_NAME,current->comm,current->pid);
    scull_dev_data__deallocate();
    scull_dev_data__unregister();
}

module_init(initialize);
module_exit(cleanup);


