#include"analyseur_syntaxique.h"
#include"symboles.h"
int uniteeCourante;
operation op;

void process() {
    char nom[100], valeur[100];
    nom_token(uniteeCourante,nom,valeur);
    affiche_element(nom,valeur,1);
    uniteeCourante=yylex();
}

//Retourne uniteeCourante pour tester si FIN est detecte
int start() {
    uniteeCourante=yylex();
    initialise_premiers();
    initialise_suivants();
    //Axiome
    pg();
    return uniteeCourante;
}
n_prog *pg() {
    n_l_dec *$1=NULL;
    n_l_dec *$2=NULL;
    n_prog *$$=NULL;
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_optDecVariables_,uniteeCourante)||est_premier(_listeDecFonctions_,uniteeCourante)||est_suivant(_programme_,uniteeCourante)) {
        $1=odv();
        $2=ldf();
        $$=cree_n_prog($1,$2);
        return $$;
    }
    affiche_balise_fermante(__FUNCTION__,1);
}

n_l_dec *odv() {
    n_l_dec *$$=NULL;

    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_listeDecVariables_,uniteeCourante)) {
        $$=ldv();
        Ptvirgule();
        return $$;
    } else {
        if(est_suivant(_optDecVariables_,uniteeCourante)) {

        } else {
            //affiche_balise_fermante(__FUNCTION__,1);
            printf("Erreur de syntaxe\n");
            exit(-1);
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return NULL;
}

n_l_dec *ldv() {
    n_dec *$1=NULL;
    n_l_dec *$2=NULL;
    n_l_dec *$$=NULL;

    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_declarationVariable_,uniteeCourante)) {
        $1=dv();
        $2=ldvb();
        $$=cree_n_l_dec($1,$2);
        return $$;
    } else {
        // if(est_suivant(_listeDecVariables_,uniteeCourante)) {} else {
        printf("Erreur de syntaxe\n");
        exit(-1);
    }
    //}
    affiche_balise_fermante(__FUNCTION__,1);
}

n_l_dec *ldvb() {

    n_dec *$2=NULL;
    n_l_dec *$3=NULL;

    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==VIRGULE) {
        process();

        $2=dv();
        $3=ldvb();
        $$=cree_n_l_dec($2,$3);
        return $$;
    } else {
        if(est_suivant(_listeDecVariablesBis_,uniteeCourante)) {

        } else {
            affiche_balise_fermante(__FUNCTION__,1);
            printf("Erreur de syntaxe\n");
            exit(-1);
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return NULL;
}


n_dec * dv() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==ENTIER) {
        process();

        if(uniteeCourante==ID_VAR) {
            char* nom=yytext();
            process();

            return ott(nom);
        } else {
            printf("Erreur de syntaxe: Declaration de variable incorrecte\n");
            exit(-1);
        }
    } else {
        affiche_balise_fermante(__FUNCTION__,1);
        printf("Erreur de syntaxe: Declaration de variable incorrecte\n");
        exit(-1);

    }
    affiche_balise_fermante(__FUNCTION__,1);

}

n_dec *ott(char* nom) {
    n_dec *$$=NULL;
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==CROCHET_OUVRANT) {
        process();


        if(uniteeCourante==NOMBRE) {
            $$=cree_n_dec_tab(nom,atoi(yytext());
                              process();

            if(uniteeCourante==CROCHET_FERMANT) {
            process();
                return $$;
            } else {
                printf("Erreur de syntaxe: Crochet fermant manquant\n");
                exit(-1);
            }
        } else {
            printf("Erreur de syntaxe: Declaration incorrecte\n");
            exit(-1);
        }
    } else {
        if(est_suivant(_optTailleTableau_,uniteeCourante)) {
            $$=cree_n_dec_var(nom);
            return $$;

        } else {
            printf("Erreur de syntaxe\n");
            exit(-1);
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}

n_l_dec *ldf() {
    n_l_dec *$$ = NULL;
    n_dec *$1 = NULL;
    n_l_dec *$2 = NULL;
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_declarationFonction_,uniteeCourante)) {
        $1 = df();
        $2 = ldf();
        $$ = cree_n_l_dec($1, $2);
    } else {
        if(est_suivant(_listeDecFonctions_,uniteeCourante)) {} else {
            printf("Erreur de syntaxe\n");
            exit(-1);
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}

n_dec *df() {
    n_dec *$$ = NULL;
    n_l_dec *$2 = NULL;
    n_l_dec *$3 = NULL;
    n_instr *$4 = NULL;
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==ID_FCT) {
        char * s = yytext();
        process();

        $2 = lp();
        $3 = odv();
        $4 = ib();
        $$ = cree_n_dec_fonc(s, $2, $3, $4);
    } else {
        printf("Erreur de syntaxe: id_fct\n");
        exit(-1);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}

n_l_dec *lp() {
    n_l_dec *$$=NULL;

    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==PARENTHESE_OUVRANTE) {
        process();

        $$ = oldv();

        if(uniteeCourante==PARENTHESE_FERMANTE) {
            process();

        } else {
            printf("Erreur de syntaxe: Parenthese fermante manquante\n");
            exit(-1);
        }
    } else {
        printf("Erreur de syntaxe: Parenthese ouvrante manquante\n");
        exit(-1);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}


n_l_dec *oldv() {
    n_l_dec *$$=NULL;
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_listeDecVariables_,uniteeCourante)) {
        $$=ldv();
    } else {
        if(est_suivant(_optListeDecVariables_,uniteeCourante)) {} else {
            printf("Erreur de syntaxe\n");
            exit(-1);
        }

    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}
n_instr *i() {
    n_instr *$$=NULL;
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_instructionAffect_,uniteeCourante)) {
        $$=iaff();

    } else {
        if(est_premier(_instructionBloc_,uniteeCourante)) {
            $$=ib();

        } else {
            if(est_premier(_instructionSi_,uniteeCourante)) {
                $$=isi();

            } else {
                if(est_premier(_instructionTantque_,uniteeCourante)) {
                    $$=itq();

                } else {
                    if(est_premier(_instructionAppel_,uniteeCourante)) {
                        $$=iapp();

                    } else {
                        if(est_premier(_instructionRetour_,uniteeCourante)) {
                            $$=iret();

                        } else {
                            if(est_premier(_instructionEcriture_,uniteeCourante)) {
                                $$=iecr();

                            } else {
                                if(est_premier(_instructionVide_,uniteeCourante)) {
                                    $$=ivide();

                                } else {
                                    printf("Erreur de syntaxe\n");
                                    exit(-1);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}


n_instr *iaff() {
    n_var *$1=NULL;
    n_exp *$3=NULL;
    n_instr *$$=NULL;

    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_var_,uniteeCourante)) {
        $1=var();

        if(uniteeCourante==EGAL) {
            process();

            $3=exp();
            Ptvirgule();
            $$=cree_n_instr_affect($1,$3);

        } else {
            printf("Erreur de syntaxe : Erreur affectation\n");
            exit(-1);
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}

n_instr *ib() {
    n_instr *$$=NULL;
    n_l_instr *$2=NULL;
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==ACCOLADE_OUVRANTE) {
        process();

        $2=li();
        $$=cree_n_instr_bloc($2);
        if(uniteeCourante==ACCOLADE_FERMANTE) {
            process();

        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}

n_l_instr *li() {
    n_l_instr *$$=NULL;
    n_instr *$1=NULL;
    n_l_instr *$2=NULL;
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_instruction_,uniteeCourante)) {
        $1=i();
        $2=li();
        $$=cree_n_l_instr($1,$2);
    } else {
        if(est_suivant(_listeInstructions_,uniteeCourante)) {} else {
            printf("Erreur de syntaxe\n");
            exit(-1);
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}

n_instr *isi() {
    n_instr *$$=NULL;
    n_exp *$2=NULL;
    n_instr *$4=NULL;
    n_instr *$5=NULL;



    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==SI) {
        process();
        $2=exp();
        if(uniteeCourante==ALORS) {
            process();

            $4=ib();
            $5=osinon();
            $$=cree_n_instr_si($2,$4,$5);
        } else {
            printf("Erreur de syntaxe: Erreur alors\n");
            exit(-1);
        }
    } else {
        printf("Erreur de syntaxe: Erreur si\n");
        exit(-1);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}

n_instr *osinon() {
    n_instr *$$=NULL;
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==SINON) {
        process();

        $$=ib();
    } else {
        if(est_suivant(_optSinon_,uniteeCourante)) {} else {
            printf("Erreur de syntaxe\n");
            exit(-1);
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}
n_instr *itq() {
    n_instr *$$=NULL;
    n_exp *$2=NULL;
    n_instr *$4=NULL;
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==TANTQUE) {
        process();

        $2=exp();
        if(uniteeCourante==FAIRE) {
            process();

            $4=ib();
            $$=cree_n_instr_tantque($2,$4);
        } else {
            printf("Erreur de syntaxe: Erreur faire\n");
            exit(-1);

        }
    } else {

        printf("Erreur de syntaxe: Erreur tq\n");
        exit(-1);

    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}
n_instr *iapp() {
    n_instr *$$=NULL;
    n_appel *$1=NULL;
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_appelFct_,uniteeCourante)) {
        $1=appf();
        Ptvirgule();
        $$=cree_n_instr_appel($1);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}
n_instr *iret() {
    n_instr * $$=NULL;
    n_exp *$2=NULL;
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==RETOUR) {
        process();

        $2=exp();
        Ptvirgule();
        $$=cree_n_instr_retour($2);
    } else {
        printf("Erreur de syntaxe: Erreur Retour\n");
        exit(-1);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}

n_instr * iecr() {
    n_instr *$$=NULL;
    n_exp *$3=NULL;
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==ECRIRE) {
        process();

        if(uniteeCourante==PARENTHESE_OUVRANTE) {
            process();

            $3=exp();
            $$=cree_n_instr_ecrire($3);
            if(uniteeCourante==PARENTHESE_FERMANTE) {
                process();

                Ptvirgule();

            } else {
                printf("Erreur de syntaxe: Erreur parenthese fermante\n");
                exit(-1);
            }
        } else {
            printf("Erreur de syntaxe: Erreur parenthese ouvrante\n");
            exit(-1);
        }
    } else {
        printf("Erreur de syntaxe: Erreur ecrire\n");
        exit(-1);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}
n_instr * ivide() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    Ptvirgule();
    affiche_balise_fermante(__FUNCTION__,1);
    return cree_n_instr_vide();
}

void Ptvirgule() {
    if(uniteeCourante==POINT_VIRGULE) {
        process();

    } else {
        printf("Erreur de syntaxe : ; manquant\n");
        exit(-1);
    }

}




n_exp * exp() {
    n_exp *$$=NULL;
    n_exp *$1=NULL;
    n_exp *$2=NULL;
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_conjonction_,uniteeCourante)) {
        $1=conj();
        $$=expb($1);
        //$$=cree_n_exp_op(ou,$1,$2);
    } else {
        printf("Erreur de syntaxe : exp\n");
        exit(-1);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}
n_exp * expb(n_exp *h) {
    n_exp *$$=NULL;
    n_exp *$2=NULL;
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==OU) {
        process();
        $2=conj();
        $$=expb(cree_n_exp_op(ou,h,$2));

    } else {
        if(est_suivant(_expressionBis_,uniteeCourante)) {
            return h;
        } else {
            printf("Erreur de syntaxe \n");
            exit(-1);
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}
n_exp *conj() {
    n_exp *$$=NULL;
    n_exp *$1=NULL;
    n_exp *$2=NULL;
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_comparaison_,uniteeCourante)) {
        $1=comp();
        $$=conjb($1);
        //$$=cree_n_exp_op(et,$1,$2);
    } else {
        printf("Erreur de syntaxe : conj\n");
        exit(-1);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}
n_exp *conjb(n_exp *h) {
    n_exp *$$=NULL;
    n_exp *$2=NULL;
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==ET) {
        process();
        $2=comp();
        $$=conjb(cree_n_exp_op(et,h,$2));//erreur potentielle ici
    } else {
        if(est_suivant(_conjonctionBis_,uniteeCourante)) {
            return h;
        } else {
            printf("Erreur de syntaxe \n");
            exit(-1);
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}

n_exp *comp() {
    n_exp *$$ = NULL;
    n_exp *$1 = NULL;
    n_exp *$2 = NULL;
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_expArith_,uniteeCourante)) {
        $1 = e();
        $$ = compb($1);
        //$$ = cree_n_exp_op(op,$1,$2);
    } else {
        printf("Erreur de syntaxe : comp\n");
        exit(-1);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}

n_exp* compb(n_exp *h) {
    n_exp *$$ = NULL;
    n_exp *$2 = NULL;
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==EGAL||uniteeCourante==INFERIEUR||uniteeCourante==SUPERIEUR) {
        switch uniteeCourante{
    case EGAL:
        op=egal;
        break;
    case INFERIEUR:
        op=inf;
        break;
    case SUPERIEUR:
        op=sup;
        break;
    }
    op=!strcmp(yytext(),"=")
           ?egal:!strcmp(yytext(),"<")?inf:sup;
        process();
        $2 = e();
        $$ = compb(cree_n_exp_op(op, h, $2));
    } else {
        if(est_suivant(_comparaisonBis_,uniteeCourante)) {
            return h;
        } else {
            printf("Erreur de syntaxe \n");
            exit(-1);
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}

n_exp *e() {
    n_exp *$$ = NULL;
    n_exp *$2 = NULL;
    n_exp *$2 = NULL;
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_terme_,uniteeCourante)) {
        $1 = t();
        $$ = eb($1);
        //$$=cree_n_exp_op(op, $1, $2); //op?
    } else {
        printf("Erreur de syntaxe: exparith \n");
        exit(-1);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}

n_exp *eb(n_exp *h) {
    n_exp *$$ = NULL;
    n_exp *$2 = NULL;
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==PLUS||uniteeCourante==MOINS) {
        switch uniteeCourante{
    case PLUS:
        op=plus;
        break;
    case MOINS:
        op=moins;
        break;
    }

    process();
        $2 = t();
        $$ = eb(cree_n_exp_op(op, h, $2));
    } else {
        if(est_suivant(_expArithBis_,uniteeCourante)) {
            return h;
        } else {
            printf("Erreur de syntaxe \n");
            exit(-1);
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}
n_exp *t() {
    n_exp *$$ = NULL;
    n_exp *$1 = NULL;
    n_exp *$2 = NULL;
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_negation_,uniteeCourante)) {
        $1 = neg();
        $$ = tb($1);
        //$$ = cree_n_exp_op(op, $1, $2);
    } else {
        printf("Erreur de syntaxe: terme\n");
        exit(-1);
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}

n_exp *tb(n_exp *h) {
    n_exp *$$ = NULL;
    n_exp *$2 = NULL;
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==FOIS||uniteeCourante==DIVISE||uniteeCourante==MODULO) {
        switch uniteeCourante{
    case FOIS:
        op=fois;
        break;
    case DIVISE:
        op=divise;
        break;
    case MODULO:
        op=modulo;
        break;
    }
    process();
        $2 = neg();
        $$ = tb(cree_n_exp_op(op, h, $2));//op ?
    } else {
        if(est_suivant(_termeBis_,uniteeCourante)) {
            return h;
        } else {
            printf("Erreur de syntaxe \n");
            exit(-1);
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}

n_exp *neg() {
    n_exp *$$ = NULL;
    n_exp *$2 = NULL;

    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==NON) {
        process();
        $2 = neg();
        $$=cree_n_exp_op(negatif,$2,NULL);

    } else {
        if(est_premier(_facteur_,uniteeCourante)) {
            $$ = f();

        } else {
            printf("Erreur de syntaxe \n");
            exit(-1);

        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}

n_exp * f() {
    n_exp *$$=NULL;
    n_exp *$2=NULL;
    n_var *$3=NULL;
    n_appel *$4=NULL;

    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==PARENTHESE_OUVRANTE) {
        process();
        $$=exp();
        if(uniteeCourante==PARENTHESE_FERMANTE) {
            process();
        } else {
            printf("Erreur de syntaxe: parenthese fermante manquante\n");
            exit(-1);
        }
    } else {
        if(est_premier(_var_,uniteeCourante)) {
            $3=var();
            $$=cree_n_exp_var($3);
        } else {
            if(est_premier(_appelFct_,uniteeCourante)) {
                $4=appf();
                $$=cree_n_exp_appel($4);
            } else {
                if(uniteeCourante==LIRE) {
                    process();
                    $$=cree_n_exp_lire();
                    if(uniteeCourante==PARENTHESE_OUVRANTE) {
                        process();
                        if(uniteeCourante==PARENTHESE_FERMANTE) {
                            process();
                        } else {
                            printf("Erreur de syntaxe: parenthese fermante manquante\n");
                            exit(-1);
                        }
                    } else {
                        printf("Erreur de syntaxe: parenthese ouvrante manquante\n");
                        exit(-1);
                    }
                } else {
                    if(uniteeCourante==NOMBRE) {
                        $$=cree_n_exp_entier(atoi(yytext());
                                             process();

                    } else {
                        printf("Erreur de syntaxe: expression invalide\n");
                        exit(-1);
                    }
                }
            }
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return $$;
}


void var() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==ID_VAR) {
        process();

        oind();

    } else {
        printf("Erreur de syntaxe: Erreur var\n");
        exit(-1);
    }
    affiche_balise_fermante(__FUNCTION__,1);
}

void oind() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==CROCHET_OUVRANT) {
        process();

        exp();
        if(uniteeCourante==CROCHET_FERMANT) {
            process();


        } else {
            printf("Erreur de syntaxe: Erreur crochet fermant\n");
            exit(-1);
        }
    } else {
        if(est_suivant(_optIndice_,uniteeCourante)) {} else {
            {
                printf("Erreur de syntaxe\n");
                exit(-1);
            }
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return NULL;
}

void appf() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==ID_FCT) {
        process();

        if(uniteeCourante==PARENTHESE_OUVRANTE) {
            process();

            lexp();
            if(uniteeCourante==PARENTHESE_FERMANTE) {
                process();

            } else {
                printf("Erreur de syntaxe: Erreur parenthese fermante\n");
                exit(-1);
            }
        } else {
            printf("Erreur de syntaxe: Erreur parenthese ouvrante\n");
            exit(-1);
        }

    } else {
        printf("Erreur de syntaxe\n");
        exit(-1);
    }
    affiche_balise_fermante(__FUNCTION__,1);
}


void lexp() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_expression_,uniteeCourante)) {
        exp();
        lexpb();
    } else {
        if(est_suivant(_listeExpressions_,uniteeCourante)) {} else {
            printf("Erreur de syntaxe\n");
            exit(-1);

        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return NULL;
}

void lexpb() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==VIRGULE) {
        process();

        exp();
        lexpb();
    } else {
        if(est_suivant(_listeExpressionsBis_,uniteeCourante)) {} else {
            printf("Erreur de syntaxe\n");
            exit(-1);

        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
    return NULL;
}
