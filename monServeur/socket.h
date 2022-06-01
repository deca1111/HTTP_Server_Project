#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/mman.h>

#include "fastcgi.h"
#include "fonction.h"

#define sendStdin(fd,id,stdin,len) sendWebData(fd,FCGI_STDIN,id,stdin,len)
#define sendData(fd,id,data,len) sendWebData(fd,FCGI_DATA,id,data,len)
#define sendParams(fd,id,params,len) sendWebData(fd,FCGI_PARAMS,id,params,len)

void writeSocket(int fd,FCGI_Header *h,unsigned int len);
void writeLen(int len, char **p);
int addNameValuePair(FCGI_Header *h,char *name,char *value);
void sendGetValue(int fd);
void sendBeginRequest(int fd,unsigned short requestId,unsigned short role,unsigned char flags);
void sendAbortRequest(int fd,unsigned short requestId);
void sendWebData(int fd,unsigned char type,unsigned short requestId,char *data,unsigned int len);
int createSocket(int port);
void sendEndRequest(int fd,unsigned short requestId,unsigned int appStatus,unsigned char protocolStatus);
void sendUnknownType(int fd,unsigned short requestId,unsigned char type);
void completeParamsHeader(FCGI_Header * header, char * tab[500][2]);
void afficherHeader(FCGI_Header * header);
int readResponse(int fd, char* response[2]);
void completeParamsConst(FCGI_Header * header);
int fillHeaderPost(FCGI_Header *header, _Token * root);

#endif
