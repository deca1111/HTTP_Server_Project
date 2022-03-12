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
  char* mot = "bs4525&95a!%4F";//A MODIFIER
  int index = 0;
  int taille_max = 15;
  char *name = "reg-name";//A MODIFIER

  float fct_faite = 23;
  float fct_a_faire=78;
  int avancement = (fct_faite/fct_a_faire)*100 ;


  _Token* premier_element;
  char* valeur;
  int res;
  Noeud* racine;

  valeur = &(mot[0]);
  racine = creerNoeud();

  printf("Debut du parseur\n");
  printf("Chaine a tester = _%s_\n",valeur);
  //modifier cette ligne pour tester une fonction en particulier
  res = verifReg_name(valeur, racine, index, taille_max);//A MODIFIER

  printf("Mot de taille : %d\n", res);

  afficherArbre(racine);

  if(res){
    premier_element = searchTree(racine, name);
    afficheToken(premier_element, name);

    purgeElement(&premier_element);
  }

  purgeTree(racine);

  printf("\nAvancement : %d %%\n",avancement);


  return 0;
}
