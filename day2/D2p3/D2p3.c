#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");

static int a=20;
static int b=10;

static char* charvar = "sub";

char* add_ch = "add";
char* sub_ch = "sub";
char* mul_ch = "mul";
char* div_ch = "div";

module_param(charvar, charp, S_IRUGO);
module_param(add_ch,charp,S_IRUGO);
module_param(sub_ch,charp,S_IRUGO);
module_param(mul_ch,charp,S_IRUGO);
module_param(div_ch,charp,S_IRUGO);
module_param(a, int, S_IRUGO);
module_param(b, int, S_IRUGO);

static int add(int a,int b)
{
	return (a+b);
}

static int sub(int a,int b)
{
	return (a-b);
}

static int mul(int a,int b)
{
	return (a*b);
}

static int div(int a,int b)
{
	return (a/b);
}

EXPORT_SYMBOL(add);
EXPORT_SYMBOL(sub);
EXPORT_SYMBOL(mul);
EXPORT_SYMBOL(div);

static int __init op_init(void)
{
	if(charvar==add_ch)
	{
		printk("addition\n");
		printk("addition result is %d\n",add(a,b));
	}
	if(charvar==sub_ch)
	{
		printk("subtraction\n");
		printk("Subtraction result is %d\n",sub(a,b));
	}
	if(charvar==mul_ch)
	{
		printk("Multiplication\n");
		printk("Multiplication result is %d\n",mul(a,b));
	}
	if(charvar==div_ch)
	{
		printk("Division\n");
		printk("Division result is %d\n",div(a,b));
	}
	return 0;
}

static void __exit op_exit(void)
{
	printk("Exit\n");
}

module_init(op_init);
module_exit(op_exit);















