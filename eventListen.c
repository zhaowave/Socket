#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <event.h>

#include "eventListen.h"
#include "server.h"
struct event_base* base;


void onRead(int conn, short iEvent, void *arg)
{
	recvData(conn);
}

void onAccept(int fd, short iEvent, void *arg)
{
    int conn;
    struct sockaddr_in sCliAddr;


    socklen_t iSinSize = sizeof(sCliAddr);
    conn = accept(fd, (struct sockaddr*)&sCliAddr, &iSinSize);

    struct event *pEvRead = (struct event*)malloc(sizeof(struct event));
    event_set(pEvRead, conn, EV_READ, onRead, pEvRead);
    event_base_set(base, pEvRead);
    event_add(pEvRead, NULL);
}


int eventListen(int sockfd){
    base = event_base_new();
    struct event evListen;
    event_set(&evListen, sockfd, EV_READ|EV_PERSIST, onAccept, NULL);
    event_base_set(base, &evListen);
    event_add(&evListen, NULL);
    event_base_dispatch(base);
    return 0;
}
