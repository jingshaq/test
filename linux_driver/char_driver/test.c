#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	int ret = 0, i = 0;
	char write_buf[]="Hello!";
	char read_buf[10] = {0};

	int dev_fd=open("/dev/chardriverdemo",O_RDWR | O_NONBLOCK);
	if(dev_fd < 0){
		printf("open error!");
		return 0;
	}
	
	for(i=0; i<10; i++){
		if(!write(dev_fd,write_buf,6))
			printf("write error");
	}

	lseek(dev_fd, 0, SEEK_SET); // driver中没有修改offset, 因此这里必须重新定位到文件开始

	while(1){
		memset(read_buf, 0, 10);
		ret = read(dev_fd, read_buf, 9);
		printf("ret = %d\n", ret);
		if(ret <= 0)
			break;
		else
			printf("read: %s\n", read_buf);
	}
	

	return 0;

}
