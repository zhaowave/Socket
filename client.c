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
#include<pthread.h>
typedef struct syninfo{
	char *key;
	char *value;
}syninfo;
void getServerIp(){
	FILE* conf = fopen("./ipconf.conf","r");
	if(conf == NULL) {
		printf("file open error\n");
		exit(0);
	}
	char line[100];
	while(fgets(line,100,conf)){
		if(strlen(line) < 9) continue;
		if(line[0] == '#') continue;
		int idx;
		for(idx = 1;line[idx] != '=';idx++);
		idx++;
		while(line[idx] == ' ') idx++;
		for(idx;idx<strlen(line)&&line[idx]!='\n';idx++) putchar(line[idx]);
	}

}
void *synMethod(void *arg){
	char *ip = (char*)arg;
	printf("%s\n",ip);
	char *k = "hello";
	char *v = "world";
	syninfo syn;
	char *key = k;
	char *value = v;
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
	server_address.sin_addr.s_addr = inet_addr(ip);
	if(connect(client_sock,(struct sockaddr*)&server_address,sizeof(server_address)) < 0){
		perror("connect fail\n");
		exit(1);
	}
	
	send(client_sock, &keylen, sizeof(keylen),0);
	send(client_sock, syn.key, keylen,0);
	send(client_sock, &vallen, sizeof(vallen),0);
	send(client_sock, syn.value, vallen,0);
	close(client_sock);
	return ((void*)0);
}
void synByThreads(){
	int server_nums = 1;
	int n;
	char *ip[4];
	for(n = 0;n<4;n++){
		ip[n] = malloc(sizeof(char)*16);
		strcpy(ip[n],"127.0.0.1");
	}
	pthread_t *p_serv = malloc(sizeof(pthread_t)*server_nums);
	int i = 0,err;
	for(;i<server_nums;i++){
		err = pthread_create(p_serv+i,NULL,synMethod,ip[i]);
		if(err != 0) printf("create p_server%d error\n",i);
	}
}
int main(){
	//if(call change cache method)
	
	char *key = "hello";
	char *value = "world";
//	synMethod(key ,value);
	getServerIp();
	synByThreads();
	sleep(1);
	return 0;
}
