#include "socket.h"
#include "fonction.h"
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
#define MAX_SIZE 100
void afficherHeader(FCGI_Header * header){
	printf("// ----- Affichage header ----- //\n");
	printf("version : _%d_\n", header->version);
	printf("type : _%d_\n", header->type);
	printf("requestId : _%d_\n", ntohs(header->requestId));
	printf("contentLength : _%d_\n", ntohs(header->contentLength));
	printf("paddingLength : _%d_\n", header->paddingLength);
	printf("// ---------------------------- //\n");
}
// =========================================================================================================== //
void readResponse(int fd, char * content){
	int ret;
	FCGI_Header head_temp;
	// lecture du premier header
	if((ret = read(fd, &head_temp, FCGI_HEADER_SIZE)) == -1){
		perror("erreur de lecture du header\n");
		return;
	}
	afficherHeader(&head_temp);
	int taille_lu;
	int taille_totale_lu = 0;
	int taille_a_lire;
	// tant qu'on a pas le header de fin, on continue
	while(head_temp.type != FCGI_END_REQUEST){
		if((content = realloc(content, sizeof(char) * ntohs(head_temp.contentLength) + taille_totale_lu)) == NULL ){
			perror("erreur allocation memoire\n");
			return;
		}
		taille_a_lire = ntohs(head_temp.contentLength);
		taille_lu = 0;
		// on lit tout le stdout
		while(taille_lu < taille_a_lire){
			ret = read(fd, content + taille_totale_lu, taille_a_lire - taille_lu);
			if(ret == -1){
				perror("erreur lecture\n");
				return;
			}
			printf("content : _%s_, taille_totale_lu : %d\n", content+taille_totale_lu, taille_totale_lu);
			taille_lu += ret;
			taille_totale_lu += ret;

		}
		// on lit le padding
		taille_a_lire = head_temp.paddingLength;
		taille_lu = 0;
		char * buff = malloc(taille_a_lire * sizeof(char));
		while(taille_lu < taille_a_lire){
			ret = read(fd, buff, taille_a_lire - taille_lu);
			if(ret == -1){
				perror("erreur lecture\n");
				return;
			}
			printf("content : _%s_, taille_totale_lu : %d\n", content+taille_totale_lu, taille_totale_lu);
			taille_lu += ret;

		}
		free(buff);
	// lecture du nouveau FCGI_Header
	if((ret = read(fd, &head_temp, FCGI_HEADER_SIZE)) == -1){
		perror("erreur de lecture du header\n");
		return;
	}

	afficherHeader(&head_temp);
	}
}
// =========================================================================================================== //
void completeParamsConst(FCGI_Header * header){
	addNameValuePair(header, "GATEWAY_INTERFACE", "CGI/1.1");
	addNameValuePair(header, "SERVER_NAME", "127.0.0.1");
	addNameValuePair(header, "SERVER_ADDR", "127.0.0.1");
	addNameValuePair(header, "SERVER_PORT", "8080");
	addNameValuePair(header, "SERVER_PROTOCOL", "HTTP/1.1");
	addNameValuePair(header, "REQUEST_SCHEME", "http");
	addNameValuePair(header, "DOCUMENT_ROOT", "/home/leovalette/Documents/3A/S2/NE302/HTTP_Server_Project/monServeur/dataPhpServer");
	addNameValuePair(header, "CONTEXT_DOCUMENT_ROOT", "/home/leovalette/Documents/3A/S2/NE302/HTTP_Server_Project/monServeur/dataPhpServer");

}
/*
int test(int argc,char *argv[]){
	int fd;
	FCGI_Header header;
	char * name[500][2] = {{"SCRIPT_FILENAME", "/var/www/html/index.php"}};
	for(int i = 1; i<500 ; i++){
		name[i][0] = NULL;
		name[i][1] = NULL;
	}
	char ** content = calloc(1, sizeof(char));
	// creation du header params
	completeParamsHeader(&header, name);
	// creation de la socket
	fd=createSocket(9000);
	// envoie du begin request
	sendBeginRequest(fd,10,FCGI_RESPONDER,FCGI_KEEP_CONN);
	// envoi des params
	sendParams(fd, 10, header.contentData, header.contentLength);
	// envoi du stdin
	sendStdinToPhp(fd, "coucou", 6, content);
	printf("Result = _%s_\n",*content);
	free(content);
	return 0;


























}
*/
