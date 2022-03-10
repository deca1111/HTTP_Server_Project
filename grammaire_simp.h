#ifndef __GRAMMAIRE_SIMP_H__
#define __GRAMMAIRE_SIMP_H__

#include <stdio.h>
#include <stdlib.h>


#include "arbre.h"
#include "api.h"

#include "struct.h"
//Contient toutes le fonctions decrivant la grammaire :
//Une fonction par element

int verifMessage(char* valeur, Noeud* pere);

int verifDebut(char* valeur, Noeud* pere);

int verifMot(char* valeur, Noeud* pere);

int verifPonct(char* valeur, Noeud* pere);

int verifNombre(char* valeur, Noeud* pere);

int verifSeparateur(char* valeur, Noeud* noeud);

int verifFin(char* valeur, Noeud* pere);

int verifLF(char* valeur, Noeud* noeud);

int verifDIGIT(char* valeur, Noeud* noeud);

int verifALPHA(char* valeur, Noeud* noeud);

#endif
