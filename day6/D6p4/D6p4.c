#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/sched.h>
#include<linux/workqueue.h>
#include<linux/types.h>

struct workqueue_struct *workqueue;

dev_t mydev;
int mychar_open(struct inode *inode,struct file *flip);
int mychar_release(struct inode *inode,struct file *flip);
ssize_t mychar_read(struct file *flip, char __user *Ubuff, size_t count, loff_t *offp);
char kbuff[100]; 

struct work_struct work;

struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open = mychar_open,
	.release = mychar_release,
	.read = mychar_read,
};

struct cdev *my_cdev;

void wrq_func(struct work_struct *work)
{
	strcpy(kbuff,"in");
	printk("In workqueue work function\n");
}

static int __init char_init(void)
{
	int r;
	int MAJOR,MINOR;
	r = alloc_chrdev_region(&mydev,0,1,"mychar");
	if(r<0)
	{
		printk("Requested region is not available\n");
		return -1;
	}
	MAJOR = MAJOR(mydev);
	MINOR = MINOR(mydev);
	printk("Major number %d\t Minor numeber %d\n",MAJOR,MINOR);
	my_cdev = cdev_alloc();
	my_cdev->ops = &fops;
	r = cdev_add(my_cdev,mydev,1);
	if(r<0)
	{
		printk("Device not created\n");
		return -1;
	}
	workqueue = create_singlethread_workqueue("Sample workqueue");
	INIT_WORK(&work, wrq_func);
	queue_work(workqueue, &work);


	return 0;
}

static void __exit char_exit(void)
{
	int MAJOR,MINOR;

	MAJOR = MAJOR(mydev);
	MINOR = MINOR(mydev);
	printk("Major number %d\t Minor number %d \n",MAJOR,MINOR);

	destroy_workqueue(workqueue);
       	unregister_chrdev_region(mydev,1);
	cdev_del(my_cdev);
	printk("unregister\n");
}

int mychar_open(struct inode *inode, struct file *flip)
{
	printk("In open system call\n");
	return 0;
}

int mychar_release(struct inode *inode, struct file *flip)
{
	printk("In release system call\n");
	return 0;
}

ssize_t mychar_read(struct file *flip,char __user *Ubuff, size_t count, loff_t *offp)
{
	//char c[100];
	queue_work(workqueue, &work);
	//memcpy(c,kbuff,sizeof(kbuff));
	unsigned long r;
	ssize_t ret;
	int cnt;

	cnt = copy_to_user((char *)Ubuff, (char *)kbuff, sizeof(kbuff));

	memset(kbuff, 0, sizeof(kbuff));


	if(r==0)
	{
		printk("Read data successfully\n");
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
module_init(char_init);
module_exit(char_exit);

