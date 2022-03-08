#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>

#include "api.h"
#include "grammaire_simp.h"
#include "arbre.h"

int main(int argc, char const *argv[]) {
  //char* mot = "startCoucou ,je :taime\t.69_?fin\n";
  char* mot = "startO ,DCvWahPeh	.q .UC-,Ka-:itN	:fin\n";

  char* valeur;
  valeur = &(mot[0]);

  Noeud* racine;

  Noeud* racine2;
  racine = creerNoeud();

  int res;
  printf("Debut du parseur\n");
  printf("Valeur = %s\n",valeur);
  res = verifMessage(valeur, racine);
  printf("Mot de taille : %d\n", res);

  afficherArbre(racine);




  return 0;
}
