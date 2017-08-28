#include "server.h"
#include "data.h"
#include <arpa/inet.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include "except.h"

Server::Server(const char* ip,unsigned short port)
{
	strcpy(labIp,ip);
	this->port = port;
}
Server::~Server(){}

void Server::initSocket()
{
	fd = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(labIp);
	int ret = bind(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(-1 == ret)
	{	
		throw DmsBindException("绑定异常！");
	}
	if(listen(fd,10)==-1)
		throw DmsListenException();

	while(1)
	{
		struct sockaddr_in c;
		socklen_t len = sizeof(addr);
		int connfd = accept(fd,(struct sockaddr*)&c,&len);
		DataReceiveThread* productor = new DataReceiveThread(connfd);
		try{
			productor->start();
		}catch(DmsServerException& e)
		{
			cout << e.what() << endl;
		}
		startService();
	}
}

void Server::startService()
{
	DataSaveThread* customer = new DataSaveThread();
	try{
		customer->start();
	}catch(DmsServerException& e)
	{
		cout << e.what() << endl;
	}
}

