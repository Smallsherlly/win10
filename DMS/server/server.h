#ifndef _SERVER_H__
#define _SERVER_H__

#include "datareceivethread.h"
#include "datasavethread.h"

class Server
{
private:
	int fd;
	char labIp[20];
	unsigned short port;
	//DataReceiveThread productor;
	//DataSaveThread customer;
public:
	Server(const char* ip,unsigned short port);
	~Server();
	void initSocket();
	void startService();
};



#endif // _SERVER_H__

