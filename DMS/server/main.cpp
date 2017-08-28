#include "server.h"
#include "userdata.h"
#include "except.h"
UserData dataPool;

int main()
{
	Server server("127.0.0.1",10087);
	try{
		server.initSocket();
	}catch(DmsServerException& e)
	{
		cout << e.what() << endl;
	}
	server.startService();
}

