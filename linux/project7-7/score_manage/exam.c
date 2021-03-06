#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	//创建文件
	int fd = open("data.txt",O_RDWR|O_CREAT|O_TRUNC,0666);
	if(0 > fd)
	{
		perror("open");
		return -1;
	}

	typedef struct Student
	{
		char name[20];
		char sex;
		short age;
	}Student; 
	Student zhaoyun = {"赵云",'m',88};
	Student zhao = {"zhan",'f',99};
	//创建缓冲区
	char buf[1024] = {};

	//把要写的数据拼接入缓冲区
	sprintf(buf,"%s %c %hd\n",zhaoyun.name,zhaoyun.sex,zhaoyun.age);

	//把缓冲区写入文件

	int ret = write(fd,buf,strlen(buf));
	if(0 > ret)
	{
		perror("write");
		return -1;
	}
	
	printf("希望写入%d字节，实际写入%d字节\n",strlen(buf),ret);
	
	ret = close(fd);
	if(0 > ret)
	{
		perror("close");
		return -1;
	}
	
	printf("关闭文件成功！\n");
	return 0;
}
