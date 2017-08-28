#ifndef _DATA_RECEIVE_THREAD_H__
#define _DATA_RECEIVE_THREAD_H__

#include <pthread.h>
#include "userdata.h"
extern UserData dataPool;

class DataReceiveThread
{
private:
	pthread_t id;
	int fd;
public:
	DataReceiveThread(int fd);
	~DataReceiveThread();
	void start();
	void run();
	static void* receiveData(void* par);
};




#endif // _DATA_RECEIVE_THREAD_H__

