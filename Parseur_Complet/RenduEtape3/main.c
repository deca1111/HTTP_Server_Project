#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>

#include "api.h"
#include "arbre.h"

#define false 0


int main(int argc,char *argv[])
{
	int res,fi;
	char *p=NULL,*addr;


        struct stat st;

	if (argc < 3 ) { printf("Usage: httpparser <file> <search>\nAttention <search> is case sensitive\n"); exit(1); }
	/* ouverture du fichier contenant la requête */
	if ((fi=open(argv[1],O_RDWR)) == -1) {
                perror("open");
                return false;
        }
        if (fstat(fi, &st) == -1)           /* To obtain file size */
                return false;
        if ((addr=mmap(NULL,st.st_size,PROT_WRITE,MAP_PRIVATE, fi, 0)) == NULL )
                return false;

	// This is a special HACK since identificateur in C can't have character '-'

	if (argc == 3 ) {
		p=argv[2];
		//printf("searching for %s\n",p);
		while (*p) {
			if (*p=='-') { *p='_'; }
			p++;
		}
		p=argv[2];
	}

	printf("\n******************************************************\nMessage à analyser : [%.*s]\n******************************************************\n\n",((int) st.st_size),addr );

	// call parser and get results.
	if ((res=parseur(addr,st.st_size))) {
		printf("Retour du parseur : %d\n\n",res);
		_Token *r,*tok;
		void *root=NULL;
		root=getRootTree();
		r=searchTree(root,p);
		printf("Recherche de [%s] : \n",p);
		tok=r;
		while (tok) {
			int l;
			char *s;
			s=getElementValue(tok->node,&l);
			printf("FOUND [%.*s]\n",l,s);
			tok=tok->next;
		}
		printf("\n");
		//afficherArbre(getRootTree());
		purgeElement(&r);
		purgeTree(root);
	}/*else{
		printf("Resultat du parseur : %d\n",res );
		afficherArbre(getRootTree());
	}*/

	close(fi);
	return(res);
}
