#include "api.h"





Noeud* racine;
char* request_line;


void *getRootTree(){
  return racine;
}

_Token *searchTree(void *start,char *name){

  //premier element de la liste chainee
  _Token* premier_element = creerToken();
  _Token* temp;
  if(start == NULL){
    temp = recursifSearchTree(getRootTree(), name, premier_element);
  }else{
    temp = recursifSearchTree((Noeud*)start, name, premier_element);
  }
  premier_element = temp->next;
  free(temp);
  return premier_element;

}

_Token *recursifSearchTree(Noeud *noeud, char *name, _Token* token){

  char* tag = getElementTag(noeud, NULL);
  _Token* precedent = token;
  if(strcmp(tag,name) == 0){
    precedent = creerToken();
    precedent->next = token;
    token->node = (void*)noeud;

  }

  if(noeud->fils != NULL){
    precedent = recursifSearchTree(noeud->fils, name, precedent);
  }

  if(noeud->frere != NULL){
    precedent = recursifSearchTree(noeud->frere, name, precedent);
  }

  return precedent;
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
  //printf("[Tag]: _%d_\t[Valeur]: _%s_\n",getElementTag(r, NULL), getElementValue((*r)->node, NULL));
  if((*r)->next != NULL){
    printf("coucou\n");
    purgeElement((*r)->next);
  }
  //free(*r);
}


void purgeTree(void *root){
  Noeud * noeud = (Noeud*) root;

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

void afficheToken(_Token* token){

  if(token->next != NULL){
    afficheToken(token->next);
  }
    printf("[Tag]: _%s_\t[Valeur]: _%s_\n",getElementTag(token->node, NULL), getElementValue(token->node, NULL));

}
