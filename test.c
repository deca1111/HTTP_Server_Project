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
  char* mot = "startcou_,COU-.fin\n";
  int index = 0;
  int taille_max = 5;


  _Token* premier_element;
  char* valeur;
  int res;
  Noeud* racine;

  valeur = &(mot[0]);
  racine = creerNoeud();


  printf("Debut du parseur\n");
  printf("Valeur = %s\n",valeur);
  //modifier cette ligne pour tester une fonction en particulier
  res = verifALPHA(valeur, racine, index, taille_max);

  printf("Mot de taille : %d\n", res);

  if(res){
    afficherArbre(racine);
  }

  premier_element = searchTree(racine, "ALPHA");
  afficheToken(premier_element);
  purgeTree(racine);
  purgeElement(&premier_element);




  return 0;
}
