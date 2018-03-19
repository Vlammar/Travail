/*
 * Analyseur lexical du compilateur L en FLEX
 */

%{
#include "symboles.h"
%}
%option yylineno
%option nounput
%option noinput
lettre [A-Za-z]
chiffre [0-9]
nombre {chiffre}+
identificateur_var \$({lettre}|_|\$|{chiffre})*
identificateur_fct ({lettre}|_)+

%%
"#".* ;
";" {return POINT_VIRGULE; }
"+" {return PLUS; }
"-" {return MOINS; }
"*" {return FOIS; }
"/" {return DIVISE; }
"%" {return MODULO; }
"(" {return PARENTHESE_OUVRANTE; }
")" {return PARENTHESE_FERMANTE; }
"[" {return CROCHET_OUVRANT; }
"]" {return CROCHET_FERMANT; }
"{" {return ACCOLADE_OUVRANTE; }
"}" {return ACCOLADE_FERMANTE; }
"=" {return EGAL; }
"<" {return INFERIEUR; }
">" {return SUPERIEUR; }
"&" {return ET; }
"|" {return OU; }
"!" {return NON; }
si {return SI; }
alors {return ALORS; }
sinon {return SINON; }
tantque {return TANTQUE; }
faire {return FAIRE; }
entier {return ENTIER; }
retour {return RETOUR;}
lire {return LIRE; }
ecrire {return ECRIRE; }
{nombre} {return NOMBRE;}
"," {return VIRGULE; }

{identificateur_var} {return ID_VAR;}

{identificateur_fct} {return ID_FCT;}


<<EOF>>              { return FIN;                 }  /* Fin de fichier */
[\n\t ] ;



%%
int yywrap(){

  return 1;
}


