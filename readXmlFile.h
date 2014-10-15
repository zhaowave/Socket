/*************************************************************************
    > File Name: readXmlFile.h
    > Author: zhaowei
    > Mail: zhao_wei@bupt.edu.cn 
    > Created Time: 2014年10月10日 星期五 13时34分37秒
 ************************************************************************/
#ifndef READXMLFILE_H
#define READXMLFILE_H
int serverCount();
void parseXml(char *name,int *count,char *ips);//
char *getServerAddress(int *count);
#endif

