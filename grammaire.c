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

  //verification de la taille de la requete
  if(index>=long_max){
    return 0;
  }

	Noeud* fils = creerFils(pere);

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
int verifCookie_name(char* valeur, Noeud* pere, int index, int long_max){
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
  }else{
    free(fils);
    pere->fils = NULL;
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

//pchar = unreserved / pct-encoded / sub-delims / ":" / "@"
int verifPchar(char* valeur, Noeud* pere, int index, int long_max){
  //definition des variables
  int taille_mot;

  //verification de la taille de la requete
  if(index>=long_max){
    return 0;
  }

  Noeud* fils = creerFils(pere);

  //code
  if((*(valeur)==':') ||
    (*(valeur)=='@'))
  {
    taille_mot = 1;
    free(fils);
    pere->fils = NULL;
  }else if (
    (taille_mot = verifUnreserved(valeur, fils, index, long_max)) ||
    (taille_mot = verifPct_encoded(valeur, fils, index, long_max)) ||
    (taille_mot = verifSub_delims(valeur, fils, index, long_max))
  )  {
  }else{
    free(fils);
    pere->fils = NULL;
    return 0;
  }


  //remplissage Noeud
  pere->tag = "pchar";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  //return taille_mot
  return taille_mot;
}

//reg-name = * ( unreserved / pct-encoded / sub-delims )
int verifReg_name(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot = 0;
  int res = 0;
  int fin = 0;
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

  while(!fin){
    if((res = verifUnreserved((valeur+taille_mot),petit_frere, index+taille_mot, long_max))){
      taille_mot += res;
      res = 0;
      frere = petit_frere;
      petit_frere = creerFrere(frere);
    }else if((res = verifPct_encoded((valeur+taille_mot),petit_frere, index+taille_mot, long_max))){
      taille_mot += res;
      res = 0;
      frere = petit_frere;
      petit_frere = creerFrere(frere);
    }else if((res = verifSub_delims((valeur+taille_mot),petit_frere, index+taille_mot, long_max))){
      taille_mot += res;
      res = 0;
      frere = petit_frere;
      petit_frere = creerFrere(frere);
    }else{
      fin = 1;
    }
  }

  if(taille_mot > 0){
    free(petit_frere);
    frere->frere = NULL;
  }else{
    free(fils);
    pere->fils = NULL;
  }


  //remplissage Noeud
  pere->tag = "reg-name";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;
}

//HTAB = %x09
int verifHTAB(char* valeur, Noeud* pere, int index, int long_max){
  //definition des variables
  int taille_mot = 0;

  //verification de la taille de la requete
  if(index>=long_max){
    return 0;
  }
  //code
  if(*(valeur)!=9){
    return 0;
  }else{
    taille_mot = 1;
  }

  //remplissage Noeud
  pere->tag = "HTAB";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  //return taille_mot
  return taille_mot;
}

//CRLF = %x0D %x0A
int verifCRLF(char* valeur, Noeud* pere, int index, int long_max){
  //definition des variables
  int taille_mot = 0;

  //verification de la taille de la requete
  if(index>=long_max){
    return 0;
  }

  if(*(valeur)==13){
    taille_mot += 1;
  }else{
    return 0;
  }

  if(*(valeur+taille_mot)==10){
    taille_mot+=1;
  }else{
    return 0;
  }

  //remplissage Noeud
  pere->tag = "CRLF";
  pere->valeur = valeur;
  pere->longueur = taille_mot;

  return taille_mot;
}

//obs-fold = CRLF 1* ( SP / HTAB )
int verifObs_fold(char* valeur, Noeud* pere, int index, int long_max){
  //definition des variables
  int taille_mot = 0;
  int res = 0;
  int fin = 0;
  Noeud* fils;
  Noeud* frere;
  Noeud* petit_frere;

  //verification de la taille de la requete
  if(index>=long_max){
    return 0;
  }

  fils = creerFils(pere);


  //code
  if ((res = verifCRLF(valeur+taille_mot,fils,index+taille_mot,long_max))){
    taille_mot+=res;
    res = 0;
  } else {
    purgeTree (fils);
    pere -> fils = NULL;
    return 0;
  }

  frere = fils;
  petit_frere = creerFrere(frere);

  //on verifie d'abord le premier bloc obligatoire
  if ((res = verifSP(valeur+taille_mot,petit_frere,index+taille_mot,long_max))){
    taille_mot+=res;
    res = 0 ;
    frere = petit_frere;
    petit_frere = creerFrere(frere);
  } else if ((res = verifHTAB(valeur+taille_mot,petit_frere,index+taille_mot,long_max))){
    taille_mot+=res;
    res = 0;
    frere = petit_frere;
    petit_frere = creerFrere(frere);
  } else {
    purgeTree(fils);
    pere -> fils = NULL;
    return 0 ;
  }

  while (!fin){
    if ((res = verifSP(valeur+taille_mot,petit_frere,index+taille_mot,long_max))){
      taille_mot+=res;
      res = 0 ;
      frere = petit_frere;
      petit_frere = creerFrere(frere);
    } else if ((res = verifHTAB(valeur+taille_mot,petit_frere,index+taille_mot,long_max))){
      taille_mot+=res;
      res = 0;
      frere = petit_frere;
      petit_frere = creerFrere(frere);
    } else {
      free (petit_frere);
      frere -> frere = NULL;
      fin = 1;
    }
  }

  //remplissage Noeud
  pere->tag = "obs-fold";
  pere->valeur = valeur;
  pere->longueur = taille_mot;

  return taille_mot;

}

//IPvFuture = "v" 1* HEXDIG "." 1* ( unreserved / sub-delims / ":" )
int verifIPvFuture(char* valeur, Noeud* pere, int index, int long_max){
  //definition des variables
  int taille_mot = 0;
  int res = 0;
  int fin = 0;
  Noeud* fils;
  Noeud* frere;
  Noeud* petit_frere;

  //verification de la taille de la requete
  if(index>=long_max){
    return 0;
  }

  if(*(valeur)=='v'){
    taille_mot = 1;
  }else{
    return 0;
  }

  fils = creerFils(pere);
  frere = fils;
  petit_frere = fils;

  while((res = verifHEXDIG((valeur+taille_mot),petit_frere, index+taille_mot, long_max))){
    taille_mot += res;
    res = 0;
    frere = petit_frere;
    petit_frere = creerFrere(frere);
  }


  //verif qu'il y a au moins 1 HEXDIG
  if(taille_mot == 1){
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;//il y a un probleme
  }else{
    free(petit_frere);
    frere->frere = NULL;
  }

  if(*(valeur+taille_mot)=='.'){
    taille_mot += 1;
  }else{
    return 0;
  }

  petit_frere = creerFrere(frere);

  //on verifie d'abord le premier bloc obligatoire
  if ((res = verifUnreserved(valeur+taille_mot,petit_frere,index+taille_mot,long_max))){
    taille_mot+=res;
    res = 0 ;
    frere = petit_frere;
    petit_frere = creerFrere(frere);
  } else if ((res = verifSub_delims(valeur+taille_mot,petit_frere,index+taille_mot,long_max))){
    taille_mot+=res;
    res = 0;
    frere = petit_frere;
    petit_frere = creerFrere(frere);
  }else if (*(valeur+taille_mot) == ':'){
    taille_mot+=1;
  } else {
    purgeTree(fils);
    pere -> fils = NULL;
    return 0 ;
  }

  while (!fin){
    if ((res = verifUnreserved(valeur+taille_mot,petit_frere,index+taille_mot,long_max))){
      taille_mot+=res;
      res = 0 ;
      frere = petit_frere;
      petit_frere = creerFrere(frere);
    } else if ((res = verifSub_delims(valeur+taille_mot,petit_frere,index+taille_mot,long_max))){
      taille_mot+=res;
      res = 0;
      frere = petit_frere;
      petit_frere = creerFrere(frere);
    }else if (*(valeur+taille_mot) == ':'){
      taille_mot+=1;
    } else {
      free (petit_frere);
      frere -> frere = NULL;
      fin = 1;
    }
  }

  //remplissage Noeud
  pere->tag = "IPvFuture";
  pere->valeur = valeur;
  pere->longueur = taille_mot;

  return taille_mot;

}

//segment = * pchar
int verifSegment(char* valeur, Noeud* pere, int index, int long_max){
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

  while((res = verifPchar((valeur+taille_mot),petit_frere, index+taille_mot, long_max))){
    taille_mot += res;
    res = 0;
    frere = petit_frere;
    petit_frere = creerFrere(frere);
  }

  //verif qu'il y a au moins 1 nombre
  if(taille_mot > 0){
    free(petit_frere);
    frere->frere = NULL;
  }else{
    free(fils);
    pere->fils = NULL;
  }


  //remplissage Noeud
  pere->tag = "segment";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;

}

//absolute-path = 1* ( "/" segment )
int verifAbsolute_path(char* valeur, Noeud* pere, int index, int long_max){
  //definition des variables
  int taille_mot = 0;
  int res = 0;
  int fin = 0;
  Noeud* fils;
  Noeud* frere;
  Noeud* petit_frere;

  //verification de la taille de la requete
  if(index>=long_max){
    return 0;
  }

  fils = creerFils(pere);
  frere = fils;
  petit_frere = fils;

  //on verifie d'abord le premier bloc obligatoire
  if (*(valeur+taille_mot) == '/'){
    taille_mot+=1;
    res = verifSegment(valeur+taille_mot,petit_frere,index+taille_mot,long_max);//segment peut etre vide donc pas de if
    taille_mot+=res;
    res = 0 ;
    frere = petit_frere;
    petit_frere = creerFrere(frere);
  } else {
    purgeTree(fils);
    pere -> fils = NULL;
    return 0 ;
  }

  int taille_bloc = 0;

  while (!fin){
    if (*(valeur+taille_mot) == '/'){
      taille_bloc+=1;
      res = verifSegment(valeur+taille_mot+taille_bloc,petit_frere,index+taille_mot+taille_bloc,long_max);//segment peut etre vide donc pas de if
      taille_bloc+=res;
      res = 0 ;
      frere = petit_frere;
      petit_frere = creerFrere(frere);
      taille_mot += taille_bloc;
      taille_bloc = 0;
    } else {
      free (petit_frere);
      frere -> frere = NULL;
      fin = 1;
    }
  }

  //remplissage Noeud
  pere->tag = "absolute-path";
  pere->valeur = valeur;
  pere->longueur = taille_mot;

  return taille_mot;

}

//query = * ( pchar / "/" / "?" )
int verifQuery(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot = 0;
  int res = 0;
  int fin = 0;
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

  while(!fin){
    if(*(valeur+taille_mot) == '/'){
      taille_mot += 1;
    }else if(*(valeur+taille_mot) == '?'){
      taille_mot += 1;
    }else if((res = verifPchar((valeur+taille_mot),petit_frere, index+taille_mot, long_max))){
      taille_mot += res;
      res = 0;
      frere = petit_frere;
      petit_frere = creerFrere(frere);
    }else{
      fin = 1;
    }
  }

  if(taille_mot > 0){
    free(petit_frere);
    frere->frere = NULL;
  }else{
    free(fils);
    pere->fils = NULL;
  }


  //remplissage Noeud
  pere->tag = "query";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;
}

//origin-form = absolute-path [ "?" query ]
int verifOrigin_form(char* valeur, Noeud* pere, int index, int long_max){
  //definition des variables
  int taille_mot = 0;
  int res = 0;

  //verification de la taille de la requete
  if(index>=long_max){
    return 0;
  }

  Noeud* fils = creerFils(pere);

  if ((res = verifAbsolute_path(valeur+taille_mot,fils,index+taille_mot,long_max))){
    taille_mot+=res;
    res = 0;
  } else {
    purgeTree (fils);
    pere -> fils = NULL;
    return 0;
  }

  int taille_bloc = 0;
  if(*(valeur+taille_mot) == '?'){
    taille_bloc += 1;
    Noeud* frere = creerFrere(fils);
    res = verifQuery(valeur+taille_mot+taille_bloc,frere,index+taille_mot+taille_bloc,long_max);//query peut etre de longueur null attention pas de if
    taille_bloc+=res;
    taille_mot += taille_bloc;
  }



  //remplissage Noeud
  pere->tag = "origin-form";
  pere->valeur = valeur;
  pere->longueur = taille_mot;

  return taille_mot;

}

//OWS = * ( SP / HTAB )
int verifOWS(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot = 0;
  int res = 0;
  int fin = 0;
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

  while(!fin){
    if((res = verifSP((valeur+taille_mot),petit_frere, index+taille_mot, long_max))){
      taille_mot += res;
      res = 0;
      frere = petit_frere;
      petit_frere = creerFrere(frere);
    }else if((res = verifHTAB((valeur+taille_mot),petit_frere, index+taille_mot, long_max))){
      taille_mot += res;
      res = 0;
      frere = petit_frere;
      petit_frere = creerFrere(frere);
    }else{
      fin = 1;
    }
  }

  if(taille_mot > 0){
    free(petit_frere);
    frere->frere = NULL;
  }else{
    free(fils);
    pere->fils = NULL;
  }


  //remplissage Noeud
  pere->tag = "OWS";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;

}

//VCHAR = %x21-7E
int verifVCHAR(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot;

  if(index>=long_max){
    return 0;
  }

  if( (*valeur < 127) && (*valeur > 32)) {
    taille_mot = 1;
  }else{
    taille_mot = 0;
  }

  //remplissage Noeud
  pere->tag = "VCHAR";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;
}

//cookie-octet = %x21 / %x23-2B / %x2D-3A / %x3C-5B / %x5D-7E
int verifCookie_octet(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot;

  if(index>=long_max){
    return 0;
  }

  if( (*valeur == 33) || ((*valeur >34 ) && (*valeur < 44)) || ((*valeur > 44) && (*valeur < 59)) || ((*valeur > 59 ) && (*valeur < 92 )) || ((*valeur > 92) && (*valeur < 127 ))){
    taille_mot = 1;
  }else{
    taille_mot = 0;
  }

  //remplissage Noeud
  pere->tag = "cookie-octet";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;
}

//DQUOTE%x22
int verifDQUOTE(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot;

  if(index>=long_max){
    return 0;
  }

  if (*valeur == 34) {
    taille_mot = 1;
  }else{
    taille_mot = 0;
  }

  //remplissage Noeud
  pere->tag = "DQUOTE";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;
}

//Expect = "100-continue"
int verifExpect(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot;
  int est_juste = 1;
  char* expect = "100-continue" ;

  if(index>=long_max){
    return 0;
  }

  for (int i = 0; i < 12; i++) {
    if (*(valeur+i) != expect[i]) {
      est_juste = 0;
    }
  }
  if (est_juste) {
    taille_mot = 12;
  }else{
    taille_mot = 0;
  }

  //remplissage Noeud
  pere->tag = "Expect";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;
}

//BWS = OWS
int verifBWS(char* valeur, Noeud* pere, int index, int long_max){

  int taille_mot = 0;
  Noeud* fils;

  //verification de la taille de la requete
  if(index>=long_max){
    return 0;
  }

  fils = creerFils(pere);

  taille_mot = verifOWS(valeur+taille_mot, fils, index+taille_mot, long_max); //OWS peut être nul donc pas de if

  //remplissage Noeud
  pere->tag = "BWS";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  //return taille_mot
  return taille_mot;
}

//HTTP-name = %x48.54.54.50
int verifHTTP_name(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot;
  int est_juste = 1;
  char* expect = "HTTP" ;

  if(index>=long_max){
    return 0;
  }

  for (int i = 0; i < 4; i++) {
    if (*(valeur+i) != expect[i]) {
      est_juste = 0;
    }
  }
  if (est_juste) {
    taille_mot = 4;
  }else{
    taille_mot = 0;
  }

  //remplissage Noeud
  pere->tag = "HTTP-name";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;
}

//HTTP-version = HTTP-name "/" DIGIT "." DIGIT
int verifHTTP_version(char* valeur, Noeud* pere, int index, int long_max){
  //definition des variables
  int taille_mot=0;
  int res;

  //verification de la taille de la requete
  if(index>=long_max){
    return 0;
  }

	Noeud* fils = creerFils(pere);

	if((res = verifHTTP_name(valeur+taille_mot,fils,index+taille_mot,long_max))){
    taille_mot+=res;
  }else{
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;//il y a un probleme
  }

  if(*(valeur+taille_mot)=='/'){
    taille_mot += 1;
  }else{
    purgeTree(fils);
    pere -> fils =NULL;
    return 0;
  }

  Noeud* frere = creerFrere(fils);

  if((res = verifDIGIT(valeur+taille_mot,frere,index+taille_mot,long_max))){
    taille_mot+=res;
  }else {
    purgeTree(fils);
    pere -> fils =NULL;
    return 0;
  }

  if(*(valeur+taille_mot)=='.'){
    taille_mot += 1;
  }else{
    purgeTree(fils);
    pere -> fils =NULL;
    return 0;
  }

  Noeud* petit_frere = creerFrere(frere);

  if((res = verifDIGIT(valeur+taille_mot,petit_frere,index+taille_mot,long_max))){
    taille_mot+=res;
  }else {
    purgeTree(fils);
    pere -> fils = NULL ;
    return 0;
  }

  //remplissage Noeud
  pere->tag = "HTTP-version";
  pere->valeur = valeur;
  pere->longueur = taille_mot;

  return taille_mot;
}

//request-target = origin-form
int verifRequest_target(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot = 0;
  Noeud* fils;

  //verification de la taille de la requete
  if(index>=long_max){
    return 0;
  }

  fils = creerFils(pere);

  if( (taille_mot = verifOrigin_form(valeur+taille_mot, fils, index+taille_mot, long_max)) == 0){
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;//il y a un probleme
  }

  //remplissage Noeud
  pere->tag = "request-target";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  //return taille_mot
  return taille_mot;
}

//request-line = method SP request-target SP HTTP-version CRLF
int verifRequest_line(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot=0;
  int res;

  //verification de la taille de la requete
  if(index>=long_max){
    return 0;
  }

  //method
  Noeud* fils = creerFils(pere);
  if((res = verifMethod(valeur+taille_mot,fils,index+taille_mot,long_max))){
    taille_mot+=res;
  }else{
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;//il y a un probleme
  }

  //SP
  Noeud* frere = creerFrere(fils);
  if((res = verifSP(valeur+taille_mot,frere,index+taille_mot,long_max))){
    taille_mot+=res;
  }else{
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;//il y a un probleme
  }

  //request-target
  Noeud* petit_frere = creerFrere(frere);
  if((res = verifRequest_target(valeur+taille_mot,petit_frere,index+taille_mot,long_max))){
    taille_mot+=res;
  }else{
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;//il y a un probleme
  }

  //SP
  frere = petit_frere;
  petit_frere = creerFrere(frere);
  if((res = verifSP(valeur+taille_mot,petit_frere,index+taille_mot,long_max))){
    taille_mot+=res;
  }else{
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;//il y a un probleme
  }

  //HTTP-version
  frere = petit_frere;
  petit_frere = creerFrere(frere);
  if((res = verifHTTP_version(valeur+taille_mot,petit_frere,index+taille_mot,long_max))){
    taille_mot+=res;
  }else{
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;//il y a un probleme
  }

  //CRLF
  frere = petit_frere;
  petit_frere = creerFrere(frere);
  if((res = verifCRLF(valeur+taille_mot,petit_frere,index+taille_mot,long_max))){
    taille_mot+=res;
  }else{
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;//il y a un probleme
  }


  //remplissage Noeud
  pere->tag = "request-line";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  //return taille_mot
  return taille_mot;
}

//A REVIEW
// obs-text = %x80-FF
int verifObs_text(char* valeur, Noeud* pere, int index, int long_max){
  /*int taille_mot;

  if(index>=long_max){
    return 0;
  }
  if( ((*valeur <= 255) && (*valeur > 127)) ){
    taille_mot = 1;//est un separateur
  }else{
    taille_mot = 0;//pas un separateur
    return taille_mot;
  }

  //remplissage Noeud
  pere->tag = "obs-text";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;*/
  return 0;
}

//Connection = * ( "," OWS ) connection-option * ( OWS "," [ OWS connection-option ] )
int verifConnection(char* valeur, Noeud* pere, int index, int long_max){
  //definition des variables
  int taille_mot = 0;
  int res = 0;
  int fin = 0;
  Noeud* fils;
  Noeud* frere;
  Noeud* petit_frere;

  //verification de la taille de la requete
  if(index>=long_max){
    return 0;
  }

  int taille_bloc = 0;
  fils = creerFils(pere);
  frere = fils;
  petit_frere = fils;

  //* ( "," OWS )
  while (!fin){
    if (*(valeur+taille_mot) == ','){
      taille_bloc+=1;
      res = verifOWS(valeur+taille_mot+taille_bloc,petit_frere,index+taille_mot+taille_bloc,long_max);//segment peut etre vide donc pas de if
      taille_bloc+=res;
      res = 0 ;
      frere = petit_frere;
      petit_frere = creerFrere(frere);
      taille_mot += taille_bloc;
      taille_bloc = 0;
    } else {
      fin = 1;
    }
  }

  //connection-option
  if((res = verifConnection_option(valeur+taille_mot,petit_frere,index+taille_mot,long_max))){
    taille_mot+=res;
  }else{
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;//il y a un probleme
  }

  taille_bloc = 0;
  int taille_option = 0;
  fin = 0;

    Noeud* frere_debut_bloc;
    Noeud* gd_frere_debut_bloc;
    Noeud* frere_debut_option;
    Noeud* gd_frere_debut_option;

  //* ( OWS "," [ OWS connection-option ] )
  while (!fin){

    frere = petit_frere;
    petit_frere = creerFrere(frere);

    frere_debut_bloc = petit_frere;
    gd_frere_debut_bloc = frere;

    res = verifOWS(valeur+taille_mot+taille_bloc,petit_frere,index+taille_mot+taille_bloc,long_max);//segment peut etre vide donc pas de if
    taille_bloc+=res;
    res = 0 ;
    if (*(valeur+taille_mot+taille_bloc) == ','){
      taille_bloc+=1;

      frere = petit_frere;
      petit_frere = creerFrere(frere);
      frere_debut_option = petit_frere;
      gd_frere_debut_option = frere;

      res = verifOWS(valeur+taille_mot+taille_bloc+taille_option,petit_frere,index+taille_mot+taille_bloc+taille_option,long_max);//segment peut etre vide donc pas de if
      taille_option += res;
      res = 0 ;
      frere = petit_frere;
      petit_frere = creerFrere(frere);
      if((res = verifConnection_option(valeur+taille_mot+taille_bloc+taille_option,petit_frere,index+taille_mot+taille_bloc+taille_option,long_max))){
        taille_option += res;
        res = 0;
        taille_bloc += taille_option;

      }else{
        purgeTree(frere_debut_option);
        gd_frere_debut_option->frere = NULL;
        petit_frere = gd_frere_debut_option;
      }
      taille_option = 0;

      taille_mot += taille_bloc;
    } else {
      purgeTree(frere_debut_bloc);
      gd_frere_debut_bloc->frere = NULL;
      fin = 1;
    }
    taille_bloc = 0;
  }

  //remplissage Noeud
  pere->tag = "Connection";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  //return taille_mot
  return taille_mot;

}

//Connection-header = "Connection" ":" OWS Connection OWS
int verifConnection_header(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot = 0;
  int est_juste = 1;
  int res;
  char* expect = "Connection:" ;

  if(index>=long_max){
    return 0;
  }

  for (int i = 0; i < 11; i++) {
    if (*(valeur+i) != expect[i]) {
      est_juste = 0;
    }
  }
  if (est_juste) {
    taille_mot = 11;
  }else{
    return 0;
  }


  Noeud* fils = creerFils(pere);
  res = verifOWS(valeur+taille_mot,fils,index+taille_mot,long_max);
  taille_mot += res;

  Noeud* frere = creerFrere(fils);
  if((res = verifConnection(valeur+taille_mot,frere,index+taille_mot,long_max))){
    taille_mot+=res;
  }else{
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;//il y a un probleme
  }

  frere = creerFrere(frere);
  res = verifOWS(valeur+taille_mot,frere,index+taille_mot,long_max);
  taille_mot += res;

  //remplissage Noeud
  pere->tag = "Connection-header";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;
}

//Content-Length-header = "Content-Length" ":" OWS Content-Length OWS
int verifContent_length_header(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot = 0;
  int est_juste = 1;
  int res;
  char* expect = "Content-Length:" ;

  if(index>=long_max){
    return 0;
  }

  for (int i = 0; i < 15; i++) {
    if (*(valeur+i) != expect[i]) {
      est_juste = 0;
    }
  }
  if (est_juste) {
    taille_mot = 15;
  }else{
    return 0;
  }

  Noeud* fils = creerFils(pere);
  res = verifOWS(valeur+taille_mot,fils,index+taille_mot,long_max);
  taille_mot += res;

  Noeud* frere = creerFrere(fils);
  if((res = verifContent_length(valeur+taille_mot,frere,index+taille_mot,long_max))){
    taille_mot+=res;
  }else{
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;//il y a un probleme
  }

  frere = creerFrere(frere);
  res = verifOWS(valeur+taille_mot,frere,index+taille_mot,long_max);
  taille_mot += res;

  //remplissage Noeud
  pere->tag = "Content-Length-header";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;
}

//cookie-value = ( DQUOTE * cookie-octet DQUOTE ) / * cookie-octet
int verifCookie_value(char* valeur, Noeud* pere, int index, int long_max){
	//definition des variables
	int taille_mot = 0;
	int res = 0;
	Noeud* fils;
	Noeud* frere;
	Noeud* petit_frere;

	//verification de la taille de la requete
	if(index>=long_max){
		return 0;
	}

	fils = creerFils(pere);
	frere = fils;
	petit_frere = fils;

	//verif ( DQUOTE * cookie-octet DQUOTE )
	if((res = verifDQUOTE(valeur+taille_mot,fils,index+taille_mot,long_max))){
		taille_mot+= res;
		res = 0;

		//verif * cookie-octet
	  frere = fils;
	  petit_frere = creerFrere(frere);

	  while((res = verifCookie_octet(valeur+taille_mot,petit_frere, index+taille_mot, long_max))){
	    taille_mot += res;
	    res = 0;
	    frere = petit_frere;
	    petit_frere = creerFrere(frere);
	  }

		//verif DQUOTE
		if((res = verifDQUOTE(valeur+taille_mot,petit_frere,index+taille_mot,long_max))){
			taille_mot+= res;
			res = 0;
		}else{
			purgeTree(fils);
			pere->fils = NULL;
			return 0;
		}

	}else{//verif * cookie-octet

		while((res = verifCookie_octet(valeur+taille_mot,petit_frere, index+taille_mot, long_max))){
		 taille_mot += res;
		 res = 0;
		 frere = petit_frere;
		 petit_frere = creerFrere(frere);
	 }

	 if(taille_mot > 0){
     free(petit_frere);
     frere->frere = NULL;
   }else{
     free(fils);
     pere->fils = NULL;
   }

	}

	//remplissage Noeud
  pere->tag = "cookie-value";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;
}

//cookie-pair = cookie-name "=" cookie-value
int verifCookie_pair(char* valeur, Noeud* pere, int index, int long_max){
	//definition des variables
	int taille_mot=0;
	int res;

	//verification de la taille de la requete
	if(index>=long_max){
		return 0;
	}

	Noeud* fils = creerFils(pere);

	if((res = verifCookie_name(valeur+taille_mot,fils,index+taille_mot,long_max))){
		taille_mot+=res;
	}else{
		purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
		pere->fils = NULL;
		return 0;//il y a un probleme
	}

	if(*(valeur+taille_mot)=='='){
		taille_mot += 1;
	}else{
		purgeTree(fils);
		pere -> fils =NULL;
		return 0;
	}

	Noeud* frere = creerFrere(fils);

	if((res = verifCookie_value(valeur+taille_mot,frere,index+taille_mot,long_max))){
		taille_mot+=res;
	}else {
		purgeTree(fils);
		pere -> fils =NULL;
		return 0;
	}

	//remplissage Noeud
  pere->tag = "cookie-pair";
  pere->valeur = valeur;
  pere->longueur = taille_mot;

  return taille_mot;

}

//cookie-string = cookie-pair * ( ";" SP cookie-pair )
int verifCookie_string(char* valeur, Noeud* pere, int index, int long_max){
	//definition des variables
	int taille_mot=0;
	int res;
	int fin = 0;
	Noeud* fils;
	Noeud* frere;
	Noeud* petit_frere;

	//verification de la taille de la requete
	if(index>=long_max){
		return 0;
	}

	fils = creerFils(pere);

	if((res = verifCookie_pair(valeur+taille_mot,fils,index+taille_mot,long_max))){
		taille_mot+=res;
	}else{
		purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
		pere->fils = NULL;
		return 0;//il y a un probleme
	}

	Noeud* frere_debut_bloc;
	Noeud* gd_frere_debut_bloc;
	int taille_bloc = 0;
	petit_frere = fils;

  while (!fin){
		frere = petit_frere;
    petit_frere = creerFrere(frere);

    frere_debut_bloc = petit_frere;
    gd_frere_debut_bloc = frere;

    if (*(valeur+taille_mot) == ';'){
      taille_bloc+=1;

			if((res = verifSP(valeur+taille_mot+taille_bloc,petit_frere,index+taille_mot+taille_bloc,long_max))){
	      taille_bloc+=res;
	      res = 0 ;
	      frere = petit_frere;
	      petit_frere = creerFrere(frere);
				if((res = verifCookie_pair(valeur+taille_mot+taille_bloc,petit_frere,index+taille_mot+taille_bloc,long_max))){
					taille_bloc+=res;
		      res = 0 ;

	      	taille_mot += taille_bloc;
				}else {
					printf("3\n");
					purgeTree(frere_debut_bloc);
		      gd_frere_debut_bloc->frere = NULL;
		      fin = 1;
		    }
			}else {
				printf("2\n");
				purgeTree(frere_debut_bloc);
	      gd_frere_debut_bloc->frere = NULL;
	      fin = 1;
	    }
    } else {
			printf("1\n");
			purgeTree(frere_debut_bloc);
      gd_frere_debut_bloc->frere = NULL;
      fin = 1;
    }
		taille_bloc = 0;
  }

	//remplissage Noeud
  pere->tag = "cookie-string";
  pere->valeur = valeur;
  pere->longueur = taille_mot;

  return taille_mot;

}

//Cookie-header = "Cookie:" OWS cookie-string OWS
int verifCookie_header(char* valeur, Noeud* pere, int index, int long_max){
	int taille_mot = 0;
  int est_juste = 1;
  int res;
  char* expect = "Cookie:" ;

  if(index>=long_max){
    return 0;
  }

  for (int i = 0; i < 7; i++) {
    if (*(valeur+i) != expect[i]) {
      est_juste = 0;
    }
  }
  if (est_juste) {
    taille_mot = 7;
  }else{
    return 0;
  }


  Noeud* fils = creerFils(pere);
  res = verifOWS(valeur+taille_mot,fils,index+taille_mot,long_max);
  taille_mot += res;

  Noeud* frere = creerFrere(fils);
  if((res = verifCookie_string(valeur+taille_mot,frere,index+taille_mot,long_max))){
    taille_mot+=res;
  }else{
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;//il y a un probleme
  }

  frere = creerFrere(frere);
  res = verifOWS(valeur+taille_mot,frere,index+taille_mot,long_max);
  taille_mot += res;

  //remplissage Noeud
  pere->tag = "Cookie-header";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;
}

//Expect-header = "Expect" ":" OWS Expect OWS
int verifExpect_header(char* valeur, Noeud* pere, int index, int long_max){
	int taille_mot = 0;
  int est_juste = 1;
  int res;
  char* expect = "Expect:" ;

  if(index>=long_max){
    return 0;
  }

  for (int i = 0; i < 7; i++) {
    if (*(valeur+i) != expect[i]) {
      est_juste = 0;
    }
  }
  if (est_juste) {
    taille_mot = 7;
  }else{
    return 0;
  }


  Noeud* fils = creerFils(pere);
  res = verifOWS(valeur+taille_mot,fils,index+taille_mot,long_max);
  taille_mot += res;

  Noeud* frere = creerFrere(fils);
  if((res = verifExpect(valeur+taille_mot,frere,index+taille_mot,long_max))){
    taille_mot+=res;
  }else{
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    pere->fils = NULL;
    return 0;//il y a un probleme
  }

  frere = creerFrere(frere);
  res = verifOWS(valeur+taille_mot,frere,index+taille_mot,long_max);
  taille_mot += res;

  //remplissage Noeud
  pere->tag = "Expect-header";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;
}

//dec-octet = "25" %x30-35 / "2" %x30-34 DIGIT / "1" 2 DIGIT / %x31-39 DIGIT / DIGIT
int verifDec_octet(char* valeur, Noeud* pere, int index, int long_max){
	int taille_mot = 0;
	int res = 0;
	int res2 = 0;

	if(index>=long_max){
    return 0;
  }

	Noeud* fils = creerFils(pere);
	Noeud* frere = creerFrere(fils);

  if( (*(valeur) == '2') && (*(valeur+1) == '5') && ((*(valeur+2) > 47) && (*(valeur+2) < 54)) ){
		taille_mot = 3;
		purgeTree(fils);
		pere->fils = NULL;
	}else if((*(valeur) == '2') && ((*(valeur+1) > 47) && (*(valeur+1) < 53)) && (res = verifDIGIT(valeur+2,fils,index+2,long_max))) {
		taille_mot = 2 + res;
		purgeTree(frere);
		fils->frere = NULL;
	}else if((*(valeur) == '1') && (res = verifDIGIT(valeur+1,fils,index+1,long_max)) && (res2 = verifDIGIT(valeur+2,frere,index+2,long_max))) {
		taille_mot = 1 + res + res2;
	}else if(((*(valeur) > 48) && (*(valeur) < 58)) && (res = verifDIGIT(valeur+1,fils,index+1,long_max))) {
		taille_mot = 1 + res;
		purgeTree(frere);
		fils->frere = NULL;
	}else if((res = verifDIGIT(valeur,fils,index,long_max))){
		taille_mot  = res;
		purgeTree(frere);
		fils->frere = NULL;
	}else{
		purgeTree(fils);
		pere->fils = NULL;
		return 0;
	}

	//remplissage Noeud
  pere->tag = "dec-octet";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;
}

//qdtext = HTAB / SP / "!" / %x23-5B / %x5D-7E / obs-text
int verifQdtext(char* valeur, Noeud* pere, int index, int long_max){
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
    (*(valeur) == '!') ||
    ((*(valeur) >= 35) && (*(valeur) <= 91)) ||
    ((*(valeur) >= 93) && (*(valeur) <= 126)) )
  {
    taille_mot = 1;
  }else if (
    (taille_mot = verifHTAB(valeur, fils, index, long_max)) ||
    (taille_mot = verifSP(valeur, fils, index, long_max)) ||
    (taille_mot = verifObs_text(valeur, fils, index, long_max)))
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
  //remplissage noeud
  pere->tag = "qdtext";
  pere->valeur = valeur;
  pere-> longueur = taille_mot;

  return taille_mot;
}

//quoted-pair = "\" ( HTAB / SP / VCHAR / obs-text )
int verifQuoted_Pair(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot = 0;
  int res = 0;
  Noeud* fils;
  Noeud* frere;

  if(index>=long_max){
    return 0;
  }else{
    taille_mot = 1;
  }

  fils = creerFils(pere);
  fils->tag = "tag_a_changer";
  fils->valeur = valeur;
  fils->longueur = 1;
  frere = creerFrere(fils);
  if(
    (res = verifHTAB(valeur+taille_mot, frere, index+taille_mot, long_max)) ||
    (res = verifSP(valeur+taille_mot, frere, index+taille_mot, long_max)) ||
    (res = verifVCHAR(valeur+taille_mot, frere, index+taille_mot, long_max))||
    (res = verifObs_text(valeur+taille_mot, frere, index+taille_mot, long_max))
  ){
    taille_mot += res;
  }else{
    free(frere);
    fils->frere = NULL;
    return 0;
  }



  pere->tag = "quoted-pair";
  pere->valeur = valeur;
  pere->longueur = taille_mot;

  return taille_mot;
}

//quoted-string = DQUOTE * ( qdtext / quoted-pair ) DQUOTE
int verifQuoted_string(char* valeur, Noeud* pere, int index, int long_max){
int taille_mot = 0;
int res = 0;
int fin = false;
Noeud* fils;
Noeud* frere;
Noeud* frere2;

//verirication que l'on ne depasse pas la longueur à parser
if(index >= long_max){
  return 0;
}
fils = creerFils(pere);


if(verifDQUOTE(valeur, fils, index, long_max)){
  taille_mot += 1;
}else{
  return 0;
}

frere = creerFrere(fils);
frere2 = frere;
while(!fin){
  if((res = verifQdtext(valeur+taille_mot, frere2, index+taille_mot, long_max))){
    taille_mot += res;
    res = 0;
    frere = frere2;
    frere2 = creerFrere(frere);
  }else if((res = verifQuoted_Pair(valeur+taille_mot, frere2, index+taille_mot, long_max))){
    taille_mot += res;
    res = 0;
    frere = frere2;
    frere2 = creerFrere(frere);
  }else{
    fin = 1;
  }
}

if(taille_mot > 1){
  purgeTree(frere2);
  frere->frere = NULL;
  frere2 = creerFrere(frere);
}else{
  purgeTree(frere);
  fils->frere = NULL;
  frere2 = creerFrere(fils);
}
if(verifDQUOTE(valeur+taille_mot, frere2, index+taille_mot, long_max)){
  taille_mot += 1;
}else{
  purgeTree(fils);
  pere->fils = NULL;
  return 0;
}



//remplissage Noeud
pere->tag = "quoted-string";
pere->valeur = valeur;
pere->longueur = taille_mot;


return taille_mot;
}

//parameter = token "=" ( token / quoted-string )
int verifParameter(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot = 0;
  int res;
  Noeud* fils;
  Noeud* frere;
  Noeud* frere2;

  if(index>=long_max){
    return 0;
  }
  fils = creerFils(pere);
  if((res = verifToken(valeur, fils, index, long_max))){
    taille_mot += res;
    res = 0;
  }else{
    purgeTree(fils);
    pere->fils = NULL;
    return 0;
  }

  if(*(valeur+taille_mot) == '='){
    frere = creerFrere(fils);
    frere->tag = "tag_a_changer";
    frere->valeur = valeur+taille_mot;
    frere->longueur = 1;
    taille_mot += 1;
  }else{
    purgeTree(fils);
    pere->fils = NULL;
    return 0;
  }

  frere2 = creerFrere(frere);
  if((res = verifToken(valeur+taille_mot, frere2, index+taille_mot, long_max))){
    taille_mot += res;
    res = 0;

  }else if((res = verifQuoted_string(valeur+taille_mot, frere2, index+taille_mot, long_max))){
    taille_mot += res;
    res = 0;
  }else{
    purgeTree(fils);
    pere->fils = NULL;
    return 0;
  }
  //remplissage Noeud
  pere->tag = "parameter";
  pere->valeur = valeur;
  pere->longueur = taille_mot;


  return taille_mot;



}

//media-type = type "/" subtype * ( OWS ";" OWS parameter )
int verifMedia_type(char* valeur, Noeud* pere, int index, int long_max){
  int taille_mot = 0;
  int res = 0;
  int fin = false;
  Noeud* fils;
  Noeud* frere;
  Noeud* frere2;

  if(index>=long_max){
    return 0;
  }
  //type
  fils = creerFils(pere);
  if((res = verifType(valeur, fils, index,long_max))){
    taille_mot += res;
    res = 0;
  }else{
    purgeTree(fils);
    pere->fils = NULL;
    return 0;
  }

  //"/"
  if(*(valeur+taille_mot) == '/'){
    frere = creerFrere(fils);
    frere->tag = "tag_a_changer";
    frere->valeur = valeur+taille_mot;
    frere->longueur = 1;
    taille_mot += 1;
  }else{
    purgeTree(fils);
    pere->fils = NULL;
    return 0;
  }
  // verifSubtype
  frere2 = creerFrere(frere);
  if((res = verifSubtype((valeur+taille_mot), frere2, (index+taille_mot), long_max))){
    taille_mot += res;
    res = 0;
    frere = frere2;
  }else{
    purgeTree(fils);
    pere->fils = NULL;
    return 0;
  }

  //* ( OWS ";" OWS parameter )
  while(!fin){
    //OWS
    frere2 = creerFrere(frere);
    if((res = verifOWS((valeur+taille_mot), frere2, (index+taille_mot), long_max))){
      taille_mot += res;
      res = 0;
      frere = frere2;
      frere2 = creerFrere(frere);
      //";"
      if(*(valeur+taille_mot) == ';'){
        frere2->tag = "tag_a_changer";
        frere2->valeur = valeur+taille_mot;
        frere2->longueur = 1;
        taille_mot += 1;
        frere = frere2;
        frere2 = creerFrere(frere);
        //OWS
        if((res = verifOWS((valeur+taille_mot), frere2, (index+taille_mot), long_max))){
          taille_mot += res;
          res = 0;
          frere = frere2;
          frere2 = creerFrere(frere);
          //parameter
          if((res = verifParameter((valeur+taille_mot), frere2, (index+taille_mot), long_max))){
            taille_mot += res;
            res = 0;
            frere = frere2;
          }else{
            purgeTree(fils);
            pere->fils = NULL;
            return 0;
          }
        }else{
          purgeTree(fils);
          pere->fils = NULL;
          return 0;
        }
      }else{
        purgeTree(fils);
        pere->fils = NULL;
        return 0;
      }
    }else{
      fin = true;
    }
  }






  //remplissage Noeud
  pere->tag = "media-type";
  pere->valeur = valeur;
  pere->longueur = taille_mot;
  return taille_mot;
}
