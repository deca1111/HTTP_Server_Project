#ifndef GRAMMAIRE_SIMP_H
#define GRAMMAIRE_SIMP_H

#include <stdio.h>
#include <stdlib.h>

//Contient toutes le fonctions decrivant la grammaire :
//Une fonction par element

int verifMessage();

int verifDebut();

int verifMot(char* valeur, Noeud* pere);

int verifPonct();

int verifNombre();

int verifSeparateur(char* valeur, Noeud* noeud);

int verifFin();

int verifLF();

int verifDIGIT();

int verifALPHA(char* valeur, Noeud* noeud);

#endif
