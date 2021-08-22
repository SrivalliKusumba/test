#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
	int fd;
	char buff[100];
	fd = open("/dev/mychar",O_RDONLY);
	if(fd<0)
	{
		printf("Error opening file\n");
		exit(1);
	}
	read(fd,buff,sizeof(buff));
	printf("Data read from kernel : %s\n",buff);
	close(fd);
	return 0;
}
