#include "arbre.h"
#include "api.h"

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
