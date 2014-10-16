/*************************************************************************
    > File Name: server.c
    > Author: zhaowei
    > Mail: zhao_wei@bupt.edu.cn 
    > Created Time: 2014年09月24日 星期三 13时03分05秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<sys/socket.h>
#include "server.h"
#include "eventListen.h"

#define QUEUE 10
#define PORT 9000
typedef struct syninfo{
	char *key;
	char *value;
}syninfo;
void recvData(int conn){
		int status = 200;
		int recvlen = 0;
		int len = recv(conn, &recvlen, sizeof(int), 0);
		//len = recv(conn,&recvlen,sizeof(int),0);
		char *recvBuffer = malloc(recvlen);
		len = recv(conn,recvBuffer,recvlen,0);
		int kLen,vLen;
		char *k,*v;
		memcpy(&kLen,recvBuffer,sizeof(int));
		recvBuffer += sizeof(int);
		
		k = malloc(kLen);
		memcpy(k,recvBuffer,kLen);
		recvBuffer += kLen;
		
		memcpy(&vLen,recvBuffer,sizeof(int));
		recvBuffer += sizeof(int);

		v = malloc(vLen);
		memcpy(v,recvBuffer,vLen);
	//	sleep(1);
		printf("k:%s--v:%s\n",k,v);
		send(conn,&status,sizeof(int),0);
}
void synEvent(){
	syninfo syn;
	int server_sock = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind( server_sock,(struct sockaddr*)&server_address,sizeof(server_address) ) == -1){
		perror("bind fail\n");
		exit(1);
	}
	if(listen(server_sock,QUEUE) == -1){
		perror("listen fail\n");
		exit(1);
	}
	eventListen(server_sock);
	/*
	struct sockaddr_in client_address;
	socklen_t length = sizeof(client_address);

	while(1){
		int conn = accept(server_sock,(struct sockaddr*)&client_address,&length);
		if(conn < 0){
			perror("accept fail\n");
			exit(1);
		}
		recvDate(conn);*/
	//recv over , write into cache,next step 
}
int main(){
	synEvent();	
	return 0;
}
