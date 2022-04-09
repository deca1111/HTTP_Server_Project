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
// for librequest
#include "request.h"

// for parser

// this will declare internal type used by the parser
#include "httpparser.h"
#include "api.h"


#define DIR_DATA "./dataServeur"
#define ERROR_400 "HTTP/1.0 400 SUCKA\r\n\r\n"
#define ERROR_405 "HTTP/1.0 405 Method Not Allowed\r\nAccepted Method : GET\r\n"
#define ERROR_404 "HTTP/1.0 404 Not Found\r\n\r\n"
#define REPONSE_STATUS "HTTP/1.0 200 OK\r\n"
#define REPONSE_CONTENT_TYPE "Content-type: "
#define SAUT_DE_LIGNE "\r\n"
#define SIZE_MIME 7
char* matrice_type[SIZE_MIME][2]={
		{"html","text/html\r\n"},
		{"css","text/css\r\n"},
		{"js","application/javascript\r\n"},
		{"txt","text/plain\r\n"},
		{"png","image/png\r\n"},
		{"gif","image/gif\r\n"},
		{"jpg","image/jpeg\r\n"}
	};

//renvoi 0 si les chaines sont identique sur la longueur l
int strcmpLen(char* c1, char* c2, int l){
	int result = 0;
	for(int i=0;i<l;i++){
		result+=c1[i]-c2[i];
	}
	return result;
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
	char* result = NULL;
	char *ext = get_filename_ext(nom_fichier);
	for(int i = 0; i<SIZE_MIME; i++){
		if(strcmp(ext,matrice_type[i][0])==0){
			result = matrice_type[i][1];
		}
	}
	return result;
}

int main(int argc, char *argv[])
{
	message *requete;
	int res;
	while ( 1 ) {
		// on attend la reception d'une requete HTTP requete pointera vers une ressource allouée par librequest.
		if ((requete=getRequest(8080)) == NULL ) return -1;

		// Affichage de debug
		printf("#########################################\nDemande recue depuis le client %d\n",requete->clientId);
		printf("Client [%d] [%s:%d]\n",requete->clientId,inet_ntoa(requete->clientAddress->sin_addr),htons(requete->clientAddress->sin_port));
		printf("Contenu de la demande %.*s\n\n",requete->len,requete->buf);
		printf("ENVOI DE LA REPONSE SUIVANTE : [\n");

		if ((res=parseur(requete->buf,requete->len))) {
			_Token *r = NULL,*root = NULL;

			// get the root of the tree this is no longer opaque since we know the internal type with httpparser.h
			//void *root;
			//writeDirectClient(requete->clientId,REPONSE,strlen(REPONSE));
			root=getRootTree();
			r=searchTree(root,"method");
			// node is no longer opaque
			Lnode *node;
			node=(Lnode *)r->node;

			//cas ou la methode est GET
			if(strcmpLen(node->value,"GET",node->len) == 0){
				r=searchTree(root,"request_target");
				node=(Lnode *)r->node;

				//recherche du fichier demandé dans le serveur
				char* add = calloc(strlen(DIR_DATA) + (node->len), sizeof(char));

				strcatLen(add,DIR_DATA,0,strlen(DIR_DATA));
				strcatLen(add,node->value,strlen(add),node->len);

				int taille_fich;


				if ((taille_fich = checkIfFileExists(add)) != -1) {

					//ouverture du fichier
					int fichier = open(add, O_RDONLY);

					if(fichier != -1){
						printf("Taille fichier %d\n", taille_fich);
						int compteur = taille_fich;
						int taille_temp;


						printf("(%s)\n", REPONSE_STATUS);
						writeDirectClient(requete->clientId,REPONSE_STATUS,strlen(REPONSE_STATUS));
						//on gere le type :

						char* type = mimeType(add);
						char* header_type = calloc(strlen(REPONSE_CONTENT_TYPE) + strlen(type), sizeof(char));
						strcat(header_type,REPONSE_CONTENT_TYPE);
						strcat(header_type,type);
						printf("(%s)\n", header_type);
						writeDirectClient(requete->clientId,header_type,strlen(header_type));


						free(header_type);

						writeDirectClient(requete->clientId,SAUT_DE_LIGNE,strlen(SAUT_DE_LIGNE));

						//recopie du fichier
						char * pointeur;
						if ((pointeur = mmap(NULL, taille_fich, PROT_WRITE, MAP_PRIVATE, fichier, 0)) == NULL){
							printf("Probleme mmap\n");
							exit(1);
						}
						writeDirectClient(requete->clientId,pointeur,taille_fich);

					}else{
						perror("Probleme dans l'ouverture du fichier");
						exit(1);
					}

				}else{
					//sinon : fichier non trouvé
					printf("(%s)",ERROR_404);
					writeDirectClient(requete->clientId,ERROR_404,strlen(ERROR_404));
				}
				free(add);
				//writeDirectClient(requete->clientId,node->value,node->len);
			}else{
				//sinon : method not allowed
				printf("(%s)",ERROR_405);
				writeDirectClient(requete->clientId,ERROR_405,strlen(ERROR_405));
			}
			purgeElement(&r);
			purgeTree(root);
		} else {
		printf("(%s)",ERROR_400);
			writeDirectClient(requete->clientId,ERROR_400,strlen(ERROR_400));
		}

		printf("]\n");
		endWriteDirectClient(requete->clientId);
		requestShutdownSocket(requete->clientId);
	// on ne se sert plus de requete a partir de maintenant, on peut donc liberer...
	freeRequest(requete);
	}
	return (1);
}
