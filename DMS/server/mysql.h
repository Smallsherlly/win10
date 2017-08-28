#include <mysql/mysql.h>
#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

class SQL
{
public:
	SQL();
	~SQL();
	/*
	功能：
		初始化数据库
		连接数据训
		设置字符集
	返回值：
		int: 0表示成功，-1表示失败
	参数：
	   database:数据库名称
	   host:数据库服务ip
	   port:数据库端口
	   user:数据库用户名
	   passwd:数据库密码
	   charset:字符集
	*/
	int Connect(const char *database="StudentInfo",const char *host="localhost",const char *port=NULL,const char *user="root",const char *passwd="131452",const char  *charset="utf8");
	/*
	功能：
		查询数据
	参数：
		sql:查询的SQL语句
	*/
	int Select(const char *sql,list<vector<string> >& listRes);
	/*
		Insert,Update,Delete三个函数：
		返回值：
			-1表示失败，其余表示影响表数据的行数
	*/
	int Insert(const char* sql);
	int Update(const char* sql);
	int Delete(const char* sql);
	int Create(const char* sql);
	void Close();
	/*
		功能：
			获得错误信息
	*/
	const char *getErr();
	bool isAutoCommit();
	bool onAutoCommit();
	bool offAutoCommit();
private:
	MYSQL *conn;
	bool  autoCommit;
	char  msg[256];
};

