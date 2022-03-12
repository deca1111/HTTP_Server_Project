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
  char* mot = "5132fezhibf";
  int index = 0;
  int taille_max = 15;
  char *name = "ALPHA";


  _Token* premier_element;
  char* valeur;
  int res;
  Noeud* racine;

  valeur = &(mot[0]);
  racine = creerNoeud();


  printf("Debut du parseur\n");
  printf("Chaine a tester = %s\n",valeur);
  //modifier cette ligne pour tester une fonction en particulier
  res = verifContent_length(valeur, racine, index, taille_max);

  printf("Mot de taille : %d\n", res);

  if(res){
    premier_element = searchTree(racine, name);
    //printf("%p,%p\n",premier_element->node,premier_element->next);
    afficheToken(premier_element, name);

    purgeElement(&premier_element);
  }

  purgeTree(racine);




  return 0;
}
