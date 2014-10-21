/*************************************************************************
    > File Name: client.c
    > Author: zhaowei
    > Mail: zhao_wei@bupt.edu.cn 
    > Created Time: 2014年09月24日 星期三 12时44分18秒
 ************************************************************************/

#include"client.h"
#define CLIENT_DEBUG
synLink s;
void intToByte(char **buffer,int len){
	int index = 0;
	for(index;index<4;index++){
		(**buffer) = len>>((index)*8);
	//	printf("bufferTemp:%d\n",**buffer);
		(*buffer)++;
	}	
}
void synMethod(char *key,char *val){
	#ifdef CLIENT_DEBUG
	printf("in synMethod\n");
	#endif
	int server_nums = 0;
	synLink *s = getServerAddress(&server_nums);
	synLink *sTemp = s;
	int status = 0;
	char *k = key;//"hello";
	char *v = val;//"world";
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
	#ifdef CLIENT_DEBUG
		printf("start address : %d\n",(int)s);	
		printf("============%d times go in=============\n",num);
		printf("-------------------\n");
		printNode(s);
		printf("-------------------\n");
	#endif
		client_sock[num] = socket(AF_INET,SOCK_STREAM,0);
		memset(&server_address[num],0,sizeof(server_address[num]));
		server_address[num].sin_family = AF_INET;
		if(!isEmpty(s)){
			syn = getNode(s);
		}
		char *ip = syn->ipaddr;
		char *port = syn->port;
	#ifdef CLIENT_DEBUG
		printf("connect server addr ip  %s port %s\n",ip,port);
	#endif
		server_address[num].sin_port = htons(atoi(port));
		server_address[num].sin_addr.s_addr = inet_addr(ip);
		if(connect(client_sock[num],(struct sockaddr*)&server_address[num],sizeof(server_address[num])) < 0){
			perror("connect fail\n");
		#ifdef CLIENT_DEBUG
			printf("c f未能成功传输到%s\n",ip);
		#endif
			jumpANode(&s);
			continue;
			//exit(1);
		}
		send(client_sock[num], buffer,bytes,0);	
	#ifdef CLIENT_DEBUG
		printf("status: %d\n",status);
	#endif
		//set a timer when send start
		int reclen = recv(client_sock[num],&status,sizeof(int),0);
	#ifdef CLIENT_DEBUG
		printf("status: %d\n",status);
	#endif
		if(status == 200){
			delNode(&s);
		#ifdef CLIENT_DEBUG
			printf("after del\n");
			printNode(s);
			printf("recvd over\n");
		#endif
			status = 0;
		}else{
			jumpANode(&s);
		#ifdef CLIENT_DEBUG
			printf("r f未能成功传输到%s\n",ip);
		#endif
		}
	}
	for(num = 0;num<server_nums;num++){
		close(client_sock[num]);
	}
	printf("exit tranfer\n");
	printf("未同步节点信息\n");
	printNode(sTemp);
//	return ((void*)0);
}
void synByThreads(){
	char *key ="here is a string called key";
	char *val = "this is the value";
	synMethod(key,val);
	//int server_nums = 1;
//	int n;
	//char *ips = getServerAddress(&server_nums);
	//pthread_t send_thread;
	//char *serverAddr;
	//serverAddr = strtok(ips,"#");
	//int i_serv = 0;
	//int *tret;
	//printf("serverAddr : %s\n",serverAddr);
	//int err;
	//err = pthread_create(&send_thread,NULL,synMethod,NULL);
	//if(err != 0) 
	//	printf("create p_server error\n");
	//err = pthread_join(send_thread,&tret);
		//if(err != 0) printf("pthread join err\n");
	//serverAddr = strtok(NULL,"#");
//	free(ips);
}
