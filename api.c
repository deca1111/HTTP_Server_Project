#include "api.h"
#include "arbre.h"




Noeud* racine;
char* request_line;


void *getRootTree(){
  return racine;
}

_Token *searchTree(void *start,char *name){

  _Token* racine;

  if(start == NULL){
    recursifSearchTree(getRootTree(), name, racine);
  }else{
    recursifSearchTree(start, name, racine);
  }

  return racine;

}

_Token *recursifSearchTree(Noeud *noeud, char *name, _Token* token){

  char* tag = getElementTag(noeud, NULL);

  if(strcmp(tag,name) == 0){
    token = creerToken();
    token->node =
  }

  if(noeud->fils != NULL){
    recursifSearchTree(noeud->fils);
  }

  if(noeud->frere != NULL){
    recursifSearchTree(noeud->frere);
  }
}

char *getElementTag(void *node,int *len){
  Noeud* noeud;
  char* tag_;

  noeud = (Noeud*) node;
  tag_ = noeud->tag;

  if(len!=NULL){
    *len = strlen(noeud->tag);
  }

  return tag_;
}

char *getElementValue(void *node,int *len){
  Noeud* noeud;
  char* valeur_;

  noeud = (Noeud*) node;
  valeur_ = malloc(sizeof(char) * ((noeud->longueur)+ 1));
  for(int i = 0; i < noeud->longueur; i++){
    *(valeur_+i) = *((noeud->valeur)+i);
  }
  valeur_[noeud->longueur] = '\0';

  if(len!=NULL){
    *len = noeud->longueur;
  }

  return valeur_;
}

void purgeElement(_Token **r){

}


void purgeTree(void *root){
  Noeud * noeud;
  noeud = (Noeud*) root;

  if(noeud->fils != NULL){
    purgeTree(noeud->fils);
  }
  if(noeud->frere != NULL){
    purgeTree(noeud->frere);
  }

  printf("Free d'un [%s] : [%s]\n", getElementTag(noeud,NULL), getElementValue(noeud,NULL));

  free(noeud);
}

int parseur(char *req, int len){

}

_Token* creerToken(){
  _Token* token = (_Token*) malloc(sizeof(_Token));
  token->node = NULL;
  token->next = NULL;

  return token;
}

void afficheToken(_Token* racine){

}
