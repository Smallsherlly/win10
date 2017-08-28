#ifndef _DATA_SAVE_THREAD_H__
#define _DATA_SAVE_THREAD_H__

#include "mysql.h"
#include "userdata.h"
#include "data.h"
#include <pthread.h>
#include <iostream>
using namespace std;
extern UserData dataPool;

class DataSaveThread
{
private:
	pthread_t id;
	SQL sql;
public:
	DataSaveThread(const char* database="DMS");
	~DataSaveThread();
	void run();
	void start();
	static void* saveData(void* par);
};


#endif // _DATA_SAVE_THREAD_H__
