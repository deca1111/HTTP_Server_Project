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
  /*unsigned char mot[100] = "a_";//A MODIFIER
  mot[0] = 204;*/
  char* mot = "100"; //A MODIFIER
  int index = 0;
  int taille_max = 100;
  char *name = "dec-octet";//A MODIFIER

  float fct_faite = 48;
  float fct_a_faire=79;
  int avancement = (fct_faite/fct_a_faire)*100 ;


  _Token* premier_element;
  char* valeur;
  int res = 0;
  Noeud* racine;

  valeur = &(mot[0]);
  racine = creerNoeud();

  printf("Debut du parseur\n");
  printf("Chaine a tester = _%s_\n",valeur);
  //modifier cette ligne pour tester une fonction en particulier
  res = verifDec_octet(valeur, racine, index, taille_max);//A MODIFIER

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
