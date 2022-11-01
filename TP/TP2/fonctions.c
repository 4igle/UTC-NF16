#include "fonctions.h"



typedef struct Un_Tableau_Entier{
    int ncase;
    int tab[NMAX];
} Un_Tableau_Entier;


typedef struct menu{
    char c[20][60];
    int n;
} menu;

float volume(tonneau t){
    tonneau *ptr = &t;
    float longueur = t.L;
    float pDiametre = (*ptr).d;
    float gDiemetre = ptr->D;
    float x = 3.14159 * longueur;
    float y = pDiametre/2.0 + (2.0/3.0) * (gDiemetre/2.0 - pDiametre/2.0);
    y *= y;
    return x * y;
}

void afficher_tonneau(tonneau t){
    printf("Petit diametre : %f\nGrand diametre : %f\nLongueur : %f\nVolume : %f\nContenant : %s\n\n", t.d, t.D, t.L, volume(t), t.contenant);
}



int fact1(int n){

    // cas particuliers
    if (n < 0){
        printf("Impossible");
        return 0;
    }
    if (n == 1 || n == 0){
        return 1;
    }

    int fact = 1;
    for (int i = 2; i <= n; i++){
        fact *= i;
    }
    return fact;
}

int fact2(int n){

    // cas particuliers
    if (n < 0){
        printf("Impossible");
        return 0;
    }
    if (n == 1 || n == 0){
        return 1;
    }

    return n * fact2(n-1);
}

void lecture(matrice m, int *n){
    int ligne, colonne;
    float f;
    printf("Entrez la dimension de la matrice : ");
    scanf("%d", n);

    for (ligne = 0; ligne < *n; ligne++){
        for (colonne = 0; colonne < *n; colonne++){
            printf("Entrez élément [%d][%d] : ", ligne, colonne);
            scanf("%f", &f);
            printf("\n");
            m[ligne][colonne] = f;
        }
    }
}

void affichage(matrice m, int n){
    int ligne, colonne;

    for (ligne = 0; ligne < n; ligne++){
        for (colonne = 0; colonne < n; colonne++){
            printf("%5.2f ", m[ligne][colonne]);
        }
        printf("\n");
    }
}


float determinant(matrice m, int dim){
    if (dim < 1) return -1;
    if (dim == 1) return (m[0][0]);
    int ligne;
    int signe = 1;
    matrice sous_matrice;
    float det = 0;


    for (ligne = 0; ligne < dim; ligne++){
        sous_copie(m, sous_matrice, dim, ligne);
        det += signe*m[ligne][0]*determinant(sous_matrice, dim-1);
        signe = -signe;
    }
    return det;
}

void sous_copie(matrice m, matrice dest, int dim, int ligne_eviter){
    int ligne, colonne;
    int ligne_dest = 0;

    for (ligne = 0; ligne < dim; ligne++){
        if (ligne != ligne_eviter){
            for (colonne = 1; colonne < dim; colonne++){
                dest[ligne_dest][colonne-1] = m[ligne][colonne];
            }
            ligne_dest++;
        }
    }
}


int fibo1(int n){
    if (n < 0) return -1;
    if (n == 0 || n == 1) return n;
    return fibo1(n-1) + fibo1(n-2);
}

int fibo2(int n){
    if (n < 0)
        return -1;
    if (n == 0 || n == 1)
        return n;
    if ((n % 2) == 0)
    {
        int x = fibo2(n/2);
        return x*x + 2 * fibo2(n/2 - 1) * fibo2(n/2);
    }
    int x = fibo2((n-1)/2);
    int y = fibo2((n-1)/2 + 1);
    return x*x + y*y;
}
