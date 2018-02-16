#include <stdio.h>
#include <stdlib.h>
#include "symboles.h"
#include "util.h"
#include "analyseur_syntaxique.h"

char yytext[100];
FILE *yyin;

int main(int argc, char **argv) {
  yyin = fopen(argv[1], "r");
  if(yyin == NULL){
    fprintf(stderr, "impossible d'ouvrir le fichier %s\n", argv[1]);
    exit(1);
  }
int uniteeCourante=start();

    if(uniteeCourante==FIN){
        printf("FIN\n");
        return 0;
    }
    printf("Erreur syntaxique\n");
    return -1;
  //test_yylex_internal(yyin);
  //return 0;
}

