#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ztop");
MODULE_DESCRIPTION("Hello world module");

static __init int initialize(void)
{
    printk(KERN_EMERG "[ztop][hello_module] initialize (KERN_EMERG)");
    printk(KERN_ALERT "[ztop][hello_module] initialize (KERN_ALERT)");
    printk(KERN_CRIT "[ztop][hello_module] initialize (KERN_CRIT)");
    printk(KERN_ERR "[ztop][hello_module] initialize (KERN_ERR)");
    printk(KERN_WARNING "[ztop][hello_module] initialize (KERN_WARNING)");
    printk(KERN_NOTICE "[ztop][hello_module] initialize (KERN_NOTICE)");
    printk(KERN_WARNING "[ztop][hello_module] initialize (KERN_WARNING)");
    printk(KERN_INFO "[ztop][hello_module] initialize (KERN_INFO)");
    printk(KERN_DEBUG "[ztop][hello_module] initialize (KERN_DEBUG)");
    printk(KERN_DEFAULT "[ztop][hello_module] initialize (KERN_DEFAULT)");
    printk(KERN_CONT "[ztop][hello_module] initialize (KERN_CONT)");
    printk("[ztop][hello_module] initialize");
    return 0;
}


static __exit void cleanup(void)
{
    printk(KERN_EMERG "[ztop][hello_module] cleanup (KERN_EMERG)");
    printk(KERN_ALERT "[ztop][hello_module] cleanup (KERN_ALERT)");
    printk(KERN_CRIT "[ztop][hello_module] cleanup (KERN_CRIT)");
    printk(KERN_ERR "[ztop][hello_module] cleanup (KERN_ERR)");
    printk(KERN_WARNING "[ztop][hello_module] cleanup (KERN_WARNING)");
    printk(KERN_NOTICE "[ztop][hello_module] cleanup (KERN_NOTICE)");
    printk(KERN_WARNING "[ztop][hello_module] cleanup (KERN_WARNING)");
    printk(KERN_INFO "[ztop][hello_module] cleanup (KERN_INFO)");
    printk(KERN_DEBUG "[ztop][hello_module] cleanup (KERN_DEBUG)");
    printk(KERN_DEFAULT "[ztop][hello_module] cleanup (KERN_DEFAULT)");
    printk(KERN_CONT "[ztop][hello_module] cleanup (KERN_CONT)");
    printk("[ztop][hello_module] cleanup");
}

module_init(initialize);
module_exit(cleanup);


