#ifndef _USER_DATA_H__
#define _USER_DATA_H__

#include "data.h"
#include <pthread.h>
#include <list>
class UserData
{
private:
	list<MatchedLogRec> data;
	pthread_mutex_t mutex;
	pthread_cond_t con_p;
	pthread_cond_t con_c;
public:
	UserData();
	~UserData();
	void push_data(MatchedLogRec rec);
	MatchedLogRec pop_data();

};




#endif // _USER_DATA_H__

