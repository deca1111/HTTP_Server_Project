#include "grammaire_simp.h"

int verifMot(char* valeur, Noeud* pere){
  int taille_mot = 0;
  int res = 0;

  Noeud* fils;
  Noeud* frere;
  Noeud* petit_frere;

  fils = creerFils(pere);
  frere = fils;
  petit_frere = fils;

  //Tant que on a des ALPHA on continu a remplir des Noeud
  //a la dernière iteration qui fait sortir de la boucle, on aura deja un petit
  // frere de cree, il faut donc le free
  while((res = verifALPHA((valeur+taille_mot),petit_frere))) {
    taille_mot += res;
    res = 0;
    frere = petit_frere;
    petit_frere = creerFrere(frere);
  }
  free(petit_frere);

  //verif qu'il y a au moins 1 ALPHA
  if(taille_mot == 0){
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    return 0;//il y a un probleme
  }

  petit_frere = creerFrere(frere);
  //verif qu'il y a bien un separateur
  if((res = verifSeparateur((valeur+taille_mot),petit_frere))){
    taille_mot += res;
    res = 0;
  }else{
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    return 0;//il y a un probleme
  }

  //remplissage Noeud
  pere->tag = "mot";
  pere->valeur = valeur;
  pere->longueur = taille_mot;

  return taille_mot;
}

int verifSeparateur(char* valeur, Noeud* noeud){
  int taille_mot;

  if((*(valeur)==',') || (*(valeur)=='.') || (*(valeur)=='!') || (*(valeur)=='?') || (*(valeur)==':')){
    taille_mot = 1;//est un separateur
  }else{
    taille_mot = 0;//pas un separateur
  }

  //remplissage Noeud
  noeud->tag = "separateur";
  pere->valeur = valeur;
  pere->longueur = taille_mot;

  return taille_mot;
}
