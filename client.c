/*************************************************************************
    > File Name: client.c
    > Author: zhaowei
    > Mail: zhao_wei@bupt.edu.cn 
    > Created Time: 2014年09月24日 星期三 12时44分18秒
 ************************************************************************/

#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>

typedef struct syninfo{
	char *key;
	char *value;
}syninfo;
void synMethod(){
	syninfo syn;
	char *key = "hello";
	char *value = "world";
	int keylen = strlen(key);
	int vallen = strlen(value);
	syn.key = malloc(keylen);
	syn.value = malloc(vallen);
	strcpy(syn.key,key);
	strcpy(syn.value,value);

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
	
	send(client_sock, &keylen, sizeof(keylen),0);
	send(client_sock, syn.key, keylen,0);
	send(client_sock, &vallen, sizeof(vallen),0);
	send(client_sock, syn.value, vallen,0);
	close(client_sock);
}

int main(){
	synMethod();
	return 0;
}
