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
  char* mot = "startcou_,COU-.fin\n";
  _Token* premier_element;
  char* valeur;
  valeur = &(mot[0]);

  Noeud* racine;

  racine = creerNoeud();

  int res;
  printf("Debut du parseur\n");
  printf("Valeur = %s\n",valeur);
  res = verifMessage(valeur, racine, 0, 20);
  printf("Mot de taille : %d\n", res);

  if(res){
    afficherArbre(racine);
    premier_element = searchTree(racine, "ALPHA");
    afficheToken(premier_element);
    purgeTree(racine);
    purgeElement(&premier_element);
  }


  return 0;
}