#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");

static int intvar = 10;

module_param(intvar, int, S_IRUGO);

static int __init param_init(void)
{
	printk(KERN_ALERT "\n The value of int variable is %d\n", intvar);
	return 0;
}

static void __exit param_exit(void)
{
	printk(KERN_ALERT "\n Goodbye");
}

module_init(param_init);
module_exit(param_exit);
