#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char const *argv[]) {

  char* mot = "arc-";

  char* valeur;
  valeur = &(mot[0]);

  Noeud* racine;

  racine = creerNoeud();

  int res;
  res = verifMot(valeur, racine);

  printf("Mot de taille : %d\n", res);
  return 0;
}
