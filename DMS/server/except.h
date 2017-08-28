#ifndef _EXCEPT_H__
#define _EXCEPT_H__

#include <exception>
#include <cstring>
using namespace std;

class DmsServerException:public exception
{
public:
	DmsServerException(const char* str="服务端异常")
	{
		strcpy(msg,str);
	}
	virtual const char* what()
	{
		return msg;
	}
	~DmsServerException()throw(){}
private:
	char msg[200];
};


class DmsBindException:public DmsServerException
{
public:
	DmsBindException(const char* str="绑定异常")
	:DmsServerException(str){}
	//~DmsReadException();
	
};

class DmsListenException:public DmsServerException
{
public:
	DmsListenException(const char* str="监听异常")
	:DmsServerException(str){}
	//~BackupException();
	
};

class CreateThreadException:public DmsServerException
{
public:
	CreateThreadException(const char* str="创建线程异常")
	:DmsServerException(str){}
	//~ReadFailLoginException();
	
};

class DmsConnectException:public DmsServerException
{
public:
	DmsConnectException(const char* str="连接异常")
	:DmsServerException(str){}
	//~MatchLogRecException();
	
};

#endif // _EXCEPT_H__
