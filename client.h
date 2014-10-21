/*************************************************************************
 *
    > File Name: client.h
    > Author: zhaowei
    > Mail: zhao_wei@bupt.edu.cn 
    > Created Time: 2014年10月14日 星期二 19时16分31秒
 ************************************************************************/

#ifndef CLIENT_H
#define CLIENT_H

#include"readXmlFile.h"
#include "synLink.h"
#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>

typedef struct syninfo{
	char *key;
	char *value;
	char *address;
}syninfo;
typedef struct ws{
	int count;
	pthread_mutex_t c_lock;
}ws;
void intToByte(char **buffer,int len);
void synMethod(char *key,char *val);
void synByThread();


#endif
