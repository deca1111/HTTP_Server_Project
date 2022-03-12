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

void afficheToken(_Token* token, char *name){
  int len;
  if(token != NULL){
    if(token->next != NULL){
      afficheToken(token->next, name);
    }
    if(token->node != NULL){
      printf("[Tag]: _%s_\t[Valeur]: _%.*s_\n",getElementTag(token->node, &len), len, getElementValue(token->node, &len));
    }
  }else{
    printf("Liste de token vide: l'arbre ne contient aucun <%s> \n", name);
  }
}

_Token *recursifSearchTree(Noeud *noeud, char *name, _Token* token, int* nb_token){

  char* tag = getElementTag(noeud, NULL);
  _Token* precedent = token;
  if(strcmp(tag,name) == 0){
    precedent = creerToken();
    precedent->next = token;
    token->node = (void*)noeud;
    *(nb_token) += 1;
  }

  if(noeud->fils != NULL){
    precedent = recursifSearchTree(noeud->fils, name, precedent, nb_token);
  }

  if(noeud->frere != NULL){
    precedent = recursifSearchTree(noeud->frere, name, precedent, nb_token);
  }

  return precedent;
}
