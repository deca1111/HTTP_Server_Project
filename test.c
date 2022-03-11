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
#include "grammaire.h"
#include "arbre.h"

int main(int argc, char const *argv[]) {
  //========parametre de la fonction a tester=========
  char* mot = "starttcou+_";
  int index = 0;
  int taille_max = 15;


  _Token* premier_element;
  char* valeur;
  int res;
  Noeud* racine;

  valeur = &(mot[0]);
  racine = creerNoeud();


  printf("Debut du parseur\n");
  printf("Valeur = %s\n",valeur);
  //modifier cette ligne pour tester une fonction en particulier
  res = verifToken(valeur, racine, index, taille_max);

  printf("Mot de taille : %d\n", res);

  if(res){
    premier_element = searchTree(racine, "tchar");
    afficheToken(premier_element);

    purgeElement(&premier_element);
  }

  purgeTree(racine);




  return 0;
}