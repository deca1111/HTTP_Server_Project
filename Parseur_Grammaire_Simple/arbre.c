#include "arbre.h"

Noeud* creerNoeud(){

  Noeud* nouveau = (Noeud*) malloc(sizeof(Noeud));
  nouveau->valeur = NULL;
  nouveau->longueur = 0;
  nouveau->frere = NULL;
  nouveau->fils = NULL;
  nouveau->profondeur = 0;

  return nouveau ;
}

Noeud* creerFils(Noeud* n){
  Noeud* nouveau = creerNoeud();
  n->fils = nouveau;
  nouveau->profondeur = n->profondeur + 1;
  return nouveau ;
}

Noeud* creerFrere(Noeud* n){
  Noeud* nouveau = creerNoeud();
  n->frere = nouveau;
  nouveau->profondeur = n->profondeur;
  return nouveau ;
}

void setNoeud(Noeud* noeud_, char* tag_, char* valeur_, int longueur_){
  noeud_->tag = tag_ ;
  noeud_->valeur = valeur_ ;
  noeud_->longueur= longueur_ ;
}

void afficherArbre(Noeud* noeud){

  for(int i = 0; i < noeud->profondeur; i++){
    printf("\t");
  }
  printf("[%d] - [%s] : {",noeud->profondeur,noeud->tag);
  for(int i = 0; i < noeud->longueur; i++){
    printf("%c",*(noeud->valeur + i));
  }
  printf("}\n");

  if(noeud->fils != NULL){
    afficherArbre(noeud->fils);
  }

  if(noeud->frere != NULL){
    afficherArbre(noeud->frere);
  }
}

_Token* creerToken(){
  _Token* token = (_Token*) malloc(sizeof(_Token));
  token->node = NULL;
  token->next = NULL;

  return token;
}

void afficheToken(_Token* token){
  int len;
  if(token->next != NULL){
    afficheToken(token->next);
  }
  if(token->node != 0){
    printf("[Tag]: _%s_\t[Valeur]: _[%.*s]_\n",getElementTag(token->node, &len), len, getElementValue(token->node, &len));
  }
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
