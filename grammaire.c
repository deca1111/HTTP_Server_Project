#include "grammaire.h"

#define false 0
#define true 1
/*

verifAbsolute_path non fini








*/
//absolute-path = 1* ( "/" segment )
int verifAbsolute_path(char* valeur, Noeud* pere, int index, int long_max){
  int fin = false
  int compteur = 0;
  int taille_mot = 0;
  Noeud* fils;
  Noeud* frere;
  Noeud* frere_2;

  fils = creerFils(pere);
  frere = fils;

  if(index>=long_max){
    return 0;
  }

  while(!fin){
    frere_2 = creerFrere(frere);
    frere_3 = creerFrere(frere_2);

    if(valeur[index+taille_mot] == "/"){
      if((res = verifSegment(valeur+taille_mot+res, frere_3, taille_mot+res, long_max))){
        taille_mot = taille_mot + res + res2;
        res = 0;
        compteur += 1;
        frere = frere_3;
      }else{
        fin = true;
      }
    }else{
      fin = true;
    }
  }





  //remplissage Noeud
  pere->tag = "absolute-path";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;
}

// ALPHA = %x41-5A / %x61-7A   ; A-Z / a-z
int verifALPHA(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot;

  if(index>=long_max){
    return 0;
  }

  if( ((*valeur < 91) && (*valeur > 64)) || ((*valeur > 96) && (*valeur < 123))){
    taille_mot = 1;//est un separateur
  }else{
    taille_mot = 0;//pas un separateur
    return taille_mot;
  }

  //remplissage Noeud
  pere->tag = "ALPHA";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;
}

// DIGIT = %x30-39  ; 0-9
int verifDIGIT(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot;

  if(index>=long_max){
    return 0;
  }
  if( ((*valeur < 58) && (*valeur > 47)) ){
    taille_mot = 1;//est un separateur
  }else{
    taille_mot = 0;//pas un separateur
    return taille_mot;
  }

  //remplissage Noeud
  noeud->tag = "DIGIT";
  noeud->valeur = valeur;
  noeud->longueur = taille_mot;


  return taille_mot;
}
