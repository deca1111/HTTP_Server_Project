#include "api.h"
#include "arbre.h"
#include "grammaire_simp.h"
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
  int res;
  char* valeur;
  racine = creerNoeud();
  valeur = &(req[0]);
  res = verifMessage(valeur, racine, 0, len);
  if(res != len){
    purgeTree(racine);
    return 0;
  }else{
    return res;
  }
}
