/*************************************************************************
    > File Name: readXmlFile.c
    > Author: zhaowei
    > Mail: zhao_wei@bupt.edu.cn 
    > Created Time: 2014年10月10日 星期五 09时49分25秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<libxml/parser.h>
#include"readXmlFile.h"
#include "synLink.h"
void parseXml(char *name,int *count,char *ips ,synLink **head){
	xmlDocPtr doc;
	xmlNodePtr curNode;
	char *szKey = ips;// malloc(sizeof(char)*100);
	char *szDocName = "Mem-conf.xml";
	doc = xmlReadFile(szDocName,"GB2312",XML_PARSE_RECOVER);
	curNode = xmlDocGetRootElement(doc);

	curNode = curNode->xmlChildrenNode;
	xmlNodePtr propNodePtr = curNode;
	while(curNode != NULL){
		if((!xmlStrcmp(curNode->name,(const xmlChar*)name))){
			curNode = curNode->xmlChildrenNode;
			break;
		}
		curNode = curNode->next;
	}
	synLink *h = *head;
	while(curNode != NULL){
		if((!xmlStrcmp(curNode->name,(const xmlChar*)"address"))){
			strcat(szKey,(char*)xmlNodeGetContent(curNode));
			strcat(szKey,"#");
			(*count)++;
			h = insertNode(h,(char*)xmlNodeGetContent(curNode));
			//szKey = xmlNodeGetContent(curNode);
			//printf("ip:%s\n",szKey);
			//xmlFree(szKey);
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
}
synLink *getServerAddress(int *count){
	char *name = "server";
	synLink *head = (synLink*)malloc(sizeof(synLink)); 
	char *ips = malloc(100*sizeof(char)); 
	parseXml(name,count,ips,&head);

	printNode(head);

//	printf("ips:%s\n",ips);
	return head;
	//return ips;
}
