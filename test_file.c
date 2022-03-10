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

#define MAX 200

int main(int argc, char const *argv[]) {
  //char* mot = "startCoucou ,je :taime\t.69_?fin\n";
  char mot[MAX];
  char* valeur;
  _Token* premier_element;
  int res;
  Noeud* racine;
  FILE * requete;



  if(argc<4){
    printf("Rentrez un fichier, une recherche et une taille pour parser\n");
    return 0;
  }

  requete = fopen(argv[1],"r");
  if(requete == NULL){
    printf("Erreur ouverture fichier\n");
    return 0;
  }
  fgets(mot, MAX, requete);
  racine = creerNoeud();
  valeur = &(mot[0]);


  printf("Debut du parseur\n");
  printf("Valeur = %s\n",valeur);
  res = verifMessage(valeur, racine);
  printf("Mot de taille : %d\n", res);
  if(res != atoi(argv[3])){
    printf("Erreur parser\n");
    purgeTree(racine);
    return 0;
  }

  if(res){
    afficherArbre(racine);
  }

  premier_element = searchTree(racine, argv[2]);
  afficheToken(premier_element);
  purgeElement(&premier_element);
  purgeTree(racine);




  return 0;
}
