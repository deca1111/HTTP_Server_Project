#ifndef __FONCTION_H__
#define __FONCTION_H__

#include "request.h"
#include "annexe.h"
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
int version(Lnode *node);
int calculer_Header(char * buffer, char *header_content, int type);
int methode(Lnode *node);

void sendLengthHeader(int taille_fich, unsigned int clientID);
void sendFichier(int fichier, int taille_fich, unsigned int clientID);
void sendTypeHeader(char* type, unsigned int clientID);
void sendDateHeader(unsigned int clientID);

void sendError400(unsigned int clientID);
void sendError404(unsigned int clientID);
void sendError505(unsigned int clientID);
void sendError501(unsigned int clientID);

#endif
