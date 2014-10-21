/*************************************************************************
    > File Name: synLink.c
    > Author: zhaowei
    > Mail: zhao_wei@bupt.edu.cn 
    > Created Time: 2014年10月16日 星期四 17时00分01秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "synLink.h"
#include "readXmlFile.h"
synLink *createSynlink(){
	synLink *s = (struct synLink *)malloc(sizeof(struct synLink));
	synLink *head = s;
	s->port = NULL;
	s->ipaddr = NULL;
	s->next = NULL;
	char addrs[] = "127.0.0.1:9000#10.103.123.22:9000#";
	char *serverAddr;
	serverAddr = strtok(addrs,"#");
//	printf("serverAddr %s\n",serverAddr);
	
	while(serverAddr != NULL){
		printf("in while serverAddr %s\n",serverAddr);
		s = insertNode(s,serverAddr);
		//s->next = temp;
		printf("========%s\n",s->ipaddr);
		serverAddr = strtok(NULL,"#");
	}
	printf("head->next->ip %s \n",head->next->ipaddr);	
	return head;
}
synLink *insertNode(synLink *p,char *addr){
//	printf("in insertNode addr %s\n",addr);
	synLink *r = (struct synLink *)malloc(sizeof(struct synLink));
	p->next = r;
	char *ip,*port;
	ip = strtok(addr,":");
	port = strtok(NULL,":");
	r->ipaddr = ip;r->port = port;
	r->next = NULL;
	return r;
}
void setNull(synLink **s){
	*s = NULL;
}
void printNode(synLink *h){
	if(h ==NULL||h->next == NULL){
		printf("empty link \n");
		return;
	}
	while(h->next){
		printf("in printNode ip:%s  port:%s \n",h->next->ipaddr,h->next->port);
		h = h->next;
	}
}
int isEmpty(synLink *h){
	if(h == NULL||h->next == NULL)
		return 1;
	return 0;
}
synLink *getNode(synLink *h){
	if(isEmpty(h)){
		printf("a empty link can't get a node\n");
		return NULL;
	}
	return h->next;
}
void delNode(synLink **h){
//	printf("in delNode fun\n");
	if(isEmpty(*h)){
		printf("empty link couldn't delNode\n");
		return;
	}
	synLink *del = (*h)->next;
	(*h)->next = del->next;
	free(del);
}
void jumpANode(synLink **h){
	//synLink *temp = (*h)->next;
//	printf("int jump\n");
//	printf("%d\n",*h);
	(*h) = (*h)->next;
//	printf("%d\n",*h);
	
}
/*
int main(){
//	synLink *h = createSynlink();
//	printNode(h);
	int a = 0;
	synLink *s = getServerAddress(&a);
	printNode(s);
	return 0;
}*/

