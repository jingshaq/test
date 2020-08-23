#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	char buf[]="Hello!";

	int dev_fd=open("/dev/chardriverdemo",O_RDWR | O_NONBLOCK);
	if(dev_fd < 0){
		printf("open error!");
		return 0;
	}
	if(!write(dev_fd,buf,6))
		printf("write error");
	if(!write(dev_fd,buf,6))
		printf("write error");

	return 0;

}
