#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/interrupt.h>

struct tasklet_struct tasklet;

char c[100]; 

dev_t mydev;
int mychar_open(struct inode *inode,struct file *flip);
int mychar_release(struct inode *inode, struct file *flip);
ssize_t mychar_read(struct file *flip, char __user *Ubuff, size_t count, loff_t *offp);

struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open = mychar_open,
	.release = mychar_release,
	.read = mychar_read,
};

struct cdev *my_cdev;




void tasklet_func(unsigned long data)
{
	printk("Scheduling tasklet\n");
	printk("data %s\n",data);
	strcpy(c,data);
}

static int __init mychar_init(void)
{
	int r;
	int MAJOR,MINOR;
	r = alloc_chrdev_region(&mydev,0,1,"mychar");
	if(r<0)
	{
		printk("region requested is not available\n");
		return -1;
	}
	MAJOR = MAJOR(mydev);
	MINOR = MINOR(mydev);
	printk("Major number %d\t Mini=or number %d\n",MAJOR,MINOR);
	my_cdev = cdev_alloc();
	my_cdev->ops = &fops;
	r = cdev_add(my_cdev,mydev,1);
	if(r<0)
	{
		printk("Device not created\n");
		return -1;
	}

	tasklet_init(&tasklet, tasklet_func,"tasklet" );

	tasklet_schedule(&tasklet);  //schedule tasklet to run

	return 0;
}

static void __exit mychar_exit(void)
{
	int MAJOR,MINOR;

	MAJOR = MAJOR(mydev);
	MINOR = MINOR(mydev);
	printk("Major number %d\t Minor number %d\n",MAJOR,MINOR);
	unregister_chrdev_region(mydev,1);
	cdev_del(my_cdev);
	printk("Unregister\n");
	tasklet_kill(&tasklet);
}

int mychar_open(struct inode *inode,struct file *flip)
{
	printk("In open system call\n");
	return 0;
}

int mychar_release(struct inode *inode,struct file *flip)
{
	printk("In release system call\n");
	return 0;

}

ssize_t mychar_read(struct file *flip, char __user *Ubuff, size_t count, loff_t *offp)
{
	tasklet_schedule(&tasklet);

	unsigned long r;
	ssize_t ret;

	//r = copy_to_user((char *)Ubuff, (char *)&c, sizeof(kbuff));
	r = copy_to_user((char *)Ubuff, (char *)c, sizeof(c));

	memset(c,0,sizeof(c));
	if(r==0)
	{
		printk("read data successfully\n");
		ret = count;
		return ret;
	}
	else
	{
		printk("Error\n");
		ret = -EFAULT;
		return ret;
	}
}


MODULE_LICENSE("GPL");
module_init(mychar_init);
module_exit(mychar_exit);
