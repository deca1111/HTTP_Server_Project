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
		char* result = NULL;
		char *ext = get_filename_ext(nom_fichier);
		for(int i = 0; i<SIZE_MIME; i++){
			if(strcmp(ext,matrice_type[i][0])==0){
				result = matrice_type[i][1];
			}
		}
		return result;
	}
