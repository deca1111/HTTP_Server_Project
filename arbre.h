#ifndef ARBRE_H
#define ARBRE_H

#include <stdio.h>
#include <stdlib.h>


//Contient les fonctions permettant de creer l'arbre ainsi que la structure de noeud

//Structure de noeud contentant le tag, la valeur et la longueur de la valeur
//Contient aussi des pointeurs vers des noeuds fils et frere
typedef struct Noeud{
  char* tag;

  char* valeur;
  int longueur;
  int profondeur;

  struct Noeud* fils;
  struct Noeud* frere;

} Noeud;

Noeud* creerNoeud();
Noeud* creerFils(Noeud* n);
Noeud* creerFrere(Noeud* n);

void setNoeud(Noeud* noeud_, char* tag_, char* valeur__, int longueur_);




#endif
