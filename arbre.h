#ifndef __ARBRE_H__
#define __ARBRE_H__

#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "api.h"

//Contient les fonctions permettant de creer l'arbre ainsi que la structure de noeud

//Structure de noeud contentant le tag, la valeur et la longueur de la valeur
//Contient aussi des pointeurs vers des noeuds fils et frere


Noeud* creerNoeud();
Noeud* creerFils(Noeud* n);
Noeud* creerFrere(Noeud* n);

void setNoeud(Noeud* noeud_, char* tag_, char* valeur__, int longueur_);
void afficherArbre(Noeud* noeud);

//***--------Fonctions Utiles pour le bon fonctionnement des fonctions si dessus--------***

_Token* creerToken();

void afficheToken(_Token* token);

//noeud: noeud actuel
//name: tag recherche
//token: element a remplir de la liste chainee
//return: element suivant de la liste chainee
_Token *recursifSearchTree(Noeud *noeud, char *name, _Token* token);



#endif
