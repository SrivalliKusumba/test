#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
	int fd;
	char kbuff[100];
	fd = open("/dev/mychar",O_RDWR,0777);
	if(fd<0)
	{
		printf("Error opening file\n");
		exit(1);
	}
	read(fd,kbuff,100);
	printf("\nData read from kernel is %s\n",kbuff);
	close(fd);
}
