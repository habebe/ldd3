#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("ztop");
MODULE_DESCRIPTION("Hello world module");

static char* param_charp = "default_charp";
static int param_int = 1;

module_param(param_charp,charp,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
module_param(param_int,int,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

MODULE_PARM_DESC(param_charp, "A charp parameter");
MODULE_PARM_DESC(param_int, "An int parameter");

static __init int initialize(void)
{
    printk(KERN_EMERG "[ztop][hello_module] initialize param=(param_charp:'%s' param_int:%d)",param_charp,param_int);


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

    printk(KERN_INFO "[ztop][hello_module] initialize process(%s,%d)",current->comm,current->pid);
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


