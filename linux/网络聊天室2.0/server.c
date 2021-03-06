#include "struct.h"


int flag = 0;
int user_len = 0;
MSG msg;
user user_info;


int create_sockfd(void)
{
	int fd = socket(AF_INET,SOCK_DGRAM,0);
	if(0 >= fd)
	{
		perror("sockfd");
		return -1;
	}

	return fd;
}

void server(void* arg)
{
	printf("-------------\n");
	int i = 0;
	int j = 0;
	int fd = create_sockfd();
	int user_num = user_len - 1;
	char* user_name = (char*)arg;
	char buf[255] = {};
	sprintf(buf,"尊敬的%s,%u正在为您服务...",user_info.user_name[user_num],pthread_self());
	sendto(fd,buf,strlen(buf)+1,0,(SP)&user_info.user_addr[user_num],sizeof(SA));
	char str[255] = {};
	sprintf(str,"%s\n","-----------");
	sendto(fd,str,strlen(str)+1,0,(SP)&user_info.user_addr[user_num],sizeof(SA));
	while(1)
	{
		flag = 0;
		char name[20] = {};
		char str[255] = {};
		recvfrom(fd,buf,sizeof(buf),0,NULL,NULL);
		sscanf(buf,"%s %s",name,str);
		//@user_name 私信
		for(i=0; name[i]!='\0'; i++)
		{
			if(name[i] == '@')
			{
				for(j=0; j<user_len; j++)
				{

					if(!strcmp(user_info.user_name[j],name+i+1))
					{

						sendto(fd,&buf,strlen(buf)+1,0,(SP)&user_info.user_addr[j],sizeof(SA));
						sendto(fd,&buf,strlen(buf)+1,0,(SP)&user_info.user_addr[user_num],sizeof(SA));
						flag = 1;
						break;
					}
				}
			}
			if(flag==1)
			break;
		}
		
		//#user_name 私聊
		for(i=0; name[i]!='\0'; i++)
		{
			if(name[i] == '#')
			{
				for(j=0; j<user_len; j++)
				{

					if(!strcmp(user_info.user_name[j],name+i+1))
					{
						sprintf(str,"c#c %s %s",user_info.user_name[user_num],buf);
						sendto(fd,&str,strlen(str)+1,0,(SP)&user_info.user_addr[user_num],sizeof(SA));
						sprintf(str,"s#s %s %s",user_info.user_name[user_num],buf);
						sendto(fd,&str,strlen(str)+1,0,(SP)&user_info.user_addr[j],sizeof(SA));
						//把私聊双方的地址发给对方
						sendto(fd,&user_info.user_addr[j],sizeof(SA),0,(SP)&user_info.user_addr[user_num],sizeof(SA));
						sendto(fd,&user_info.user_addr[user_num],sizeof(SA),0,(SP)&user_info.user_addr[j],sizeof(SA));
						flag = 1;
						break;
					}
				}
			}
			if(flag==1)
			break;
		}
		

		//群聊
		if(flag==0)
		{
			for(i=0; i<user_len; i++)
			{
				sendto(fd,&buf,strlen(buf),0,(SP)&user_info.user_addr[i],sizeof(SA));
			}
		}	
		
	}	
}

int main()
{
	int fd = create_sockfd();
	SA send_addr;
	SA send_addr2;
	SA recv_addr;
	recv_addr.sin_family = AF_INET;
	recv_addr.sin_port = htons(12346);
	recv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int ret = bind(fd,(SP)&recv_addr,sizeof(recv_addr));
	if(0 > ret)
	{
		perror("bind");
		return -1;
	}
	pthread_t pth_id = 0;
	char user_name[20] = {};
	socklen_t len = sizeof(send_addr);
	
	user_len = 0;

	while(1)
	{
		recvfrom(fd,user_name,sizeof(send_addr),0,(SP)&user_info.user_addr[user_len],&len);
		sprintf(user_info.user_name[user_len],"%s",user_name);
		printf("recv:%s\n",user_info.user_name[user_len]);
		user_len++;	
		
		sleep(1);
		printf("user_len:%d\n",user_len);
		//开辟子线程
		ret = pthread_create(&pth_id,NULL,server,NULL);
		if(0 > ret)
		{
			perror("pthread_create");
			return -1;
		}
	}
	
}
