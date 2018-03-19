#ifndef ANALYSEUR_SYNTAXIQUE
#define ANALYSEUR_SYNTAXIQUE


#include<stdio.h>
#include<stdlib.h>
#include"symboles.h"
#include "util.h"
#include "premiers.h"
#include "suivants.h"
#include "affiche_arbre_abstrait.h"
#include "syntabs.h"

n_prog *pg();
n_l_dec *odv();
n_l_dec *ldf();
n_l_dec *ldv();
n_dec *dv();
n_l_dec *ldvb();
n_dec *ott(char* nom);
n_dec *df();
n_l_dec *lp();
n_instr *ib();
n_l_dec *oldv();

n_instr *iaff();
n_instr *isi();
n_instr *itq();
n_instr *iapp();
n_instr *iret();
n_instr *iecr();
n_instr *ivide();

n_var *var();
n_l_instr *li();
n_instr *i();

n_instr *osinon();
n_appel *appf();
n_var *oind();
n_l_exp *lexp();
n_l_exp *lexpb(n_l_exp *h);

void Ptvirgule();


int start();
n_exp *exp();
n_exp *expb(n_exp *h);
n_exp *conj();
n_exp *conjb(n_exp *h);
n_exp *comp();
n_exp *compb(n_exp *h);
n_exp *e();
n_exp *eb(n_exp *h);
n_exp *t();
n_exp *tb(n_exp *h);
n_exp *neg();
n_exp *f();
#endif // ANALYSEUR_SYNTAXIQUE
