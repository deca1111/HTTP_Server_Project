#include "socket.h"
// =========================================================================================================== //
void writeSocket(int fd,FCGI_Header *h,unsigned int len){
	int w;
	// convertis les tailles pour avoir les bits dans le bon sens
	h->contentLength=htons(h->contentLength);
	h->paddingLength=htons(h->paddingLength);

	//ecriture dans la socket fd
	while (len) {
	// try to write
		do {
			w = write(fd, h, len);
		} while (w == -1 && errno == EINTR);
	len-=w;
	}
}
// =========================================================================================================== //
void writeLen(int len, char **p) {
	if (len > 0x7F ) {
		*((*p)++)=(len>>24)&0x7F;
		*((*p)++)=(len>>16)&0xFF;
		*((*p)++)=(len>>8)&0xFF;
		*((*p)++)=(len)&0xFF;
	} else *((*p)++)=(len)&0x7F;
}
// =========================================================================================================== //
int addNameValuePair(FCGI_Header *h,char *name,char *value){
	char *p;
	unsigned int nameLen=0,valueLen=0;

	if (name) nameLen=strlen(name);
	if (value) valueLen=strlen(value);
	printf("longueur Name : %d || longueur Value : %d\n", nameLen, valueLen);

	// si les tailles sont trop grandes on retourne une erreur
	if ((valueLen > FASTCGIMAXNVPAIR) || (valueLen > FASTCGIMAXNVPAIR) ) return -1;
	// si la somme des deux tailles est trop grande on retourne une erreur
	if ((h->contentLength+((nameLen>0x7F)?4:1)+((valueLen>0x7F)?4:1)) > FASTCGILENGTH ) return -1;
	p=(h->contentData)+(h->contentLength);
	writeLen(nameLen,&p);
	writeLen(valueLen,&p);
	strncpy(p,name,nameLen);
	p+=nameLen;
	if (value) strncpy(p,value,valueLen);
	h->contentLength+=nameLen+((nameLen>0x7F)?4:1);
	h->contentLength+=valueLen+((valueLen>0x7F)?4:1);
	return 0;
}
// =========================================================================================================== //
void sendGetValue(int fd){
FCGI_Header h;

	h.version=FCGI_VERSION_1;
	h.type=FCGI_GET_VALUES;
	h.requestId=htons(FCGI_NULL_REQUEST_ID);
	h.contentLength=0;
	h.paddingLength=0;
	addNameValuePair(&h,FCGI_MAX_CONNS,NULL);
	addNameValuePair(&h,FCGI_MAX_REQS,NULL);
	addNameValuePair(&h,FCGI_MPXS_CONNS,NULL);
	writeSocket(fd,&h,FCGI_HEADER_SIZE+(h.contentLength)+(h.paddingLength));
}
// =========================================================================================================== //
void sendBeginRequest(int fd,unsigned short requestId,unsigned short role,unsigned char flags){
FCGI_Header h;
FCGI_BeginRequestBody *begin;

	h.version=FCGI_VERSION_1;
	h.type=FCGI_BEGIN_REQUEST;
	h.requestId=htons(requestId);
	h.contentLength=sizeof(FCGI_BeginRequestBody);
	h.paddingLength=0;
	begin=(FCGI_BeginRequestBody *)&(h.contentData);
	begin->role=htons(role);
	begin->flags=flags;
	writeSocket(fd,&h,FCGI_HEADER_SIZE+(h.contentLength)+(h.paddingLength));
}
// =========================================================================================================== //
void sendAbortRequest(int fd,unsigned short requestId){
	FCGI_Header h;

	h.version=FCGI_VERSION_1;
	h.type=htons(FCGI_ABORT_REQUEST);
	h.requestId=requestId;
	h.contentLength=0;
	h.paddingLength=0;
	writeSocket(fd,&h,FCGI_HEADER_SIZE+(h.contentLength)+(h.paddingLength));
}

//============================================================================================================ //
void sendWebData(int fd,unsigned char type,unsigned short requestId,char *data,unsigned int len){
	FCGI_Header h;
	if (len > FASTCGILENGTH) return ;

	h.version=FCGI_VERSION_1;
	h.type=type;
	h.requestId=htons(requestId);
	h.contentLength=len;
	h.paddingLength=0;
	memcpy(h.contentData,data,len);
	writeSocket(fd,&h,FCGI_HEADER_SIZE+(h.contentLength)+(h.paddingLength));
}
// =========================================================================================================== //
int createSocket(int port){
	int fd;
	struct sockaddr_in serv_addr;

	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket creation failed\n");
		return (-1);
	}

	bzero(&serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	inet_aton("127.0.0.1",&serv_addr.sin_addr);
	serv_addr.sin_port = htons(port);

	if (connect(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("connect failed\n");
		return (-1);
	}

	return fd;
}
// =========================================================================================================== //
void sendEndRequest(int fd,unsigned short requestId,unsigned int appStatus,unsigned char protocolStatus){
FCGI_Header h;
FCGI_EndRequestBody *end;

	h.version=FCGI_VERSION_1;
	h.type=FCGI_END_REQUEST;
	h.requestId=htons(requestId);
	h.contentLength=sizeof(FCGI_EndRequestBody);
	h.paddingLength=0;
	end=(FCGI_EndRequestBody *)&(h.contentData);
	end->appStatus=htons(appStatus);
	end->protocolStatus=protocolStatus;
	writeSocket(fd,&h,FCGI_HEADER_SIZE+(h.contentLength)+(h.paddingLength));
}
// =========================================================================================================== //
void sendUnknownType(int fd,unsigned short requestId,unsigned char type){
FCGI_Header h;
FCGI_UnknownTypeBody *unknown;
	h.version=FCGI_VERSION_1;
	h.type=FCGI_UNKNOWN_TYPE;
	h.requestId=htons(requestId);
	h.contentLength=sizeof(FCGI_UnknownTypeBody);
	h.paddingLength=0;
	unknown=(FCGI_UnknownTypeBody *)&(h.contentData);
	unknown->type=type;
	writeSocket(fd,&h,FCGI_HEADER_SIZE+(h.contentLength)+(h.paddingLength));
}

// =========================================================================================================== //
// Permet d'afficher le header
void afficherHeader(FCGI_Header * header){
	printf("// ----- Affichage header ----- //\n");
	printf("version : _%d_\n", header->version);
	printf("type : _%d_\n", header->type);
	printf("requestId : _%d_\n", ntohs(header->requestId));
	printf("contentLength : _%d_\n", 	ntohs(header->contentLength));
	printf("paddingLength : _%d_\n", header->paddingLength);
	printf("// ---------------------------- //\n");
}
// =========================================================================================================== //
// Permet de lire la réponse du serveur php
int readResponse(int fd, char* response[2]){
	int ret =0, hasError = 0;
	FCGI_Header head_temp;

	char * content = calloc(1, sizeof(char));
	char * error = calloc(1, sizeof(char));

	// lecture du premier header
	if((ret = read(fd, &head_temp, FCGI_HEADER_SIZE)) == -1){
		perror("erreur de lecture du header\n");
		return EXIT_FAILURE;
	}
	int taille_lu;
	int size_content = 0;
	int size_error = 0;
	int taille_a_lire;

	// tant qu'on a pas le header FCGI_END_REQUEST, on continue
	while(head_temp.type != FCGI_END_REQUEST){
		// dans le cas d'un FCGI_STDERR
		if(head_temp.type == FCGI_STDERR){
			hasError = ERROR_PHP;

			// On realloue de la memoire pour modifier la taille de notre erreur avec le nouveau contentLength
			if((error = realloc(error, sizeof(char) * (ntohs(head_temp.contentLength) + size_error + 2))) == NULL ){
				perror("erreur allocation memoire\n");
				return EXIT_FAILURE;
			}
			// On initialise ce qui vient d'etre alloue avec des 0
			bzero(error+size_error,(ntohs(head_temp.contentLength)+2));


			taille_a_lire = ntohs(head_temp.contentLength);
			taille_lu = 0;
			// On lit toute l'erreur
			while(taille_lu < taille_a_lire){
				ret = read(fd, error + size_error, taille_a_lire - taille_lu);
				if(ret == -1){
					perror("erreur lecture\n");
					return EXIT_FAILURE;
				}
				taille_lu += ret;
				size_error += ret;
			}
			// on ajoute une \n a la fin de notre erreur
			strcatLen(error,"\n",size_error++,1);
		}else if(head_temp.type == FCGI_STDOUT){
			// si on a un header FCGI_STDOUT

				// On realloue de la memoire pour modifier la taille de notre contenu avec le nouveau contentLength
			if((content = realloc(content, sizeof(char) * ntohs(head_temp.contentLength) + size_content+1)) == NULL ){
				perror("erreur allocation memoire\n");
				return EXIT_FAILURE;
			}
			bzero(content+size_content,(ntohs(head_temp.contentLength)+1));

			// on lit tout le stdout
			taille_a_lire = ntohs(head_temp.contentLength);
			taille_lu = 0;
			while(taille_lu < taille_a_lire){
				ret = read(fd, content + size_content, taille_a_lire - taille_lu);
				if(ret == -1){
					perror("erreur lecture\n");
					return EXIT_FAILURE;
				}
				taille_lu += ret;
				size_content += ret;
			}

		}


		taille_a_lire = head_temp.paddingLength;
		taille_lu = 0;
		char * buff = malloc(taille_a_lire * sizeof(char));
		// On lit le padding et on le jette dans un buffer
		while(taille_lu < taille_a_lire){
			ret = read(fd, buff, taille_a_lire - taille_lu);
			if(ret == -1){
				perror("erreur lecture\n");
				free(buff);
				return EXIT_FAILURE;
			}
			taille_lu += ret;
		}
		free(buff);

		// lecture et affectation du FCGI_Header suivant
		if((ret = read(fd, &head_temp, FCGI_HEADER_SIZE)) == -1){
			perror("erreur de lecture du header\n");
			return EXIT_FAILURE;
		}
	}

	response[0] = error;
	response[1] = content;

	return(hasError);
}

// =========================================================================================================== //
// Ajouter des parametres en dur dans un header
void completeParamsConst(FCGI_Header * header){
	addNameValuePair(header, "GATEWAY_INTERFACE", "CGI/1.1");
	addNameValuePair(header, "SERVER_NAME", "127.0.0.1");
	addNameValuePair(header, "SERVER_ADDR", "127.0.0.1");
	addNameValuePair(header, "SERVER_PORT", "8080");
	addNameValuePair(header, "SERVER_PROTOCOL", "HTTP/1.1");
	addNameValuePair(header, "REQUEST_SCHEME", "http");
}
// =========================================================================================================== //
// Remplie le content du header params avec les parametres Content_Length, Content_Type et referer
int fillHeaderPost(FCGI_Header *header, _Token * root){
	_Token *token_CL = NULL, *token_CT = NULL, *token_Ref = NULL;
	Lnode *node_CL, *node_CT, *node_Ref;

	token_CL = searchTree(root,"Content_Length");
	token_CT = searchTree(root,"Content_Type");
	token_Ref = searchTree(root,"Referer");

	if((token_CL==NULL)||(token_CT==NULL)||(token_Ref==NULL)){
		//bad request, Content-Lenght-Header obligatoire
		return -1;
	}

	node_CL = (Lnode *)token_CL->node;
	node_CT = (Lnode *)token_CT->node;
	node_Ref = (Lnode *)token_Ref->node;

	char* contentLength = calloc(node_CL->len + 1 , sizeof(char));
	char* contentType = calloc(node_CT->len + 1 , sizeof(char));
	char* referer = calloc(node_Ref->len + 1 , sizeof(char));

	strncpy(contentLength,node_CL->value,node_CL->len);
	strncpy(contentType,node_CT->value,node_CT->len);
	strncpy(referer,node_Ref->value,node_Ref->len);

	int longueur_MB = atoi(contentLength);

	addNameValuePair(header, "CONTENT_LENGTH", contentLength);
	addNameValuePair(header, "CONTENT_TYPE", contentType);
	addNameValuePair(header, "HTTP_REFERER", referer);

	free(contentLength);
	purgeElement(&token_CL);
	free(contentType);
	purgeElement(&token_CT);
	free(referer);
	purgeElement(&token_Ref);

	return longueur_MB;
}
