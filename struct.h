#ifndef __STRUCTURE__
#define __STRUCTURE__

typedef struct _token {
		void *node;  		// node type opaque pointant vers un noeud de votre structure de données.
		struct _token *next; 	// next pointe vers le prochain token.
}_Token;

typedef struct Noeud{
  char* tag;

  char* valeur;
  int longueur;
  int profondeur;

  struct Noeud* fils;
  struct Noeud* frere;

} Noeud;

#endif
