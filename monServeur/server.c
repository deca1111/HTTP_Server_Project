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


		//verif parseur, message conforme rfc
		if (!(res=parseur(requete->buf,requete->len))) {
			//bad request, parseur a pas reussi
			sendError400(requete->clientId);
			goto ENDWHILE;
		}

		//declaration des var
		_Token *token_host = NULL,*token_query = NULL,*root = NULL,*token_path = NULL,*token_body=NULL;
		Lnode *node_path, *node_host, *node_query, *node_body;

		root=getRootTree();

		//initialisation des donnés parsées et des variables "booléennes"
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

		//verif version http
		if(!(HTTP_version == HTTP1_0 || HTTP_version == HTTP1_1)){
			//version http non valide
			sendError505(requete->clientId);
			goto ENDWHILE_purge;
		}
		//version http valide

		//verif que si HTTP 1.1 alors Host
		if((HTTP_version == HTTP1_1) && (!hasHost)){
			//pas de host alors que http1.1, bad request
			sendError400(requete->clientId);
			goto ENDWHILE_purge;
		}


		//verif methode implémentée
		if(!(method == GET_METHODE || method == HEAD_METHODE || method == POST_METHODE)){
			//Method not implemented
			sendError501(requete->clientId);
			goto ENDWHILE_purge;
		}



		//decodage du percent encoding sur l'@ du fichier
		char* path = calloc(MAX_SIZE, sizeof(char));
		path = decodePercent(node_path->value, node_path->len, path);

		//on recupere le mime type du fichier
		char* type = mimeType(path);

		//on check si c'est un fichier php
		int isPHP = (strcmp(type,"isPHP"))?0:1;

		//recherche du fichier demandé dans le serveur
		char* add_serv_http = calloc(strlen(DIR_DATA) + (strlen(path)) + (size_t) MAX_SIZE, sizeof(char));
		char* add_serv_php = calloc(strlen(START_PHP_FILENAME)  + (strlen(path)) + (size_t) MAX_SIZE, sizeof(char));
		char* script_name = calloc((strlen(path)) + (size_t) MAX_SIZE, sizeof(char));
		strcatLen(add_serv_http,DIR_DATA,0,strlen(DIR_DATA));
		strcatLen(add_serv_php,START_PHP_FILENAME,0,strlen(START_PHP_FILENAME));

		if(hasHost){
			strcat(add_serv_http,"/");
			strcat(script_name,"/");
			strcatLen(add_serv_http,node_host->value,strlen(add_serv_http),node_host->len);
			strcatLen(script_name,node_host->value,strlen(script_name),node_host->len);
		}

		strcatLen(add_serv_http,path,strlen(add_serv_http),strlen(path));
		strcatLen(script_name,path,strlen(script_name),strlen(path));
		strcatLen(add_serv_php,script_name,strlen(add_serv_php),strlen(script_name));

		free(path);

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

		//comportement en cas de fichier php (GET ou POST)
		if (isPHP) {

			//initialisation communication PHP
			FCGI_Header header;
			bzero(&header, sizeof(header));
			int fd = createSocket(9000);
			sendBeginRequest(fd,10,FCGI_RESPONDER,FCGI_KEEP_CONN);

			char *query;
			//on gere les query
			if(hasQuery){
				query = calloc(node_query->len + 1, sizeof(char));
				strncpy(query, node_query->value, node_query->len);
				addNameValuePair(&header, "QUERY_STRING", query);
			}else{
				addNameValuePair(&header, "QUERY_STRING", NULL);
			}
			//completion et envoie du header fcgi
			//completeParamsConst(&header);
			printf("Script name : [%s]\nScript filename : [%s]\nLongueur : %d\n",script_name,add_serv_php,(int) strlen(add_serv_php));

			addNameValuePair(&header, "REQUEST_METHOD", (method == POST_METHODE)?"POST":"GET");
			addNameValuePair(&header, "SCRIPT_NAME", script_name);
			addNameValuePair(&header, "SCRIPT_FILENAME", add_serv_php);


			//on gere le message body
			if(method == POST_METHODE){

				int longueur_MB = fillHeaderPost(&header, root);

				if(longueur_MB == -1){
					sendError400(requete->clientId);
					goto ENDWHILE_add;
				}
				sendParams(fd, 10, header.contentData, header.contentLength);
				sendParams(fd, 10, NULL, 0);


				if(hasQuery) free(query);

				//envoi du message body
				if(longueur_MB == 0){
					sendStdin(fd, 10, "", 0);
				}else{

					token_body = searchTree(root,"message_body");

					if(token_body==NULL){
						//bad request, pas de message body
						sendError400(requete->clientId);
						goto ENDWHILE_add;
					}

					node_body = (Lnode *)token_body->node;
					printf("envoi du message body: 1\n");
					sendStdin(fd, 10, node_body->value, longueur_MB);

				}
			}else{
				sendParams(fd, 10, header.contentData, header.contentLength);
				sendParams(fd, 10, NULL, 0);

				if(hasQuery) free(query);

				sendStdin(fd, 10, "", 0);
			}
			//lecture de la reponse
			char* response[2];

			if(readResponse(fd, response) == ERROR_PHP){
				sendPhpError(response[0], response[1], requete->clientId);
			}else{
				sendPhpResponse(response[1], requete->clientId);
			}

			printf("Error = _%s_\n",response[0]);
			printf("Content = _%s_\n",response[1]);


			free(response[0]);
			free(response[1]);
			close(fd);
			goto ENDWHILE_add;
		}

		int taille_fich;
		printf("serveur http: [%s]\n", add_serv_http);
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
		free(script_name);



		ENDWHILE_purge:
		connection_status = connexion(root);

		purgeElement(&token_host);
		purgeElement(&token_path);
		purgeElement(&token_query);
		purgeElement(&token_body);

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
