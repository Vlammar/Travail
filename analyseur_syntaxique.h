#ifndef ANALYSEUR_SYNTAXIQUE
#define ANALYSEUR_SYNTAXIQUE


#include<stdio.h>
#include<stdlib.h>
#include"symboles.h"
#include "util.h"
#include "premiers.h"
#include "suivants.h"
void pg();
void odv();
void ldf();
void ldv();
void dv();
void ldvb();
void ott();
void df();
void lp();
void ib();
void oldv();

void iaff();
void isi();
void itq();
void iapp();
void iret();
void iecr();
void ivide();

void var();
void li();
void i();

void osinon();
void appf();
void oind();
void lexp();
void lexpb();

void Ptvirgule();


int start();
void exp();
void expb();
void conj();
void conjb();
void comp();
void compb();
void e();
void eb();
void t();
void tb();
void neg();
void f();
#endif // ANALYSEUR_SYNTAXIQUE
