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

		_Token *token_host = NULL,*token_query = NULL,*root = NULL,*token_path = NULL;
		Lnode *node_path, *node_host, *node_query;

		root=getRootTree();

		//initialisation des donnés parsées
		token_host = searchTree(root,"uri_host");
		token_path = searchTree(root,"absolute_path");
		token_query = searchTree(root,"query");

		int hasHost = (token_host== NULL)?0:1;
		int hasQuery = (token_query== NULL)?0:1;

		if(hasHost){
			node_host = (Lnode *)token_host->node;
		}

		if(hasQuery){
			node_query = (Lnode *)token_query->node;
		}

		node_path = (Lnode *)token_path->node;


		int HTTP_version = version(root);
		int method = methode(root);


		if(!(HTTP_version == HTTP1_0 || HTTP_version == HTTP1_1)){
			//version http non valide
			sendError505(requete->clientId);
			goto ENDWHILE_purge;
		}
		//version http valide


		if((HTTP_version == HTTP1_1) && (!hasHost)){
			//pas de host alors que http1.1, bad request
			sendError400(requete->clientId);
			goto ENDWHILE_purge;
		}


		if(!(method == GET_METHODE || method == HEAD_METHODE || method == POST_METHODE)){
			//Method not implemented
			sendError501(requete->clientId);
			goto ENDWHILE_purge;
		}



		//decodage du percent encoding sur l'@ du fichier
		char* buffer = calloc(40, sizeof(char)), *tmp;
		tmp = decodePercent(node_path->value, node_path->len, buffer);

		char* type = mimeType(tmp);

		int isPHP = (strcmp(type,"isPHP"))?0:1;

		//recherche du fichier demandé dans le serveur
		char* add_serv_http = calloc(strlen(DIR_DATA) + (strlen(tmp)) + (size_t) MAX_SIZE, sizeof(char));
		char* add_serv_php = calloc((strlen(tmp)) + (size_t) MAX_SIZE, sizeof(char));
		strcatLen(add_serv_http,DIR_DATA,0,strlen(DIR_DATA));

		if(hasHost){
			strcat(add_serv_http,"/");
			strcatLen(add_serv_http,node_host->value,strlen(add_serv_http),node_host->len);
			strcatLen(add_serv_php,node_host->value,strlen(add_serv_php),node_host->len);
		}

		strcatLen(add_serv_http,tmp,strlen(add_serv_http),strlen(tmp));
		strcatLen(add_serv_php,tmp,strlen(add_serv_php),strlen(tmp));

		free(tmp);

		if((method == POST_METHODE && !isPHP) || (method == HEAD_METHODE && isPHP)){
			//fichier php et methode HEAD ou methode POST et pas de fichier php
			sendError405(requete->clientId);
			if (method == POST_METHODE){
				sendAllowHeader("GET, HEAD\r\n", requete->clientId);
			}else{
				sendAllowHeader("GET, POST\r\n", requete->clientId);
			}
			writeDirectClient(requete->clientId,SAUT_DE_LIGNE,strlen(SAUT_DE_LIGNE));
			goto ENDWHILE_add;
		}

		if (isPHP) {
			
		}

		int taille_fich;
		if ((taille_fich = checkIfFileExists(add_serv_http)) == -1) {
			//fichier non trouvé
			sendError404(requete->clientId);
			goto ENDWHILE_add;
		}

		//ouverture du fichier
		int fichier = open(add_serv_http, O_RDONLY);

		if(fichier == -1){
			perror("Probleme dans l'ouverture du fichier");
			exit(1);
		}

		//debut du message avec le 200...
		printf("(%s)", REPONSE_STATUS);
		writeDirectClient(requete->clientId,REPONSE_STATUS,strlen(REPONSE_STATUS));

		//on gere le type :
		sendTypeHeader(type, requete->clientId);

		sendDateHeader(requete->clientId);

		if(method == GET_METHODE){
			sendLengthHeader(taille_fich, requete->clientId);
			sendFichier(fichier,taille_fich, requete->clientId);
		}else{
			sendLengthHeader(0, requete->clientId);
		}

		close(fichier);



		ENDWHILE_add:
		free(add_serv_http);
		free(add_serv_php);



		ENDWHILE_purge:
		connection_status = connexion(root);

		purgeElement(&token_host);
		purgeElement(&token_path);
		purgeElement(&token_query);

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
