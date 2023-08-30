#include "fonction.h"

char* matrice_type[SIZE_MIME][2]={
		{"html","text/html\r\n"},
		{"css","text/css\r\n"},
		{"js","application/javascript\r\n"},
		{"txt","text/plain\r\n"},
		{"png","image/png\r\n"},
		{"gif","image/gif\r\n"},
		{"jpg","image/jpeg\r\n"},
		{"mp4","video/mp4\r\n"},
		{"collection","font/collection\r\n"},
		{"bmp","image/bmp\r\n"},
		{"arc","application/octet-stream\r\n"},
		{"avi","video/x-msvideo\r\n"},
		{"bin","application/octet-stream\r\n"},
		{"sh","application/x-sh\r\n"},
		{"csv","text/csv\r\n"},
		{"epub","application/epub+zip\r\n"},
		{"ico","image/x-icon\r\n"},
		{"jar","application/java-archive\r\n"},
		{"jpeg","image/jpeg\r\n"},
		{"json","application/json\r\n"},
		{"mpeg","video/mpeg\r\n"},
		{"otf","font/otf\r\n"},
		{"pdf","application/pdf\r\n"},
		{"rar","application/x-rar-compressed\r\n"},
		{"swf","application/x-shockwave-flash\r\n"},
		{"tar","application/x-tar\r\n"},
		{"wav","audio/x-wav\r\n"},
		{"xml","application/xml\r\n"},
		{"zip","application/zip\r\n"},
		{"7z","application/x-7z-compressed\r\n"},
		{"php","isPHP"}
	};

	//renvoi 0 si les chaines sont identique sur la longueur l
int strcmpLen(char* c1, char* c2, int l){
		for(int i=0;i<l;i++){
			if(c1[i] != c2[i]){
				return 1;
			}
		}
		return 0;
	}

	//concatene c2 dans c1, il faut que c1 soit assez grand
void strcatLen(char* c1, char* c2, int l1, int l2){
		for(int i=0;i<l2;i++){
			c1[l1+i] = c2[i];
		}
	}

	//renvoi la taille du fichier si le fichier existe, -1 sinon
int checkIfFileExists(const char* filename){
	    struct stat buffer;
	    int exist = stat(filename,&buffer);
	    if(exist == 0)
	        return buffer.st_size;
	    else
	        return -1;
	}

char *get_filename_ext(char *filename) {
	    char *dot = strrchr(filename, '.');
	    if(!dot || dot == filename) return "";
	    return dot + 1;
	}

char* mimeType(char* nom_fichier){
		char* result = "application/octet-stream\r\n";
		char *ext = get_filename_ext(nom_fichier);
		for(int i = 0; i<SIZE_MIME; i++){
			if(strcmp(ext,matrice_type[i][0])==0){
				result = matrice_type[i][1];
			}
		}
		return result;
	}

int version (_Token * root){
	_Token *r = NULL;
	Lnode *node;
	r=searchTree(root,"HTTP_version");
	node=(Lnode *)r->node;
	int result;
	if(strcmpLen(node->value,"HTTP/1.1",node->len) == 0){
		result = HTTP1_1;
	}else if(strcmpLen(node->value,"HTTP/1.0",node->len) == 0){
		result = HTTP1_0;
	}else{
		result = EXIT_FAILURE;
	}
	purgeElement(&r);
	return result;
}

int methode(_Token * root){
	_Token *r = NULL;
	Lnode *node;
	r=searchTree(root,"method");
	node=(Lnode *)r->node;
	int result;
	if(strcmpLen(node->value,"GET",node->len) == 0){
		result = GET_METHODE;
	}else if(strcmpLen(node->value,"HEAD",node->len) == 0){
		result = HEAD_METHODE;
	}else if(strcmpLen(node->value,"POST",node->len) == 0){
		result = POST_METHODE;
	}else{
		result = EXIT_FAILURE;
	}
	purgeElement(&r);
	return result;
}

int connexion(_Token * root){
	_Token *r = NULL;
	Lnode *node;
	r=searchTree(root,"connection_option");
	int result;
	if(r == NULL){
		result = NO_HEADER;
	}else{
		node=(Lnode *)r->node;
		if(strcmpLen(node->value,"close",node->len) == 0){
			result = CLOSE;
		}else if(strcmpLen(node->value,"keep-alive",node->len) == 0){
			result = KEEP_ALIVE;
		}else{
			result = WRONG_SYNTAX;
		}
	}
	purgeElement(&r);
	return result;
}



char* decodePercent(char* src, int len, char* buffer){
	int j = 0, value = 0;
	char petit_buffer[2];
	for(int i = 0; i < len; i++){
		if(src[i] == '%'){
			petit_buffer[0] = src[i+1];
			petit_buffer[1] = src[i+2];
			value = (int) strtol(petit_buffer,NULL,16);
			buffer[j++] = (char) value;
			i+=2;
		}else{
			buffer[j++] = src[i];
		}
	}
	return buffer;
}

void sendLengthHeader(int taille_fich, unsigned int clientID){
	//Header Length
	char length [40];snprintf (length,40, "%d\r\n", taille_fich);
	char* header_length = calloc(strlen(REPONSE_CONTENT_LENGTH) + strlen(length) + 1, sizeof(char));
	if(header_length == NULL){
		printf("Probleme calloc\n");
		exit(1);
	}
	strcat(header_length,REPONSE_CONTENT_LENGTH);
	strcat(header_length,length);
	printf("(%s)", header_length);

	writeDirectClient(clientID,header_length,strlen(header_length));
	free(header_length);
}

void sendFichier(int fichier, int taille_fich, unsigned int clientID){
	writeDirectClient(clientID,SAUT_DE_LIGNE,strlen(SAUT_DE_LIGNE));
	char * pointeur;
	if ((pointeur = mmap(NULL, taille_fich, PROT_WRITE, MAP_PRIVATE, fichier, 0)) == NULL){
		printf("Probleme mmap\n");
		exit(1);
	}
	writeDirectClient(clientID,pointeur,taille_fich);
}

void sendTypeHeader(char* type, unsigned int clientID){
	char* header_type = calloc(strlen(REPONSE_CONTENT_TYPE) + strlen(type) + 1, sizeof(char));
	strcat(header_type,REPONSE_CONTENT_TYPE);
	strcat(header_type,type);
	printf("(%s)", header_type);
	writeDirectClient(clientID,header_type,strlen(header_type));
	free(header_type);
}

void sendDateHeader(unsigned int clientID){
	time_t timestamp = time( NULL );
	struct tm * gmtTime = gmtime( & timestamp );

	char date[MAX_SIZE];
	int longueur;
	longueur = strftime( date, MAX_SIZE, "%a, %d %b %Y %H:%M:%S GMT\r\n", gmtTime );
	char* header_date = calloc(strlen(REPONSE_DATE) + longueur + 1, sizeof(char));
	strcat(header_date,REPONSE_DATE);
	strcat(header_date,date);
	printf("(%s)", header_date);

	writeDirectClient(clientID,header_date,strlen(header_date));
	free(header_date);
}

void parsePhpContent(char * content, char * new[2]){
	int index = 0;
	while (index < (int) strlen(content) && content[index] != '\n'){
		index ++;
	}

	new[0] = calloc(index + 1, sizeof(char));
	new[1] = calloc(strlen(content) - index + 1, sizeof(char));
	strncpy(new[0], content, index - 1);
	strncpy(new[1], content + index, strlen(content) - index);
}


void sendPhpResponse(char* content, unsigned int clientID){
	char * new[2];

	parsePhpContent(content, new);


	writeDirectClient(clientID,REPONSE_STATUS,strlen(REPONSE_STATUS));
	sendTypeHeader(new[0], clientID);
	sendLengthHeader(strlen(new[1]),clientID);
	writeDirectClient(clientID,SAUT_DE_LIGNE,strlen(SAUT_DE_LIGNE));
	writeDirectClient(clientID,new[1],strlen(new[1]));

	free(new[0]);
	free(new[1]);
}

void sendPhpError(char * error, char* content, unsigned int clientID){
	char * new[2];

	parsePhpContent(content, new);

	writeDirectClient(clientID,REPONSE_STATUS,strlen(REPONSE_STATUS));
	sendTypeHeader("text/plain\r\n", clientID);
	sendLengthHeader(strlen(new[0]) + strlen(error),clientID);
	writeDirectClient(clientID,SAUT_DE_LIGNE,strlen(SAUT_DE_LIGNE));
	char * buffer = calloc(strlen(new[0]) + strlen(error) + 2 + strlen(PETITE_JOKE), sizeof(char));
	strcat(buffer, PETITE_JOKE);
	strcat(buffer, new[0]);
	strcat(buffer, "\n\n");
	strcat(buffer, error);


	writeDirectClient(clientID,buffer,strlen(buffer));
	free(buffer);
	free(new[0]);
	free(new[1]);
}


void sendAllowHeader(char* method_allowed, unsigned int clientID){
	char* header_allow = calloc(strlen(REPONSE_ALLOW) + strlen(method_allowed) + 1, sizeof(char));
	strcat(header_allow,REPONSE_ALLOW);
	strcat(header_allow,method_allowed);
	printf("(%s)", header_allow);
	writeDirectClient(clientID,header_allow,strlen(header_allow));
	free(header_allow);
}


void sendError400(unsigned int clientID){
	printf("(%s)",ERROR_400);
	writeDirectClient(clientID,ERROR_400,strlen(ERROR_400));
}

void sendError404(unsigned int clientID){
	printf("(%s)",ERROR_404);
	writeDirectClient(clientID,ERROR_404,strlen(ERROR_404));
}

void sendError505(unsigned int clientID){
	printf("(%s)",ERROR_505);
	writeDirectClient(clientID,ERROR_505,strlen(ERROR_505));
}

void sendError501(unsigned int clientID){
	printf("(%s)",ERROR_501);
	writeDirectClient(clientID,ERROR_501,strlen(ERROR_501));
}

void sendError405(unsigned int clientID){
	printf("(%s)",ERROR_405);
	writeDirectClient(clientID,ERROR_405,strlen(ERROR_405));
}
