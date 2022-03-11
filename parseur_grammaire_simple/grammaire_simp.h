#ifndef __GRAMMAIRE_SIMP_H__
#define __GRAMMAIRE_SIMP_H__

#include <stdio.h>
#include <stdlib.h>


#include "arbre.h"
#include "api.h"

#include "struct.h"
//Contient toutes le fonctions decrivant la grammaire :
//Une fonction par element

int verifMessage(char* valeur, Noeud* pere, int index, int len_max);

int verifDebut(char* valeur, Noeud* pere, int index, int len_max);

int verifMot(char* valeur, Noeud* pere, int index, int len_max);

int verifPonct(char* valeur, Noeud* pere, int index, int len_max);

int verifNombre(char* valeur, Noeud* pere, int index, int len_max);

int verifSeparateur(char* valeur, Noeud* noeud, int index, int len_max);

int verifFin(char* valeur, Noeud* pere, int index, int len_max);

int verifLF(char* valeur, Noeud* noeud, int index, int len_max);

int verifDIGIT(char* valeur, Noeud* noeud, int index, int len_max);

int verifALPHA(char* valeur, Noeud* noeud, int index, int len_max);

#endif
