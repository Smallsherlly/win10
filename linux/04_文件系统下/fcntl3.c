#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int wlock(int fd,size_t len,int wait)
{
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = len;
	lock.l_pid = -1;
	fcntl(fd,F_GETLK,&lock);
	if(lock.l_type == F_UNLCK)
	{
		printf("未加锁！\n");
		return 0;
	}
	else if(lock.l_type == F_WRLCK)
	{
		printf("当前为只读！\n");
		return -1;
	}
	else if(lock.l_type == F_RDLCK)
	{
		printf("当前为只写！\n");
		return -1;
	}
}

int main()
{
	int fd = open("fcntl.bin",O_WRONLY|O_CREAT);
	
	wlock(fd,20,0);
	scanf("%*c");

	return 0;
}

