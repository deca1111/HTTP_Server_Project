#include "annexe.h"
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
