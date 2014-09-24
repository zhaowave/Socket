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

typedef struct syninfo{
	char *key;
	char *value;
}syninfo;
void synEvent(){
	int server_sock = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(5555);
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind( server_sock,(struct sockaddr*)&server_address,sizeof(server_address) ) == -1){
		perror("bind fail\n");
		exit(1);
	}
	if(listen(server_sock,10) == -1){
		perror("listen fail\n");
		exit(1);
	}
	struct sockaddr_in client_address;
	socklen_t length = sizeof(client_address);
	int conn = accept(server_sock,(struct sockaddr*)&client_address,&length);
	if(conn < 0){
		perror("accept fail\n");
		exit(1);
	}
	int keylen;
	int len = recv(conn, &keylen, sizeof(keylen), 0);
	printf("%d\n",keylen);
	char *key = malloc(keylen);
	len = recv(conn,key,keylen,0);
	printf("%s\n",key);
	int vallen;
	len = recv(conn, &vallen, sizeof(vallen), 0);
	printf("%d\n",vallen);
	char *value = malloc(vallen);
	len = recv(conn,value,vallen,0);
	printf("%s\n",value);
}

int main(){
	synEvent();	
	return 0;
}
