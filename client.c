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
	syninfo syn;
	int client_sock = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server_address;
	memset(&server_address,0,sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(5555);
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	if(connect(client_sock,(struct sockaddr*)&server_address,sizeof(server_address)) < 0){
		perror("connect fail\n");
		exit(1);
	}
	
	int keylen;
	int len = recv(client_sock, &keylen, sizeof(keylen), 0);
	syn.key = malloc(keylen);
	len = recv(client_sock,syn.key,keylen,0);
	printf("syn.key:%s\n",syn.key);
	int vallen;
	len = recv(client_sock, &vallen, sizeof(vallen), 0);
	syn.value = malloc(vallen);
	len = recv(client_sock,syn.value,vallen,0);
	printf("syn.value:%s\n",syn.value);
	//recv over , write into cache,next step 
	close(client_sock);
}

int main(){
	synEvent();	
	return 0;
}
