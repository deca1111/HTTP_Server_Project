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
		{"7z","application/x-7z-compressed\r\n"}
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

int version (Lnode * node){
	int result;
	if(strcmpLen(node->value,"HTTP/1.1",node->len) == 0){
		result = HTTP1_1;
	}else if(strcmpLen(node->value,"HTTP/1.0",node->len) == 0){
		result = HTTP1_0;
	}else{
		result = EXIT_FAILURE;
	}
	return result;
}

int methode(Lnode *node){
	int result;
	if(strcmpLen(node->value,"GET",node->len) == 0){
		result = GET_METHODE;
	}else if(strcmpLen(node->value,"HEAD",node->len) == 0){
		result = HEAD_METHODE;
	}else{
		result = EXIT_FAILURE;
	}
	return result;
}

void sendLengthHeader(int taille_fich, unsigned int clientID){
	//Header Length
	int longueur;
	char length [40];
	longueur = snprintf (length,40, "%d\r\n", taille_fich);
	printf("Taille : [%s], longueur : %d",length,longueur);
	char* header_length = calloc(strlen(REPONSE_CONTENT_LENGTH) + strlen(length), sizeof(char));
	if(header_length == NULL){
		printf("Probleme calloc\n");
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
	char* header_type = calloc(strlen(REPONSE_CONTENT_TYPE) + strlen(type), sizeof(char));
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
	printf("Date : [%s], longueur : %d\n",date, longueur);
	char* header_date = calloc(strlen(REPONSE_DATE) + longueur, sizeof(char));
	strcat(header_date,REPONSE_DATE);
	strcat(header_date,date);
	printf("(%s)", header_date);

	writeDirectClient(clientID,header_date,strlen(header_date));
	free(header_date);
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

int calculer_Header(char * buffer, char *header_content, int type){
	int result = 1;
	switch(type){
		case HEADER_TYPE:
			strcat(buffer,REPONSE_CONTENT_TYPE);
			strcat(buffer,header_content);
			printf("(%s)", buffer);

			break;
		case HEADER_LENGTH:
			strcat(buffer,REPONSE_CONTENT_LENGTH);
			strcat(buffer,header_content);
			printf("(%s)", buffer);
			break;
		default:
			result = EXIT_FAILURE;
	}
	return result;
}
