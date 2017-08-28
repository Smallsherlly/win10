#include "datareceivethread.h"
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "except.h"
using namespace std;
extern UserData dataPool;
DataReceiveThread::DataReceiveThread(int fd):fd(fd){}

DataReceiveThread::~DataReceiveThread()
{
	pthread_join(id,NULL);
}

void DataReceiveThread::run()
{
	MatchedLogRec log;
	// accept返回的一个值
	while(recv(fd,(char*)&log,sizeof(log),0)>0)
	{
		log.pid = ntohl(log.pid);
		log.logintime = ntohl(log.logintime);
		log.logouttime = ntohl(log.logouttime);
		log.durations = ntohl(log.durations);
		dataPool.push_data(log);
	}
}

void DataReceiveThread::start()
{
	int ret = pthread_create(&id,NULL,receiveData,this);
	if(0 != ret)
	{
		throw CreateThreadException();
	}
}

void* DataReceiveThread::receiveData(void* par)
{
	DataReceiveThread* datareceive = reinterpret_cast<DataReceiveThread*>(par);
	datareceive->run();
}



