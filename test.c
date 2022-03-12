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
  char* mot = "Fstarttcou+_";
  int index = 0;
  int taille_max = 15;


  _Token* premier_element;
  char* valeur;
  int res;
  Noeud* racine;

  valeur = &(mot[0]);
  racine = creerNoeud();


  printf("Debut du parseur\n");
<<<<<<< HEAD
  printf("Valeur = %s\n",valeur);

  //modifier cette ligne pour tester une fonction en particulier
  res = verifHEXDIG(valeur, racine, index, taille_max);
=======
  printf("Chaine a tester = %s\n",valeur);
  //modifier cette ligne pour tester une fonction en particulier
  res = verifUnreserved(valeur, racine, index, taille_max);
>>>>>>> de5a95e20b993fb6bc8b3e42011776b91b2eb783

  printf("Mot de taille : %d\n", res);

  if(res){
    premier_element = searchTree(racine, "unreserved");
    afficheToken(premier_element);
    afficherArbre(racine);
    purgeElement(&premier_element);
  }

  purgeTree(racine);




  return 0;
}
