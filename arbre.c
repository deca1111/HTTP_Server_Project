#include "arbre.h"
#include "api.h"

Noeud* creerNoeud(){

  Noeud* new= (Noeud*) malloc(sizeof(Noeud));
  new.value = NULL;
  new.longueur = 0;
  new.frere = NULL;
  new.fils = NULL;

  return new ;
}

Noeud* creerFils(Noeud* n){
  Noeud* new = creerNoeud();
  n.fils = new;
  return new ;
}

Noeud* creerFrere(Noeud* n){
  Noeud* new = creerNoeud();
  n.frere = new ;
  return new ;
}

void setNoeud(Noeud* noeud_, char* tag_, char* value_, int longueur_){
  noeud_.tag = tag_ ;
  noeud_.value = value_ ;
  noeud_.longueur= longueur_ ;
}
