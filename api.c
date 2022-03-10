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
  printf("premier_element = %p\n", premier_element);
  premier_element = temp->next;
  printf("premier_element = %p\n", premier_element);
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
    printf("token->next = %p, precedent = %p\n", token->next, precedent);

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

  valeur_ = noeud->valeur;

  if(len!=NULL){
    *len = noeud->longueur;
  }

  return valeur_;
}

void purgeElement(_Token **r){
  if((*r)->next != NULL){
    purgeElement(&((*r)->next));
  }
  free(*r);
}


void purgeTree(void *root){
  Noeud * noeud = (Noeud*) root;

  //printf("noeuds = %p\n", noeud);
  if(noeud->frere != NULL){
    //printf("purgeTree(%p)\n",noeud->frere);
    purgeTree(noeud->frere);
  }
  //printf("noeud->fils = (%p)\n",noeud->fils);
  if(noeud->fils != NULL){
    //printf("purgeTree(%p)\n",noeud->fils);
    purgeTree(noeud->fils);

  }
  //printf("noeud->frere = (%p)\n",noeud->frere);
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
  if(token->node != 0){
    printf("[Tag]: _%s_\t[Valeur]: _%s_\n",getElementTag(token->node, NULL), getElementValue(token->node, NULL));
  }


}
