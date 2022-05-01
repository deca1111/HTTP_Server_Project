#include "server.h"

int main()
{
	message *requete;
	int res;
	int connection_status = CLOSE;
	while ( 1 ) {
		// on attend la reception d'une requete HTTP requete pointera vers une ressource allouée par librequest.
		if ((requete=getRequest(8080)) == NULL ) return -1;

		// Affichage de debug
		printf("#########################################\nDemande recue depuis le client %d\n",requete->clientId);
		printf("Client [%d] [%s:%d]\n",requete->clientId,inet_ntoa(requete->clientAddress->sin_addr),htons(requete->clientAddress->sin_port));
		printf("Contenu de la demande [%.*s]\n\n",requete->len,requete->buf);
		printf("ENVOI DE LA REPONSE SUIVANTE : [\n");

		if (!(res=parseur(requete->buf,requete->len))) {
			//bad request, parseur a pas reussi
			sendError400(requete->clientId);
			goto ENDWHILE;
		}

		_Token *r = NULL,*h = NULL,*root = NULL;
		Lnode *node, *node_host;
		int hasHost = 0;
		root=getRootTree();


		int HTTP_version = version(root);


		if(!(HTTP_version == HTTP1_0 || HTTP_version == HTTP1_1)){
			//version http non valide
			sendError505(requete->clientId);
			goto ENDWHILE_purge;
		}
		//version http valide

		int method = methode(root);

		if(!(method == GET_METHODE || method == HEAD_METHODE)){
			//Method not implemented
			sendError501(requete->clientId);
			goto ENDWHILE_purge;
		}
		//cas ou la methode est GET ou HEAD

		hasHost = ((h = searchTree(root,"uri_host")) == NULL)?0:1;

		if((HTTP_version == HTTP1_1) && (!hasHost)){
			//pas de host alors que http1.1, bad request
			sendError400(requete->clientId);
			goto ENDWHILE_purge;
		}

		//pour l'instant pas de prise en compte de la query
		r=searchTree(root,"absolute_path");
		node=(Lnode *)r->node;

		char* buffer = calloc(40, sizeof(char)), *tmp;
		tmp = decodePercent(node->value, node->len, buffer);

		//recherche du fichier demandé dans le serveur
		char* add = calloc(strlen(DIR_DATA) + (strlen(tmp)) + (size_t) MAX_SIZE, sizeof(char));
		strcatLen(add,DIR_DATA,0,strlen(DIR_DATA));

		if(hasHost){
			node_host = (Lnode *)h->node;
			strcat(add,"/");
			strcatLen(add,node_host->value,strlen(add),node_host->len);
		}

		strcatLen(add,tmp,strlen(add),strlen(tmp));

		free(tmp);
		
		int taille_fich;
		if ((taille_fich = checkIfFileExists(add)) == -1) {
			//fichier non trouvé
			sendError404(requete->clientId);
			goto ENDWHILE_add;
		}

		//ouverture du fichier
		int fichier = open(add, O_RDONLY);

		if(fichier == -1){
			perror("Probleme dans l'ouverture du fichier");
			exit(1);
		}

		//debut du message avec le 200...
		printf("(%s)", REPONSE_STATUS);
		writeDirectClient(requete->clientId,REPONSE_STATUS,strlen(REPONSE_STATUS));

		//on gere le type :
		char* type = mimeType(add);
		sendTypeHeader(type, requete->clientId);

		sendDateHeader(requete->clientId);

		if(method == GET_METHODE){
			sendLengthHeader(taille_fich, requete->clientId);
			sendFichier(fichier,taille_fich, requete->clientId);
		}else{
			sendLengthHeader(0, requete->clientId);
		}

		close(fichier);

		connection_status = connexion(root);

		ENDWHILE_add:
		free(add);

		ENDWHILE_purge:
		purgeElement(&r);
		purgeElement(&h);

		purgeTree(root);

		ENDWHILE:
		printf("]\n");

		endWriteDirectClient(requete->clientId);

		if(((connection_status == NO_HEADER) && (HTTP_version == HTTP1_0))||(connection_status == CLOSE)){
			requestShutdownSocket(requete->clientId);
		}

		// on ne se sert plus de requete a partir de maintenant, on peut donc liberer...
		freeRequest(requete);
	}
	return (1);
}
