#include "grammaire.h"

#define false 0
#define true 1
/* base de chaque fonction:
//definition des variables
int taille_mot;

//verification de la taille de la requete
if(index>=long_max){
  return 0;
}
//code





//remplissage Noeud
pere->tag = "DIGIT";
pere->valeur = valeur;
pere->longueur = taille_mot;


//return taille_mot
return taille_mot;
*/

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
  pere->tag = "DIGIT";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;
}

//tchar = "!" / "#" / "$" / "%" / "&" / "'" / "*" / "+" / "-" / "." / "^" / "_" / "`" / "|" / "~" / DIGIT / ALPHA
int verifTchar(char* valeur, Noeud* pere, int index, int long_max){
  //definition des variables
  int taille_mot;
  int est_pere = false;
  Noeud* fils = creerFils(pere);
  //verification de la taille de la requete
  if(index>=long_max){
    return 0;
  }
  //code
  if(
    (*(valeur)=='!') ||
    (*(valeur)=='#') ||
    (*(valeur)=='$') ||
    (*(valeur)=='%') ||
    (*(valeur)=='&') ||
    (*(valeur)=='\'') ||
    (*(valeur)=='*') ||
    (*(valeur)=='+') ||
    (*(valeur)=='-') ||
    (*(valeur)=='.') ||
    (*(valeur)=='^') ||
    (*(valeur)=='_') ||
    (*(valeur)=='`') ||
    (*(valeur)=='|') ||
    (*(valeur)=='~'))
  {
    taille_mot = 1;
  }else if (
    verifALPHA(valeur, fils, index, long_max) ||
    verifDIGIT(valeur, fils, index, long_max))
  {
    taille_mot = 1;
    est_pere = true;
  }
  else{
    return 0;
  }

  if(!est_pere){
    free(fils);
    pere->fils = NULL;
  }
  //remplissage Noeud
  pere->tag = "tchar";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  //return taille_mot
  return taille_mot;
}

//token = 1* tchar
int verifToken(char* valeur, Noeud* pere, int index, int long_max){
  //definition des variables
  int taille_mot = 0;
  int fin = false;
  int compteur = 0;
  int res = 0;
  Noeud* fils = creerFils(pere);
  Noeud* frere = fils;
  Noeud* frere2 = fils;
  //verification de la taille de la requete
  if(index>=long_max){
    return 0;
  }
  //code
  while(!fin){
    if((res = verifTchar(valeur+taille_mot, frere2, index+taille_mot, long_max))){
      taille_mot += res;
      res = 0;
      frere = frere2;
      compteur += 1;
    }else{
      fin = true;
      frere->fils = NULL;
    }

  }
  if(compteur<1){
    purgeTree(fils);
    pere->fils = NULL;
    return 0;
  }else{
    free(frere2);
    frere->frere = NULL;
    frere->fils = NULL;

  }

  //remplissage Noeud
  pere->tag = "token";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  //return taille_mot
  return taille_mot;
}
