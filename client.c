/*************************************************************************
    > File Name: client.c
    > Author: zhaowei
    > Mail: zhao_wei@bupt.edu.cn 
    > Created Time: 2014年09月24日 星期三 12时44分18秒
 ************************************************************************/

#include"client.h"
synLink s;
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
	int server_nums = 0;
	//char *ips = getServerAddress(&server_nums);
	synLink *s = getServerAddress(&server_nums);
	//server_nums = 1;
	int status = 0;
	//char *ip = "127.0.0.1",*port = "9000";
	char *k = "hello";
	char *v = "world";
	//syninfo *syn;
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
//	printf("address: ip:%s  port: %s\n",ip,port);
	int *client_sock = malloc(sizeof(int)*server_nums);
	struct sockaddr_in *server_address = malloc(sizeof(struct sockaddr_in)*server_nums);
	int num;

	synLink *syn;
	for(num = 0;num<server_nums;num++){
		printf("%d times go in\n",num);
		client_sock[num] = socket(AF_INET,SOCK_STREAM,0);
		memset(&server_address[num],0,sizeof(server_address[num]));
		server_address[num].sin_family = AF_INET;
		if(!isEmpty(s)){
			syn = getNode(s);
		}
		char *ip = syn->ipaddr;
		char *port = syn->port;
		delNode(&s);
		printf("after del\n");
		printNode(s);
		printf("connect server addr ip  %s port %s\n",ip,port);
		server_address[num].sin_port = htons(atoi(port));
		server_address[num].sin_addr.s_addr = inet_addr(ip);
		if(connect(client_sock[num],(struct sockaddr*)&server_address[num],sizeof(server_address[num])) < 0){
			perror("connect fail\n");
			//exit(1);
		}
		send(client_sock[num], buffer,bytes,0);	
		printf("status: %d\n",status);
		//set a timer when send start
		recv(client_sock[num],&status,sizeof(int),0);
		printf("status: %d\n",status);
		if(status == 200){
			printf("recvd over\n");
			status = 0;
		}
	}
	for(num = 0;num<server_nums;num++){
		close(client_sock[num]);
	}
	printf("exit tranfer\n");
	return ((void*)0);
}
void synByThreads(){
	//int server_nums = 1;
	int n;
	//char *ips = getServerAddress(&server_nums);
	pthread_t send_thread;
	//char *serverAddr;
	//serverAddr = strtok(ips,"#");
	//int i_serv = 0;
	int *tret;
	//printf("serverAddr : %s\n",serverAddr);
	int err;
	err = pthread_create(&send_thread,NULL,synMethod,NULL);
	if(err != 0) 
		printf("create p_server error\n");
	err = pthread_join(send_thread,&tret);
		if(err != 0) printf("pthread join err\n");
	//serverAddr = strtok(NULL,"#");
//	free(ips);
}
