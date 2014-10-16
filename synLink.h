/*************************************************************************
    > File Name: synLink.h
    > Author: zhaowei
    > Mail: zhao_wei@bupt.edu.cn 
    > Created Time: 2014年10月16日 星期四 16时48分37秒
 ************************************************************************/

#ifndef SYNLINK_H
#define SYNLINK_H
typedef struct synLink{
	char *ipaddr;
	char *port;
	struct synLink *next;
}synLink;
typedef struct writeStatus{
	char *key;
	synLink *synln;
}writeStatus;
void setNull(synLink **s);
synLink *createSynlink();
synLink *insertNode(synLink *p, char *addr);
void deleteNode(char *ip);
void printNode(synLink *head);
int isEmpty(synLink *h);
synLink *getNode(synLink *h);
void delNode(synLink **h);
#endif
