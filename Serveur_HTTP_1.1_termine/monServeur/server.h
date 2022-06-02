#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>

// for librequest
#include "request.h"

// for parser

// this will declare internal type used by the parser
#include "httpparser.h"
#include "api.h"
#include "fonction.h"
#include "annexe.h"
#include "socket.h"

#endif
