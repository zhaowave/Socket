#ifndef EVENTLISTEN_H_INCLUDED
#define EVENTLISTEN_H_INCLUDED

int eventListen(int sockfd);
void onRead(int conn, short iEvent, void *arg);

#endif // EVENTLISTEN_H_INCLUDED
