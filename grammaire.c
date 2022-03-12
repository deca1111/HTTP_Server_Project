#include "grammaire.h"

#define false 0
#define true 1

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

//HEXDIG  =  DIGIT / "A" / "B" / "C" / "D" / "E" / "F"
int verifHEXDIG(char* valeur, Noeud* pere, int index, int long_max){
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
    (*(valeur)=='A') ||
    (*(valeur)=='B') ||
    (*(valeur)=='C') ||
    (*(valeur)=='D') ||
    (*(valeur)=='E') ||
    (*(valeur)=='F'))
  {
    taille_mot = 1;
  }else if ((taille_mot = verifDIGIT(valeur, fils, index, long_max))){
    est_pere = true;
  }else{
    free(fils);
    pere->fils = NULL;
    return 0;
  }

  if(!est_pere){
    free(fils);
    pere->fils = NULL;
  }

  //remplissage Noeud
  pere->tag = "HEXDIG";
  pere->valeur = valeur;
  pere->longueur = taille_mot;

  //return taille_mot
  return taille_mot;
}

//SP =  %x20
int verifSP(char* valeur, Noeud* pere, int index, int long_max){
  //definition des variables
  int taille_mot = 0;

  //verification de la taille de la requete
  if(index>=long_max){
    return 0;
  }
  //code
  if(*(valeur)!=' '){
    return 0;
  }else{
    taille_mot = 1;
  }

  //remplissage Noeud
  pere->tag = "SP";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  //return taille_mot
  return taille_mot;
}


//unreserved = ALPHA / DIGIT / "-" / "." / "_" / "~"
int verifUnreserved(char* valeur, Noeud* pere, int index, int long_max){
  //definition des variables
  int taille_mot;
  int est_pere = false;

  //verification de la taille de la requete
  if(index>=long_max){
    return 0;
  }

  Noeud* fils = creerFils(pere);

  //code
  if(
    (*(valeur)=='-') ||
    (*(valeur)=='.') ||
    (*(valeur)=='_') ||
    (*(valeur)=='~'))
  {
    taille_mot = 1;
  }else if (
    (taille_mot = verifALPHA(valeur, fils, index, long_max)) ||
    (taille_mot = verifDIGIT(valeur, fils, index, long_max)))
  {
    est_pere = true;
  }else{
    free(fils);
    pere->fils = NULL;
    return 0;
  }

  if(!est_pere){
    free(fils);
    pere->fils = NULL;
  }
  //remplissage Noeud
  pere->tag = "unreserved";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  //return taille_mot
  return taille_mot;
}

//tchar = "!" / "#" / "$" / "%" / "&" / "'" / "*" / "+" / "-" / "." / "^" / "_" / "`" / "|" / "~" / DIGIT / ALPHA
int verifTchar(char* valeur, Noeud* pere, int index, int long_max){
  //definition des variables
  int taille_mot;
  int est_pere = false;

  //verification de la taille de la requete
  if(index>=long_max){
    return 0;
  }

  Noeud* fils = creerFils(pere);

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
    (taille_mot = verifALPHA(valeur, fils, index, long_max)) ||
    (taille_mot = verifDIGIT(valeur, fils, index, long_max)))
  {
    est_pere = true;
  }else{
    free(fils);
    pere->fils = NULL;
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
  int taille_mot = 0;
  int res = 0;
  Noeud* fils;
  Noeud* frere;
  Noeud* petit_frere;

  //verirication que l'on ne depasse pas la longueur à parser
  if(index >= long_max){
    return 0;
  }

  fils = creerFils(pere);
  frere = fils;
  petit_frere = fils;



  while((res = verifTchar((valeur+taille_mot),petit_frere, index+taille_mot, long_max))){
    taille_mot += res;
    res = 0;
    frere = petit_frere;
    petit_frere = creerFrere(frere);
  }


  //verif qu'il y a au moins 1 nombre
  if(taille_mot == 0){
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;//il y a un probleme
  }else{
    free(petit_frere);
    frere->frere = NULL;
  }


  //remplissage Noeud
  pere->tag = "token";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;
}

//type = token
int verifType(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot = 0;
  Noeud* fils;

  //verification de la taille de la requete
  if(index>=long_max){
    return 0;
  }

  fils = creerFils(pere);

  if( (taille_mot = verifToken(valeur+taille_mot, fils, index+taille_mot, long_max)) == 0){
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;//il y a un probleme
  }

  //remplissage Noeud
  pere->tag = "type";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  //return taille_mot
  return taille_mot;
}

//connection-option = token
int verifConnection_option(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot = 0;
  Noeud* fils;

  //verification de la taille de la requete
  if(index>=long_max){
    return 0;
  }

  fils = creerFils(pere);

  if( (taille_mot = verifToken(valeur+taille_mot, fils, index+taille_mot, long_max)) == 0){
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;//il y a un probleme
  }

  //remplissage Noeud
  pere->tag = "connection-option";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  //return taille_mot
  return taille_mot;
}

//cookie-name = token
int veriCookie_name(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot = 0;
  Noeud* fils;

  //verification de la taille de la requete
  if(index>=long_max){
    return 0;
  }

  fils = creerFils(pere);

  if( (taille_mot = verifToken(valeur+taille_mot, fils, index+taille_mot, long_max)) == 0){
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;//il y a un probleme
  }

  //remplissage Noeud
  pere->tag = "cookie-name";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  //return taille_mot
  return taille_mot;
}

//field-name = token
int verifField_name(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot = 0;
  Noeud* fils;

  //verification de la taille de la requete
  if(index>=long_max){
    return 0;
  }

  fils = creerFils(pere);

  if( (taille_mot = verifToken(valeur+taille_mot, fils, index+taille_mot, long_max)) == 0){
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;//il y a un probleme
  }

  //remplissage Noeud
  pere->tag = "field-name";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  //return taille_mot
  return taille_mot;
}

//method = token
int verifMethod(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot = 0;
  Noeud* fils;

  //verification de la taille de la requete
  if(index>=long_max){
    return 0;
  }

  fils = creerFils(pere);

  if( (taille_mot = verifToken(valeur+taille_mot, fils, index+taille_mot, long_max)) == 0){
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;//il y a un probleme
  }

  //remplissage Noeud
  pere->tag = "method";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  //return taille_mot
  return taille_mot;
}

//subtype = token
int verifSubtype(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot = 0;
  Noeud* fils;

  //verification de la taille de la requete
  if(index>=long_max){
    return 0;
  }

  fils = creerFils(pere);

  if( (taille_mot = verifToken(valeur+taille_mot, fils, index+taille_mot, long_max)) == 0){
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;//il y a un probleme
  }

  //remplissage Noeud
  pere->tag = "subtype";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  //return taille_mot
  return taille_mot;
}

//Content-Length = 1* DIGIT
int verifContent_length(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot = 0;
  int res = 0;
  Noeud* fils;
  Noeud* frere;
  Noeud* petit_frere;

  //verirication que l'on ne depasse pas la longueur à parser
  if(index >= long_max){
    return 0;
  }

  fils = creerFils(pere);
  frere = fils;
  petit_frere = fils;

  while((res = verifDIGIT((valeur+taille_mot),petit_frere, index+taille_mot, long_max))){
    taille_mot += res;
    res = 0;
    frere = petit_frere;
    petit_frere = creerFrere(frere);
  }


  //verif qu'il y a au moins 1 nombre
  if(taille_mot == 0){
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;//il y a un probleme
  }else{
    free(petit_frere);
    frere->frere = NULL;
  }


  //remplissage Noeud
  pere->tag = "Content-Length";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;
}

//port = * DIGIT
int verifPort(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot = 0;
  int res = 0;
  Noeud* fils;
  Noeud* frere;
  Noeud* petit_frere;

  //verirication que l'on ne depasse pas la longueur à parser
  if(index >= long_max){
    return 0;
  }

  fils = creerFils(pere);
  frere = fils;
  petit_frere = fils;



  while((res = verifDIGIT((valeur+taille_mot),petit_frere, index+taille_mot, long_max))){
    taille_mot += res;
    res = 0;
    frere = petit_frere;
    petit_frere = creerFrere(frere);
  }


  //verif qu'il y a au moins 1 nombre
  if(taille_mot > 0){
    free(petit_frere);
    frere->frere = NULL;
  }


  //remplissage Noeud
  pere->tag = "port";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;

}


//status-code = 3 DIGIT
int verifStatus_code(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot = 0;
  int res = 0;
  Noeud* fils;
  Noeud* frere;
  Noeud* petit_frere;

  //verirication que l'on ne depasse pas la longueur à parser
  if(index >= long_max){
    return 0;
  }

  fils = creerFils(pere);
  frere = fils;
  petit_frere = fils;



  while((res = verifDIGIT((valeur+taille_mot),petit_frere, index+taille_mot, long_max))){
    taille_mot += res;
    res = 0;
    frere = petit_frere;
    petit_frere = creerFrere(frere);
  }


  //verif qu'il y a 3 digits
  if(taille_mot != 3){
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;//il y a un probleme
  }else{
    free(petit_frere);
    frere->frere = NULL;
  }


  //remplissage Noeud
  pere->tag = "status-code";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;
}

//h16 = 1*4 HEXDIG
int verifH16(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot = 0;
  int res = 0;
  int compteur = 0;
  int fin = 0;
  int taille_bloc = 0;
  Noeud* fils;
  Noeud* frere;
  Noeud* petit_frere;
  Noeud* frere_debut_bloc;
  Noeud* grand_frere_debut_bloc;

  //verirication que l'on ne depasse pas la longueur à parser
  if(index >= long_max){
    return 0;
  }

  fils = creerFils(pere);
  frere = fils;
  petit_frere = fils;
  frere_debut_bloc = fils;

  //on verifie d'abord le premier bloc obligatoire
  while((compteur < 4 ) && (res = verifHEXDIG((valeur+taille_mot+taille_bloc),petit_frere, index+taille_mot+taille_bloc, long_max))){
    compteur += 1;
    taille_bloc += res;
    res = 0;
    frere = petit_frere;
    petit_frere = creerFrere(frere);
  }
  if(compteur !=4){
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;
  }else{
    compteur = 0;
    taille_mot += taille_bloc ;
    taille_bloc =0;
    frere_debut_bloc = petit_frere ;
    grand_frere_debut_bloc = frere ;

  }

  //on verifie les blocs optionels
  while (!fin) {
    while((compteur < 4 ) && (res = verifHEXDIG((valeur+taille_mot+taille_bloc),petit_frere, index+taille_mot+taille_bloc, long_max))){
      compteur += 1;
      taille_bloc += res;
      res = 0;
      frere = petit_frere;
      petit_frere = creerFrere(frere);
    }

    if(compteur !=4){
      purgeTree(frere_debut_bloc);//on detruit tous les noeuds eventuelement crées avant
      grand_frere_debut_bloc->frere = NULL;
      fin = 1;
    }else{
      compteur = 0;
      taille_mot += taille_bloc ;
      taille_bloc =0;
      frere_debut_bloc = petit_frere ;
      grand_frere_debut_bloc = frere ;
    }

  }

  //remplissage Noeud
  pere->tag = "h16";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;
}

//pct-encoded = "%" HEXDIG HEXDIG
int verifPct_encoded(char* valeur, Noeud* pere, int index, int long_max){
  //definition des variables
  int taille_mot;
  int res;

  //verification de la taille de la requete
  if(index>=long_max){
    return 0;
  }

  if(*(valeur)=='%'){
    taille_mot = 1;
  }else{
    return 0;
  }

  Noeud* fils = creerFils(pere);

  if((res = verifHEXDIG(valeur+taille_mot,fils,index+taille_mot,long_max))){
    taille_mot+=res;
  }else{
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;//il y a un probleme
  }

  Noeud* frere = creerFrere(fils);

  if((res = verifHEXDIG(valeur+taille_mot,frere,index+taille_mot,long_max))){
    taille_mot+=res;
  }else{
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;//il y a un probleme
  }

  //remplissage Noeud
  pere->tag = "pct-encoded";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;
}

//sub-delims = "!" / "$" / "&" / "'" / "(" / ")" / "*" / "+" / "," / ";" / "="
int verifSub_delims(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot;

  if(index>=long_max){
    return 0;
  }

  if( (*valeur == '!') ||
  (*valeur == '$') ||
  (*valeur == '&') ||
  (*valeur == 39) ||
  (*valeur == '(') ||
  (*valeur == ')') ||
  (*valeur == '*') ||
  (*valeur == '+') ||
  (*valeur == ',') ||
  (*valeur == ';') ||
  (*valeur == '=')
      ){
    taille_mot = 1;//est un separateur
  }else{
    taille_mot = 0;//pas un separateur
  }

  //remplissage Noeud
  pere->tag = "sub-delims";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;
}
