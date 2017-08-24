#include "struct.h"

int ret = 0;
int sockfd = 0;
int inum = 0;

int login(MSG* msg,int fd)
{
	DIR* dp = opendir ("./data");
	MSG msg2;
	if (! dp) 
	{
	 	perror ("opendir");
	 	return -1;
	}
	char s[30] = {};
	struct dirent* de;
	for (de = readdir (dp); de; de = readdir (dp)) 
	{
		if(de->d_name[0]!='.')
		{
			sprintf(s,"%ld%s",msg->acc.id[0],".bat");
				
			if(0 == strcmp(s,de->d_name))
			{
				
				sprintf(s,"%s%ld%s","./data/",msg->acc.id[0],".bat");
				FILE* fp = fopen(s,"r");
				
				fread(&msg2.acc,sizeof(msg->acc),1,fp);
			
				
				if(strcmp(msg->acc.psw,msg2.acc.psw)==0)
				{
					
					msg->type = 1;
					fclose(fp);
					return 1;
				}
				else
				{
					msg->type = 0;
					fclose(fp);
					return 0;

				}
				fclose(fp);
			}
		}
	}
	msg->type = 0;
	return 0;

}

void* func(void* arg)
{
	int fd_c = *(int*)arg;
	
	int re = 0;
	while(1)
	{	
		MSG msg = {};
		MSG msg2 = {};
		int flag = 1;
		re = 0;
		//接收请求
		ret = recv(fd_c,&re,sizeof(int),0);//2    1
		if(0 >= ret)
		{
			perror("recv");
			pthread_exit(NULL);
		}
		printf("re = %d\n",re);
		if(re == 1)
		{
			ret = recv(fd_c,&msg,sizeof(MSG),0);//3    2
			if(0 >= ret)
			{
				perror("recv");
				pthread_exit(NULL);
			}
			//读取并生成账户号码
			FILE* fp = fopen("./data/id.txt","r+");
			if(0 > fp)
			{
				perror("fopen");
				return NULL;
			}
			int id = 0;
			fscanf(fp,"%d",&id);
			id++;
			fseek(fp,0,SEEK_SET);
			fprintf(fp,"%d",id);
			fclose(fp);

			msg.acc.id[0] = id;;
			//保存在.bat文件中
			char s[30] = {};
			sprintf(s,"%s%d%s","./data/",id,".bat");
			fp = fopen(s,"w+");
			fwrite(&msg.acc,sizeof(msg.acc),1,fp);
			fclose(fp);
		}
		else
		{
			switch(re)
			{
				case 2://销户
				{
					recv(fd_c,&msg,sizeof(MSG),0);
					if(login(&msg,fd_c) == 0)
					{
						flag = 0;
						send(fd_c,&msg,sizeof(msg),0);
						break;
					}
					send(fd_c,&msg,sizeof(msg),0);
					
					DIR* dp = opendir ("./data");
					if (! dp) 
					{
			   		 perror ("opendir");
			   		 return NULL;
					}
					char s[20] = {};
					struct dirent* de;
					for (de = readdir (dp); de; de = readdir (dp)) 
					{
						if(de->d_name[0]!='.')
						{
							sprintf(s,"%ld%s",msg.acc.id[0],".bat");
							if(0 == strcmp(s,de->d_name))
							{
								sprintf(s,"%s%ld%s","./data/",msg.acc.id[0],".bat");
								unlink(s);
							}
						}
					}
					break;
				}
				case 3://存款
				{
					recv(fd_c,&msg,sizeof(MSG),0);
					if(login(&msg,fd_c) == 0)
					{
						send(fd_c,&msg,sizeof(msg),0);
						flag = 0;
						break;
					}
					send(fd_c,&msg,sizeof(msg),0);
					
					recv(fd_c,&msg,sizeof(MSG),0);
					//读取指定账户文件
					char s[30] = {};
					sprintf(s,"%s%ld%s","./data/",msg.acc.id[0],".bat");
					FILE* fp = fopen(s,"r+");
					if(0 > fp)
					{
						perror("fopen");
						return NULL;
					}
					fread(&msg2.acc,sizeof(msg.acc),1,fp);
					msg.acc.money = msg2.acc.money+msg.acc.money;
					fseek(fp,0,SEEK_SET);
					fwrite(&msg.acc,sizeof(msg.acc),1,fp);
					fclose(fp);
					break;
				}
				case 4://取款
				{
					recv(fd_c,&msg,sizeof(MSG),0);
					if(login(&msg,fd_c) == 0)
					{
						send(fd_c,&msg,sizeof(msg),0);
						flag = 0;
						break;
					}
					send(fd_c,&msg,sizeof(msg),0);
					
					recv(fd_c,&msg,sizeof(MSG),0);
					//读取指定账户文件
					char s[30] = {};
					sprintf(s,"%s%ld%s","./data/",msg.acc.id[0],".bat");
					FILE* fp = fopen(s,"r+");
					if(0 > fp)
					{
						perror("fopen");
						return NULL;
					}
					fread(&msg2.acc,sizeof(msg.acc),1,fp);
					msg.acc.money = msg2.acc.money-msg.acc.money;
					fseek(fp,0,SEEK_SET);
					if(msg.acc.money > 0)
					{
						fwrite(&msg.acc,sizeof(msg.acc),1,fp);
					}
					fclose(fp);
					break;
				}
				case 5://转账
				{
					recv(fd_c,&msg,sizeof(MSG),0);
					if(login(&msg,fd_c) == 0)
					{
						send(fd_c,&msg,sizeof(msg),0);
						flag = 0;
						break;
					}
					send(fd_c,&msg,sizeof(msg),0);
					
					recv(fd_c,&msg,sizeof(MSG),0);
					int flag = 0;
					//读取指定账户文件
					char s[2][30] = {};
			
					DIR* dp = opendir ("./data");
					if (! dp) 
					{
			   		 perror ("opendir");
			   		 return NULL;
					}
					struct dirent* de;
					sprintf(s[1],"%ld%s",msg.acc.id[1],".bat");
					for (de = readdir (dp); de; de = readdir (dp)) 
					{
						if(de->d_name[0]!='.')
						{
							if(0 == strcmp(s[1],de->d_name))
							{
								flag = 1;
							}
						}
					}
					if(flag == 1)
					{
						sprintf(s[0],"%s%ld%s","./data/",msg.acc.id[0],".bat");
						sprintf(s[1],"%s%ld%s","./data/",msg.acc.id[1],".bat");
						FILE* fp = fopen(s[0],"r+");
						if(NULL == fp)
						{
							perror("fopen");
							return NULL;
						}
						FILE* fp2 = fopen(s[1],"r+");
						if(NULL == fp2)
						{
							perror("fopen");
							return NULL;
						}
						int money = msg.acc.money;
						fread(&msg2.acc,sizeof(msg.acc),1,fp);
						msg.acc.money = msg2.acc.money-money;
						fseek(fp,0,SEEK_SET);
			
						if(msg.acc.money > 0)
						{
							fwrite(&msg.acc,sizeof(msg.acc),1,fp);
				
							fread(&msg2.acc,sizeof(msg.acc),1,fp2);
							fseek(fp2,0,SEEK_SET);
							msg2.acc.money = msg2.acc.money + money;
							fwrite(&msg2.acc,sizeof(msg.acc),1,fp2);
						}
						
						fclose(fp);
						fclose(fp2);
					}
					else
					{
						msg.type = 567;
					}
					break;
				}
				case 6://余额查询
				{
					recv(fd_c,&msg,sizeof(MSG),0);
					if(login(&msg,fd_c) == 0)
					{
						send(fd_c,&msg,sizeof(msg),0);
						flag = 0;
						break;
					}
					send(fd_c,&msg,sizeof(msg),0);
					//读取指定账户文件
					char s[30] = {};
					sprintf(s,"%s%ld%s","./data/",msg.acc.id[0],".bat");
					FILE* fp = fopen(s,"r+");
					if(0 > fp)
					{
						perror("fopen");
						return NULL;
					}
					fread(&msg2.acc,sizeof(msg.acc),1,fp);
					msg.acc.money = msg2.acc.money+msg.acc.money;
					fseek(fp,0,SEEK_SET);
					fwrite(&msg.acc,sizeof(msg.acc),1,fp);
					fclose(fp);
					break;
				}
				case 7:
					pthread_exit(NULL);
				default: 
				{
					flag = 0;
					break;
				}
			}
		}
		//响应请求
		if(flag == 1)
		{
			ret = send(fd_c,&msg,sizeof(MSG),0);//4
			if(0 > ret)
			{	
				perror("send");
				pthread_exit(NULL);
			}
		}
	}
	

}

int main()
{
	struct account acc = {};
	struct msg msg = {};

	int i = 1;
	pid_t pid = getpid();
	
	//创建sockfd
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(0 >= sockfd)
	{
		perror("socket");
		return -1;
	}

	//准备连接地址
	struct sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(18888);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");


	//绑定sockfd和通信地址
	ret = bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
	if(0 > ret)
	{
		perror("bind");
		return -1;
	}

	//监听
	ret = listen(sockfd,50);
	if(0 > ret)
	{
		perror("listen");
		return -1;
	}


	

	//接收客户端发来的业务请求，创建相应子线程
	inum = 0;
	int re = 0;
	pthread_t pth_id = 0;
	socklen_t len = sizeof(addr);
	
	while(1)
	{
		int fd = accept(sockfd,(struct sockaddr*)&addr,&len);
		if(0 >= fd)
		{
			perror("accept");
			return -1;
		}
		printf("接收到请求，fd = %d\n",fd);

		ret = pthread_create(&pth_id,0,func,&fd);
		if(0 > ret)
		{
			perror("pthread_create");
			return -1;
		}

		
		
			
		
	}
	
	scanf("%*c");
	
	//关闭子进程

	

	return 0;	
}
