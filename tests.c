#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char const *argv[]) {

  char* str = "abcdefgh";

  char* tag;
  int longueur;

  tag = &(str[2]);
  longueur = 3;

  for (int i = 0; i < longueur; i++) {
    printf("%c",*(tag+i) );

  }
  printf("\n");

  return 0;
}
