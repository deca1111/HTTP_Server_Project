#include "grammaire_simp.h"

/*message = debut 2*( mot ponct /nombre separateur ) [ponct] fin LF*/
int verifMessage(char* valeur, Noeud* pere){
  int taille_mot = 0;
  int res = 0;
  int res2 = 0;
  int fin = 0;
  int est_mot = 0;
  int compteur = 0;
  Noeud* fils;
  Noeud* frere;
  Noeud* frere_2;
  Noeud* frere_3;


  //verification Debut
  fils = creerFils(pere);
  frere = fils;
  if((res = verifDebut(valeur, frere))){
    taille_mot += res;
    res = 0;
  }else{
    free(fils);
    pere->fils = NULL;
    return 0;
  }

  //verification mot ponct / nombre Separateur
  while(!fin)
  {
    frere_2 = creerFrere(frere);
    frere_3 = creerFrere(frere_2);

    if(((res = verifMot(valeur+taille_mot, frere_2)))){
      if((res2 = verifPonct(valeur+taille_mot+res, frere_3))){
        taille_mot = taille_mot + res + res2;
        res = 0;
        res2 = 0;
        compteur += 1;
        est_mot = 1;
        frere = frere_3;
      }else{
        est_mot = 0;
      }
    }else{
      est_mot = 0;
    }

    if(!est_mot){
      if((res = verifNombre(valeur+taille_mot, frere_2))){
        if((res2 = verifSeparateur(valeur+taille_mot+res, frere_3))){
          taille_mot = taille_mot + res + res2;
          res = 0;
          res2 = 0;
          compteur += 1;
          frere = frere_3;
        }else{
          fin = 1;
          free(frere_2);
          free(frere_3);
          frere->frere = NULL;
        }
      }else{
        fin = 1;
        free(frere_2);
        free(frere_3);
        frere->frere = NULL;
      }
    }
  }

  if(compteur < 2){
    //purgeTree(fils);
    return 0;
  }

  //verification ponct
  frere_2 = creerFrere(frere);

  if((res = verifPonct(valeur+taille_mot, frere_2))){
    taille_mot += res;
    res = 0;
    frere = frere_2;
  }else{
    free(frere_2);
    frere->frere = NULL;
  }

  //verification fin
  frere_2 = creerFrere(frere);
  if((res = verifFin(valeur+taille_mot, frere_2))){
    taille_mot += res;
    res = 0;
    frere = frere_2;
  }else{
    purgeTree(fils);
    return 0;
  }

  //verification LF
  frere_2 = creerFrere(frere);
  if((res = verifLF(valeur+taille_mot, frere_2))){
    taille_mot += res;
    res = 0;
    frere = frere_2;
  }else{
    purgeTree(fils);
    return 0;
  }

  pere->tag = "message";
  pere->valeur = valeur;
  pere->longueur = taille_mot;

  /*
  //affichage du Mot
  for(int i = 0; i < pere->profondeur; i++){
    printf("\t");
  }
  printf("Message: ");
  for(int i = 0; i < taille_mot; i++){
    printf("%c",*(valeur+i));
  }
  printf("\n");
  */

  return taille_mot;
}

int verifDebut(char* valeur, Noeud* pere){
  int taille_mot = 0;
  char* start = "start";

  for(int i = 0; i < 5; i++){
    if(*(valeur+i) != start[i]){
      return 0;
    }
  }
  taille_mot = 5;

  //remplissage du noeud
  pere->tag = "debut";
  pere->valeur = valeur;
  pere->longueur = taille_mot;

  /*
  //affichage du Mot
  for(int i = 0; i < pere->profondeur; i++){
    printf("\t");
  }
  printf("Debut: ");
  for(int i = 0; i < taille_mot; i++){
    printf("%c",*(valeur+i));
  }
  printf("\n");
  */

  return taille_mot;
}

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
  frere->frere = NULL;

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

  /*
  //affichage du Mot
  for(int i = 0; i < pere->profondeur; i++){
    printf("\t");
  }
  printf("Mot: ");
  for(int i = 0; i < taille_mot; i++){
    printf("%c",*(valeur+i));
  }
  printf("\n");
  */

  return taille_mot;
}

int verifPonct(char* valeur, Noeud* pere){
  int taille_mot;
  if((*(valeur)==',') || (*(valeur)=='.') || (*(valeur)=='!') || (*(valeur)=='?') || (*(valeur)==':')){
    taille_mot = 1;//est une ponctuation
  }else{
    return 0;
  }
  //remplissage du noeud
  pere->tag = "ponct";
  pere->valeur = valeur;
  pere->longueur = taille_mot;

  /*
  //affichage du Mot
  for(int i = 0; i < pere->profondeur; i++){
    printf("\t");
  }
  printf("Ponctuation: ");
  for(int i = 0; i < taille_mot; i++){
    printf("%c",*(valeur+i));
  }
  printf("\n");
  */

  return taille_mot;
}

int verifNombre(char* valeur, Noeud* pere){
  int taille_mot = 0;
  int res = 0;
  Noeud* fils;
  Noeud* frere;
  Noeud* petit_frere;

  fils = creerFils(pere);
  frere = fils;
  petit_frere = fils;

  //Tant que on a des nombres on continu a remplir des Noeud
  //a la dernière iteration qui fait sortir de la boucle, on aura deja un petit
  // frere de cree, il faut donc le free

  while((res = verifDIGIT((valeur+taille_mot),petit_frere))){
    taille_mot += res;
    res = 0;
    frere = petit_frere;
    petit_frere = creerFrere(frere);
  }
  free(petit_frere);
  frere->frere = NULL;

  //verif qu'il y a au moins 1 nombre
  if(taille_mot == 0){
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    return 0;//il y a un probleme
  }

  //remplissage Noeud
  pere->tag = "nombre";
  pere->valeur = valeur;
  pere->longueur = taille_mot;

  /*
  //affichage du Mot
  for(int i = 0; i < pere->profondeur; i++){
    printf("\t");
  }
  printf("Nombre: ");
  for(int i = 0; i < taille_mot; i++){
    printf("%c",*(valeur+i));
  }
  printf("\n");
  */

  return taille_mot;
}

int verifSeparateur(char* valeur, Noeud* noeud){
  int taille_mot;
  if((*(valeur)==' ') || (*(valeur)=='\t') || (*(valeur)=='-') || (*(valeur)=='_')){
    taille_mot = 1;//est un separateur
  }else{
    return 0;
  }

  //remplissage Noeud
  noeud->tag = "separateur";
  noeud->valeur = valeur;
  noeud->longueur = taille_mot;

  /*
  //affichage du Mot
  for(int i = 0; i < noeud->profondeur; i++){
    printf("\t");
  }
  printf("Separateur: ");
  for(int i = 0; i < taille_mot; i++){
    printf("%c",*(valeur+i));
  }
  printf("\n");
  */

  return taille_mot;
}

int verifFin(char* valeur, Noeud* pere){
  int taille_mot = 0;
  char* fin = "fin";

  for(int i = 0; i < 3; i++){
    if(*(valeur+i) != fin[i]){
      return 0;
    }
  }
  taille_mot = 3;

  //remplissage du noeud
  pere->tag = "fin";
  pere->valeur = valeur;
  pere->longueur = taille_mot;

  /*
  //affichage du Mot
  for(int i = 0; i < pere->profondeur; i++){
    printf("\t");
  }
  printf("Fin: ");
  for(int i = 0; i < taille_mot; i++){
    printf("%c",*(valeur+i));
  }
  printf("\n");
  */

  return taille_mot;
}

int verifLF(char* valeur, Noeud* noeud){
  int taille_mot;

  if(*valeur == '\n'){
    /*
    for(int i = 0; i < noeud->profondeur; i++){
      printf("\t");
    }
    printf("LF: \\n\n");
    */
    taille_mot = 1;//est un separateur
  }else{
    taille_mot = 0;//pas un separateur
  }

  //remplissage Noeud
  noeud->tag = "LF";
  noeud->valeur = valeur;
  noeud->longueur = taille_mot;

  return taille_mot;
}

int verifDIGIT(char* valeur, Noeud* noeud){
  int taille_mot;

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

  /*
  //affichage du Mot
  for(int i = 0; i < noeud->profondeur; i++){
    printf("\t");
  }
  printf("DIGIT: ");
  for(int i = 0; i < taille_mot; i++){
    printf("%c",*(valeur+i));
  }
  printf("\n");
  */

  return taille_mot;
}

int verifALPHA(char* valeur, Noeud* noeud){
  int taille_mot;

  if( ((*valeur < 91) && (*valeur > 64)) || ((*valeur > 96) && (*valeur < 123))){
    taille_mot = 1;//est un separateur
  }else{
    taille_mot = 0;//pas un separateur
    return taille_mot;
  }

  //remplissage Noeud
  noeud->tag = "ALPHA";
  noeud->valeur = valeur;
  noeud->longueur = taille_mot;
  

  return taille_mot;
}
