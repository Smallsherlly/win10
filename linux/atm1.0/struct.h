#ifndef STRUCT_H_
#define STRUCT_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <dirent.h>


struct account
{
	long id[2];
	char name[20];
	char psw[20];
	int money;
	char idnum[18];
};

typedef struct msg
{
	short type;
	struct account acc;
}MSG;



#endif//STRUCT_H_
