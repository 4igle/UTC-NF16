#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct element{
    int valeur;
    struct element *suivant;
}element;

typedef struct liste{
    element *tete;
}liste;

typedef struct monome{
    int coef;
    int degre;
    struct monome *suivant;
}monome;

typedef monome *polynome;


void ajout_element(liste *L, element *elt);
void difference_symetrique(liste *A, liste *B, liste *difference);
void afficher(liste L, char C);
polynome constructeur(int c, int d, polynome p);
int degre(polynome p);
polynome addition(polynome P1, polynome P2);
polynome produit_monome(int c, int d, polynome P);
polynome produit_polynome(polynome P1, polynome P2);
void affichage_monome(struct monome m);
void affichage_polynome(polynome p);



int main(){
    polynome p;
    p = NULL;
    p = constructeur(2, 6, p);
    p = constructeur(1, 5, p);
    p = constructeur(6, 4, p);
    p = constructeur(7, 3, p);

    polynome q;
    q = NULL;
    q = constructeur(4, 7, q);
    q = constructeur(2, 5, q);
    q = constructeur(4, 4, q);
    q = constructeur(6, 3, q);
    affichage_polynome(p);
    printf("\n");
    affichage_polynome(q);
    polynome z = produit_polynome(p, q);
    printf("\n");
    affichage_polynome(z);
    return 0;
}


int main2() {
    liste A, B, C;
    C.tete = NULL;


    element e1, e2, e3, e4, e5, e6, e7;
    A.tete = &e1;

    e1.suivant = &e2;
    e1.valeur = 1;

    e2.suivant = &e3;
    e2.valeur = 3;

    e3.suivant = &e4;
    e3.valeur = 5;

    e4.suivant = NULL;
    e4.valeur = 7;



    B.tete = &e5;

    e5.suivant = &e6;
    e5.valeur = 2;

    e6.suivant = &e7;
    e6.valeur = 5;

    e7.suivant = NULL;
    e7.valeur = 9;

    printf("Début : \n");
    afficher(A, 'A');
    afficher(B, 'B');
    afficher(C, 'C');
    printf("\nFonction : \n");

    difference_symetrique(&A, &B, &C);
    afficher(C, 'C');

    return 0;
}


void difference_symetrique(liste *A, liste *B, liste *difference){
    element *E;
    if (A->tete == NULL){
        while (B->tete != NULL){
            ajout_element(difference, B->tete);
            E = B->tete;
            B->tete = B->tete->suivant;
            E->suivant = NULL;
        }

        //printf("1");
        //afficher(*A, 'A');
        //afficher(*B, 'B');
        //afficher(*difference, 'C');
    }
    else if (B->tete == NULL){
        while (A->tete != NULL){
            ajout_element(difference, A->tete);
            E = A->tete;
            A->tete = A->tete->suivant;
            E->suivant = NULL;
        }

        //printf("2");
        //afficher(*A, 'A');
        //afficher(*B, 'B');
        //afficher(*difference, 'C');
    }
    else if (A->tete->valeur == B->tete->valeur){
        // on enlève le premier élément
        A->tete = A->tete->suivant;
        B->tete = B->tete->suivant;
        difference_symetrique(A, B, difference);

        //printf("3");
        //afficher(*A, 'A');
        //afficher(*B, 'B');
        //afficher(*difference, 'C');
    }
    else if(A->tete->valeur < B->tete->valeur){
        ajout_element(difference, A->tete);
        E = A->tete;
        A->tete = A->tete->suivant;
        E->suivant = NULL;
        difference_symetrique(A, B, difference);

        //printf("4");
        //afficher(*A, 'A');
        //afficher(*B, 'B');
        //afficher(*difference, 'C');
    }
    else{
        ajout_element(difference, B->tete);
        E = B->tete;
        B->tete = B->tete->suivant;
        E->suivant = NULL;
        difference_symetrique(A, B, difference);

        //printf("5");
        //afficher(*A, 'A');
        //afficher(*B, 'B');
        //afficher(*difference, 'C');
    }
}


void ajout_element(liste *L, element *elt){
    if (L->tete == NULL){
        L->tete = elt;
    }
    else{
        element *X = L->tete;
        while (X->suivant != NULL){
            X = X->suivant;
        }
        X->suivant = elt;
    }
}

void afficher(liste L, char C){
    element *X = L.tete;
    int i = 1;
    printf("\n%c\n", C);
    while (X != NULL){
        printf("[%d] : %d\n", i, X->valeur);
        X = X->suivant;
        i++;
    }
    printf("\n");

}

polynome constructeur(int c, int d, polynome p){
    polynome P1 = malloc(sizeof(monome));

    P1->coef = c;
    P1->degre = d;
    P1->suivant = p;

    return P1;
}

int degre(polynome p){
    int d = 0;
    while(p != NULL){
        if (p->degre > d){
            d = p->degre;
        }
        p = p->suivant;
    }
    return d;
}


polynome addition(polynome P1, polynome P2){
    if (P1 == NULL)
        return P2;

    if (P2 == NULL)
        return P1;

    if (P1->degre == P2->degre) {
        if (P1->coef + P2->coef == 0)
            return addition(P1->suivant, P2->suivant);
        return constructeur(P1->coef + P2->coef, P1->degre, addition(P1->suivant, P2->suivant));
    }

    if (P1->degre < P2->degre)
        return constructeur(P1->coef, P1->degre, addition(P1->suivant, P2));

    if (P1->degre > P2->degre)
        return constructeur(P2->coef, P2->degre, addition(P1, P2->suivant));


}

polynome produit_monome(int c, int d, polynome P){
    if (P == NULL)
        return NULL;
    return constructeur(c * P->coef, d + P->degre, produit_monome(c, d, P->suivant));
}

polynome produit_polynome(polynome P1, polynome P2){
    if (P1 == NULL || P2 == NULL)
        return NULL;

    return addition(produit_monome(P1->coef, P1->degre, P2), produit_polynome(P1->suivant, P2));
}

void affichage_monome(monome m){
    if (m.coef != 0){
        if (m.degre == 0){
            printf("%d", m.coef);
        }
        else
            if (m.coef == 1){
                if (m.degre == 1)
                    printf("x");
                else
                    printf("x^%d", m.degre);
            }
            else{
                if (m.degre == 1)
                    printf("%dx", m.coef);
                else
                    printf("%dx^%d", m.coef, m.degre);
            }
    }
}

void affichage_polynome(polynome p){
    if (p != NULL){
        monome m;
        m.coef = p->coef;
        m.degre = p->degre;
        affichage_monome(m);
        if (p->suivant != NULL && p->suivant->coef > 0){
            printf(" + ");
        }
        affichage_polynome(p->suivant);
    }
}
