#include "grammaire_simp.h"


int verifMessage(char* valeur, Noeud* pere){
  int taille_mot = 0;
  int res = 0;
  int fin = 0;
  int compteur = 0;
  Noeud* fils;
  Noeud* frere;
  Noeud* frere_2;
  Noeud* petit_frere;
  Noeud* petit_frere_2;


  //verification Debut
  fils = creerFils(pere);
  frere = creerFrere(fils);
  if((res = verifDebut(valeur, frere))){
    taille_mot += res;
    res = 0;
  }else{
    purgeTree(fils);
    return 0;
  }
  //verification mot ponct / nombre Separateur
  frere_2 = creerFrere(frere);
  frere = frere_2;
  frere_2 = creerFrere(frere);
  petit_frere = creerFrere(frere_2);
  while(!fin)
  {
    if(((res+=verifMot(valeur+taille_mot, frere_2)) && (res+=verifPonct(valeur+taille_mot, petit_frere)))){
      taille_mot += res;
      res = 0;
      compteur += 1;
      frere = frere_2;
      frere_2 = petit_frere;
      petit_frere = creerFrere(frere_2);

    }else if(((res+=verifNombre(valeur+taille_mot, frere_2)) && (res+=verifSeparateur(valeur+taille_mot, petit_frere)))){
      taille_mot += res;
      res = 0;
      compteur += 1;
      frere = frere_2;
      frere_2 = petit_frere;
      petit_frere = creerFrere(frere_2);
    }else{
      fin = 1;
      free(petit_frere);
    }
  }
  if(compteur < 3){
    purgeTree(fils);
    return 0;
  }
  //verification ponct
  frere = frere_2;
  if(())
  //verification fin

  //verification LF

  pere->tag = "message";
  pere->valeur = valeur;
  pere->longueur = taille_mot;

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

  //affichage du Mot
  printf("Debut: ");
  for(int i = 0; i < taille_mot; i++){
    printf("%c",*(valeur+i));
  }
  printf("\n");
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

  //affichage du Mot
  printf("Mot: ");
  for(int i = 0; i < taille_mot; i++){
    printf("%c",*(valeur+i));
  }
  printf("\n");

  return taille_mot;
}
int verifPonct(char* valeur, Noeud* pere){
  int taille_mot;

  if((*(valeur)==',') || (*(valeur)=='.') || (*(valeur)=='!') || (*(valeur)=='?') || (*(valeur)==':')){
    taille_mot = 1;//est une ponctuation
    printf("separateur: %c\n",*valeur);
  }else{
    return 0;
  }
  //remplissage du noeud
  pere->tag = "ponct";
  pere->valeur = valeur;
  pere->longueur = taille_mot;

  //affichage du Mot
  printf("Ponctuation: ");
  for(int i = 0; i < taille_mot; i++){
    printf("%c",*(valeur+i));
  }
  printf("\n");
  return taille_mot;
}
int verifNombre(char* valeur, Noeud* pere){
  int taille_mot = 0;
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

  //verif qu'il y a au moins 1 nombre
  if(taille_mot == 0){
    purgeTree(fils);//on detruit tous les noeuds eventuelement crées avant
    return 0;//il y a un probleme
  }
  //remplissage Noeud
  pere->tag = "nombre";
  pere->valeur = valeur;
  pere->longueur = taille_mot;
  //affichage du Mot
  printf("Nombre: ");
  for(int i = 0; i < taille_mot; i++){
    printf("%c",*(valeur+i));
  }
  printf("\n");
  return taille_mot;
}
int verifSeparateur(char* valeur, Noeud* noeud){
  int taille_mot;

  if((*(valeur)==' ') || (*(valeur)=='\t') || (*(valeur)=='-') || (*(valeur)=='_')){
    taille_mot = 1;//est un separateur
    printf("separateur: %c\n",*valeur);
  }else{
    return 0;
  }

  //remplissage Noeud
  noeud->tag = "separateur";
  noeud->valeur = valeur;
  noeud->longueur = taille_mot;

  return taille_mot;
}
int verifFin(char* valeur, Noeud* noeud){
  int taille_mot = 0;
  char* fin = "fin";

  for(int i = 0; i < 5; i++){
    if(*(valeur+i) != fin[i]){
      return 0;
    }
  }
  taille_mot = 5;

  //remplissage du noeud
  pere->tag = "fin";
  pere->valeur = valeur;
  pere->longueur = taille_mot;

  //affichage du Mot
  printf("Fin: ");
  for(int i = 0; i < taille_mot; i++){
    printf("%c",*(valeur+i));
  }
  printf("\n");
  return taille_mot;
}
int verifLF(char* valeur, Noeud* noeud){
  int taille_mot;

  if(*valeur == '\n'){
    printf("LF: %c\n",*valeur);
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
    printf("DIGIT: %c\n",*valeur);
    taille_mot = 1;//est un separateur
  }else{
    taille_mot = 0;//pas un separateur
  }

  //remplissage Noeud
  noeud->tag = "DIGIT";
  noeud->valeur = valeur;
  noeud->longueur = taille_mot;

  return taille_mot;
}
int verifALPHA(char* valeur, Noeud* noeud){
  int taille_mot;

  if( ((*valeur < 91) && (*valeur > 64)) || ((*valeur > 96) && (*valeur < 123))){
    printf("ALPHA: %c\n",*valeur);
    taille_mot = 1;//est un separateur
  }else{
    taille_mot = 0;//pas un separateur
  }

  //remplissage Noeud
  noeud->tag = "ALPHA";
  noeud->valeur = valeur;
  noeud->longueur = taille_mot;

  return taille_mot;
}
