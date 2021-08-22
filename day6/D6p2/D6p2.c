#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/timer.h>

#define TIMEOUT 2000

static struct timer_list mytimer;
unsigned int i = 0;

//timer callback function
static void mytimer_callback(struct timer_list *timer)
{
	printk("In timer callback function %d\n",i++);
	printk("%s called %ld \n",__func__, jiffies);

	//re-enable the timer which will make timer as periodic
	
	mod_timer(&mytimer, jiffies + msecs_to_jiffies(TIMEOUT));
}

static int __init kernel_init(void)
{
	int ret;

	printk("timer module loaded %s\n",__func__);

	//set timer to call timer callback function

	timer_setup(&mytimer, mytimer_callback,0);
	printk("%s: setup timer to fire in 25 %ld \n",__func__, jiffies);

        //set timer interval to base on timeout macro
	ret = mod_timer(&mytimer, jiffies + msecs_to_jiffies(TIMEOUT));
	if(ret)
		printk("%s: Timer firing failed\n", __func__);
	return 0;
}

static void __exit kernel_exit(void)
{
	int ret;

	ret = del_timer(&mytimer);
	if(ret)
		printk("%s: The timer is still in use \n",__func__);
	printk("%s: Timer module is unloaded\n",__func__);
}



MODULE_LICENSE("GPL");
module_init(kernel_init);
module_exit(kernel_exit);
