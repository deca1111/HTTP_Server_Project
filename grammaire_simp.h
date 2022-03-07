#ifndef GRAMMAIRE_SIMP_H
#define GRAMMAIRE_SIMP_H

#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"
#include "api.h"
//Contient toutes le fonctions decrivant la grammaire :
//Une fonction par element

int verifMessage(char* valeur, Noeud* pere);

int verifDebut(char* valeur, Noeud* pere);

int verifMot(char* valeur, Noeud* pere);

int verifPonct(char* valeur, Noeud* pere);

int verifNombre(char* valeur, Noeud* pere);

int verifSeparateur(char* valeur, Noeud* noeud);

int verifFin(char* valeur, Noeud* noeud);

int verifLF(char* valeur, Noeud* noeud);

int verifDIGIT(char* valeur, Noeud* noeud);

int verifALPHA(char* valeur, Noeud* noeud);

#endif
