#include "userdata.h"
#include <pthread.h>
#define MAX_USER 200
/*
	list<MatchedLogRec> data;
	pthread_mutex_t mutex;
	pthread_cond_t con_p;
	pthread_cond_t con_c;
*/
UserData::UserData()
{
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&con_p,NULL);
	pthread_cond_init(&con_c,NULL);
}

UserData::~UserData()
{
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&con_p);
	pthread_cond_destroy(&con_c);
}

void UserData::push_data(MatchedLogRec rec)
{
	pthread_mutex_lock(&mutex);
	while(data.size()>=200)
	{
		pthread_cond_wait(&con_p,&mutex);
	}
	data.push_back(rec);
	pthread_cond_broadcast(&con_c);
	pthread_mutex_unlock(&mutex);
}

MatchedLogRec UserData::pop_data()
{
	pthread_mutex_lock(&mutex);
	while(data.empty())
	{
		pthread_cond_wait(&con_c,&mutex);
	}
	MatchedLogRec logrec = data.front();
	data.pop_front();
	pthread_cond_broadcast(&con_p);
	pthread_mutex_unlock(&mutex);
	return logrec;
}

