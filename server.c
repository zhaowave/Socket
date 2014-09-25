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

#define QUEUE 10
typedef struct syninfo{
	char *key;
	char *value;
}syninfo;
char *getServerIp(){
	FILE* conf = fopen("./ipconf.conf","r");
	char *ip = malloc(15);
	memset(ip,0,15);
	if(conf == NULL) {
		printf("file open error\n");
		exit(0);
	}
	char line[100];
	while(fgets(line,100,conf)){
		if(strlen(line) < 9) continue;
		int idx;
		for(idx = 1;line[idx] != '=';idx++);
		idx++;
		while(line[idx] == ' ') idx++;
		int k = 0;
		for(;idx<strlen(line)&&line[idx]!='\n';idx++) 
			ip[k++] = line[idx];
		if(strlen(ip) != 0) break;
	}
	return ip;

}

void synMethod(char *k,char *v){
	syninfo syn;
	char *key = k;
	char *value = v;
	int keylen = strlen(key);
	int vallen = strlen(value);
	syn.key = malloc(keylen);
	syn.value = malloc(vallen);
	strcpy(syn.key,key);
	strcpy(syn.value,value);

	int server_sock = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(5555);
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind( server_sock,(struct sockaddr*)&server_address,sizeof(server_address) ) == -1){
		perror("bind fail\n");
		exit(1);
	}
	if(listen(server_sock,QUEUE) == -1){
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
	
	send(conn, &keylen, sizeof(keylen),0);
	send(conn, syn.key, keylen,0);
	send(conn, &vallen, sizeof(vallen),0);
	send(conn, syn.value, vallen,0);
	//send over 
}

int main(){
	//if(call change cache method)
	
	char *key = "hello";
	char *value = "world";
	//synMethod(key ,value);
	char*ip = getServerIp();
	printf("%s\n",ip);
	return 0;
}
