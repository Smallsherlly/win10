#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "struct.h"
#include <signal.h>

int main(int argc,char* argv[])	
{
	struct account acc = {};
	struct msg msg = {};
	struct msg msg2 = {};
	
	//获取消息队列
	key_t key1 = ftok(".",11);
	key_t key2 = ftok(".",22);
	int msgid_s = msgget(key1,0);
	int msgid_r = msgget(key2,0);
	while(1)
	{
		if(msgrcv(msgid_r,&msg,sizeof(msg.acc),110,IPC_NOWAIT)!=-1)
		{
			msgsnd(msgid_s,&msg,sizeof(msg.acc),0);
			printf("_%d进程已关闭\n",msg.type);		
			return 0;
		}
		if(msgrcv(msgid_r,&msg,sizeof(msg.acc),111,IPC_NOWAIT)!=-1)
		{
			//读取并生成账户号码
			FILE* fp = fopen("./data/id.txt","r+");
			if(0 > fp)
			{
				perror("fopen");
				return -1;
			}
			int id = 0;
			fscanf(fp,"%d",&id);
			id++;
			fseek(fp,0,SEEK_SET);
			fprintf(fp,"%d",id);
			fclose(fp);
			
			msg.acc.id[0] = id;
			msgsnd(msgid_s,&msg,sizeof(msg.acc),0);
			//保存在.bat文件中
			char s[30] = {};
			sprintf(s,"%s%d%s","./data/",id,".bat");
			fp = fopen(s,"w+");
			fwrite(&msg.acc,sizeof(msg.acc),1,fp);
			fclose(fp);
		}
	}
	
	return 0;
}
