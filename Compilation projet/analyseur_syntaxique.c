#include"analyseur_syntaxique.h"
#include"symboles.h"
int uniteeCourante;

void process() {
    uniteeCourante=yylex();
    char* s;
    nom_token(uniteeCourante,s)
    printf("%s\n",s);

}




//Retourne uniteeCourante pour tester si FIN est detecte
int start() {
    process();
    initialise_premiers();
    initialise_suivants();
    //Axiome
    printf("Debut\n");

    pg();
    return uniteeCourante;
}
void pg() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_optDecVariables_,uniteeCourante)||est_premier(_listeDecFonctions_,uniteeCourante)||est_suivant(_programme_,uniteeCourante)) {

        odv();
        ldf();
    }
    affiche_balise_fermante(__FUNCTION__,1);
}

void odv() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_listeDecVariables_,uniteeCourante)) {
        ldv();
        Ptvirgule();
    } else {
        if(est_suivant(_optDecVariables_,uniteeCourante)) {
            return;
        } else {
            affiche_balise_fermante(__FUNCTION__,1);
            printf("Erreur de syntaxe\n");
            exit(-1);
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
}

void ldv() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_declarationVariable_,uniteeCourante)) {
        dv();
        ldvb();
    } else {
        if(est_suivant(_listeDecVariables_,uniteeCourante)) {} else {
        printf("Erreur de syntaxe\n");
            exit(-1);
        }
    }//TODO tester erreur potentielle ici
    /*else {
        printf("Erreur de syntaxe\n");
        exit(-1);
    }*/
    affiche_balise_fermante(__FUNCTION__,1);
}

void ldvb() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==VIRGULE) {
        process();

        dv();
        ldvb();
    } else {
        if(est_suivant(_listeDecVariablesBis_,uniteeCourante)) {

        } else {
            affiche_balise_fermante(__FUNCTION__,1);
            printf("Erreur de syntaxe\n");
            exit(-1);
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
}


void dv() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==ENTIER) {
        process();

        if(uniteeCourante==ID_VAR) {
            process();

            ott();
        }
    } else {
        affiche_balise_fermante(__FUNCTION__,1);
        printf("Erreur de syntaxe: Declaration de variable incorrecte\n");
        exit(-1);

    }
    affiche_balise_fermante(__FUNCTION__,1);

}

void ott() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==CROCHET_OUVRANT) {
        process();


        if(uniteeCourante==NOMBRE) {
            process();

            if(uniteeCourante==CROCHET_FERMANT) {
                process();

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

        } else {
            printf("Erreur de syntaxe\n");
            exit(-1);
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);

}

void ldf() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_declarationFonction_,uniteeCourante)) {
        df();
        ldf();
    } else {
        if(est_suivant(_listeDecFonctions_,uniteeCourante)) {} else {
            printf("Erreur de syntaxe\n");
            exit(-1);
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
}

void df() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==ID_FCT) {
        process();

        lp();
        odv();
        ib();
    } else {
        printf("Erreur de syntaxe: id_fct\n");
        exit(-1);
    }
    affiche_balise_fermante(__FUNCTION__,1);
}

void lp() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==PARENTHESE_OUVRANTE) {
        process();

        oldv();
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
}


void oldv() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_listeDecVariables_,uniteeCourante)||est_suivant(_optListeDecVariables_,uniteeCourante)) {
        ldv();
    } else {
        printf("Erreur de syntaxe\n");
        exit(-1);
    }
    affiche_balise_fermante(__FUNCTION__,1);
}

void i() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_instructionAffect_,uniteeCourante)) {
        iaff();

    } else {
        if(est_premier(_instructionBloc_,uniteeCourante)) {
            ib();

        } else {
            if(est_premier(_instructionSi_,uniteeCourante)) {
                isi();

            } else {
                if(est_premier(_instructionTantque_,uniteeCourante)) {
                    itq();

                } else {
                    if(est_premier(_instructionAppel_,uniteeCourante)) {
                        iapp();

                    } else {
                        if(est_premier(_instructionRetour_,uniteeCourante)) {
                            iret();

                        } else {
                            if(est_premier(_instructionEcriture_,uniteeCourante)) {
                                iecr();

                            } else {
                                if(est_premier(_instructionVide_,uniteeCourante)) {
                                    ivide();

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
}


void iaff() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_var_,uniteeCourante)) {
        var();

        if(uniteeCourante==EGAL) {
            process();

            exp();
            Ptvirgule();
        } else {
            printf("Erreur de syntaxe ligne no %d: Erreur affectation\n",yylineno());
            exit(-1);
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
}

void ib() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==ACCOLADE_OUVRANTE) {
        process();

        li();
        if(uniteeCourante==ACCOLADE_FERMANTE) {
            process();

        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
}

void li() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_instruction_,uniteeCourante)) {
        i();
        li();
    } else {
        if(est_suivant(_listeInstructions_,uniteeCourante)) {} else {
            printf("Erreur de syntaxe\n");
            exit(-1);
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
}

void isi() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==SI) {
        process();

        exp();
        if(uniteeCourante==ALORS) {
            process();

            ib();
            osinon();
        } else {
            printf("Erreur de syntaxe: Erreur alors\n");
            exit(-1);
        }
    } else {
        printf("Erreur de syntaxe: Erreur si\n");
        exit(-1);
    }
    affiche_balise_fermante(__FUNCTION__,1);
}

void osinon() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==SINON) {
        process();

        ib();
    } else {
        if(est_suivant(_optSinon_,uniteeCourante)) {} else {
            printf("Erreur de syntaxe\n");
            exit(-1);
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
}
void itq() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==TANTQUE) {
        process();

        exp();
        if(uniteeCourante==FAIRE) {
            process();

            ib();
        } else {
            printf("Erreur de syntaxe: Erreur faire\n");
            exit(-1);

        }
    } else {

        printf("Erreur de syntaxe: Erreur tq\n");
        exit(-1);

    }
    affiche_balise_fermante(__FUNCTION__,1);
}
void iapp() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_appelFct_,uniteeCourante)) {
        appf();
        Ptvirgule();
    }
    affiche_balise_fermante(__FUNCTION__,1);
}
void iret() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==RETOUR) {
        process();

        exp();
        Ptvirgule();
    } else {
        printf("Erreur de syntaxe: Erreur Retour\n");
        exit(-1);
    }
    affiche_balise_fermante(__FUNCTION__,1);
}

void iecr() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==ECRIRE) {
        process();

        if(uniteeCourante==PARENTHESE_OUVRANTE) {
            process();

            exp();
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
}
void ivide() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    Ptvirgule();
    affiche_balise_fermante(__FUNCTION__,1);
}

void Ptvirgule() {
    //affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==POINT_VIRGULE) {
        process();

    } else {
        printf("Erreur de syntaxe : ; manquant\n");
        exit(-1);
    }
    //affiche_balise_fermante(__FUNCTION__,1);
}




void exp() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_conjonction_,uniteeCourante)) {
        conj();
        expb();
    } else {
        printf("Erreur de syntaxe : exp\n");
        exit(-1);
    }
    affiche_balise_fermante(__FUNCTION__,1);
}
void expb() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==OU) {
        process();
        conj();
        expb();
    } else {
        if(est_suivant(_expressionBis_,uniteeCourante)) {} else {
            printf("Erreur de syntaxe \n");
            exit(-1);
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
}
void conj() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_comparaison_,uniteeCourante)) {
        comp();
        conjb();
    } else {
        printf("Erreur de syntaxe : conj\n");
        exit(-1);
    }
    affiche_balise_fermante(__FUNCTION__,1);
}
void conjb() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==ET) {
        process();
        comp();
        conjb();
    } else {
        if(est_suivant(_conjonctionBis_,uniteeCourante)) {} else {
            printf("Erreur de syntaxe \n");
            exit(-1);
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
}

void comp() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_expArith_,uniteeCourante)) {
        e();
        compb();
    } else {
        printf("Erreur de syntaxe : comp\n");
        exit(-1);
    }
    affiche_balise_fermante(__FUNCTION__,1);
}

void compb() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==EGAL||uniteeCourante==INFERIEUR) {
        process();
        e();
        compb();
    } else {
        if(est_suivant(_comparaisonBis_,uniteeCourante)) {} else {
            printf("Erreur de syntaxe \n");
            exit(-1);
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
}

void e() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_terme_,uniteeCourante)) {
        t();
        eb();
    } else {
        printf("Erreur de syntaxe: exparith \n");
        exit(-1);
    }
    affiche_balise_fermante(__FUNCTION__,1);
}
void eb() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==PLUS||uniteeCourante==MOINS) {
        process();
        t();
        eb();
    } else {
        if(est_suivant(_expArithBis_,uniteeCourante)) {} else {
            printf("Erreur de syntaxe \n");
            exit(-1);
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
}
void t() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(est_premier(_negation_,uniteeCourante)) {
        neg();
        tb();
    } else {
        printf("Erreur de syntaxe: terme\n");
        exit(-1);
    }
    affiche_balise_fermante(__FUNCTION__,1);
}
void tb() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==FOIS||uniteeCourante==DIVISE) {
        process();
        neg();
        tb();
    } else {
        if(est_suivant(_termeBis_,uniteeCourante)) {} else {
            printf("Erreur de syntaxe \n");
            exit(-1);
        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
}

void neg() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==NON) {
        process();
        neg();
    } else {
        if(est_premier(_facteur_,uniteeCourante)) {
            f();
        } else {
            printf("Erreur de syntaxe \n");
            exit(-1);

        }
    }
    affiche_balise_fermante(__FUNCTION__,1);
}

void f() {
    affiche_balise_ouvrante(__FUNCTION__,1);
    if(uniteeCourante==PARENTHESE_OUVRANTE) {
        process();
        exp();
        if(uniteeCourante==PARENTHESE_FERMANTE) {
            process();
        } else {
            printf("Erreur de syntaxe: parenthese fermante manquante\n");
            exit(-1);
        }
    } else {
        if(est_premier(_var_,uniteeCourante)) {
            var();
        } else {
            if(est_premier(_appelFct_,uniteeCourante)) {
                appf();
            } else {
                if(uniteeCourante==LIRE) {
                    process();
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
}
