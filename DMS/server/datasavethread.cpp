#include "datasavethread.h"
#include "except.h"
extern UserData dataPool;

DataSaveThread::DataSaveThread(const char* database)
{
	if(0 != sql.Connect(database))
	{
//		throw DmsConnectException();
		cout << "连接数据库异常" << endl;
	}
}

DataSaveThread::~DataSaveThread()
{
	pthread_join(id,NULL);
}

void DataSaveThread::run()
{
	cout << "datasavethread\n";
	while(1)
	{
	MatchedLogRec log = dataPool.pop_data();
	char sqlstr[1024] = "";
	sprintf(sqlstr,"insert into user_login_info_detail(userid,ip,logintime,logouttime,durations)values('%s','%s',%d,%d,%d)",log.logname,log.logip,log.logintime,log.logouttime,log.durations);
	sql.Insert(sqlstr);
	}
}

void DataSaveThread::start()
{
	int ret = pthread_create(&id,NULL,saveData,this);
	if(ret != 0)
	{
		throw CreateThreadException();
	}
}

void* DataSaveThread::saveData(void* par)
{
	DataSaveThread* dataSave = (DataSaveThread*)par;
	dataSave->run();
}


