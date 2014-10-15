/*************************************************************************
    > File Name: client.c
    > Author: zhaowei
    > Mail: zhao_wei@bupt.edu.cn 
    > Created Time: 2014年09月24日 星期三 12时44分18秒
 ************************************************************************/

#include"client.h"
typedef struct syninfo{
	char *key;
	char *value;
}syninfo;
void intToByte(char **buffer,int len){
	int index = 0;
	for(index;index<4;index++){
		(**buffer) = len>>((index)*8);
	//	printf("bufferTemp:%d\n",**buffer);
		(*buffer)++;
	}	
}
void *synMethod(void *arg){
	printf("in synMethod\n");
	char *serverAddr = (char*)arg;
	char *ip,*port;
	ip = strtok(serverAddr,":");
	port = strtok(NULL,":");
	char *k = "hellodjakfldjaklsfjd;las";
	char *v = "world";
	syninfo *syn;
	int kLen = strlen(k);
	int vLen = strlen(v);
	int len = kLen + vLen + 2*sizeof(int);
	size_t bytes = 3*sizeof(int) + kLen + vLen;
	char *buffer = malloc(sizeof(char)*bytes);
	char *bufferTemp = buffer;
	intToByte(&bufferTemp,len);
	intToByte(&bufferTemp,kLen);
	memcpy(bufferTemp,k,kLen);
	bufferTemp += kLen;
	intToByte(&bufferTemp,vLen);
	memcpy(bufferTemp,v,vLen);

	int client_sock = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server_address;
	memset(&server_address,0,sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(atoi(port));
	server_address.sin_addr.s_addr = inet_addr(ip);
	if(connect(client_sock,(struct sockaddr*)&server_address,sizeof(server_address)) < 0){
		perror("connect fail\n");
		exit(1);
	}
	send(client_sock, buffer,bytes,0);	
	close(client_sock);
	return ((void*)0);
}
void synByThreads(){
	int server_nums = 1;
	int n;
	char *ips = getServerAddress(&server_nums);
	pthread_t *p_serv = malloc(sizeof(pthread_t)*server_nums);
	char *serverAddr;
	serverAddr = strtok(ips,"#");
	int i_serv = 0;
	int *tret;
	while(serverAddr != NULL){
		printf("serverAddr : %s\n",serverAddr);
		int err;
		err = pthread_create(p_serv+i_serv,NULL,synMethod,serverAddr);
		i_serv++;
		if(err != 0) 
			printf("create p_server error\n");
		//err = pthread_join(*(p_serv+i_serv),&tret);
		//if(err != 0) printf("pthread join err\n");
		serverAddr = strtok(NULL,"#");
	}
}
//int main(){
	//if(call change cache method)
//	synByThreads();
//	sleep(1);
//	return 0;
//}
