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
int serverCount(){
	int count = 0;
	char *name = "serverip";
	xmlDocPtr doc;
	xmlNodePtr curNode;
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
	while(curNode != NULL){
		if((!xmlStrcmp(curNode->name,(const xmlChar*)"ip"))){
			count++;
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
	return count;
}
void parseXml(char *name,int *count,char *ips){
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
	while(curNode != NULL){
		if((!xmlStrcmp(curNode->name,(const xmlChar*)"ip"))){
			strcat(szKey,(char*)xmlNodeGetContent(curNode));
			strcat(szKey,"#");
			(*count)++;
			//szKey = xmlNodeGetContent(curNode);
			//printf("ip:%s\n",szKey);
			//xmlFree(szKey);
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
	//printf("---long ip is %s\n",szKey);
//	return szKey;
	
}
char *getServerAddress(int *count){
	char *name = "serverip";
	char *ips = malloc(100*sizeof(char)); 
	parseXml(name,count,ips);
	printf("ips:%s\n",ips);
	return ips;
}
