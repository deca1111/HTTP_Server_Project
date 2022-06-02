#ifndef __FONCTION_H__
#define __FONCTION_H__

#include "request.h"
#include "annexe.h"
#include "api.h"
#include "httpparser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>
#include<sys/stat.h>



int strcmpLen(char* c1, char* c2, int l);
void strcatLen(char* c1, char* c2, int l1, int l2);
int checkIfFileExists(const char* filename);
char *get_filename_ext(char *filename);
char* mimeType(char* nom_fichier);
int version(_Token * root);
int methode(_Token * root);
int connexion(_Token * root);
char* decodePercent(char* src, int len, char* buffer);
void parsePhpContent(char * content, char * new[2]);

void sendLengthHeader(int taille_fich, unsigned int clientID);
void sendFichier(int fichier, int taille_fich, unsigned int clientID);
void sendTypeHeader(char* type, unsigned int clientID);
void sendDateHeader(unsigned int clientID);
void sendAllowHeader(char* method_allowed, unsigned int clientID);
void sendPhpResponse(char* content, unsigned int clientID);
void sendPhpError(char * error, char* content, unsigned int clientID);


void sendError400(unsigned int clientID);
void sendError404(unsigned int clientID);
void sendError505(unsigned int clientID);
void sendError501(unsigned int clientID);
void sendError405(unsigned int clientID);

#endif
