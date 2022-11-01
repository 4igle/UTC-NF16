#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

#define NMAX 10

typedef float ligne[NMAX];
typedef ligne matrice[NMAX];
typedef struct tonneau{
    float d;
    float D;
    float L;
    char contenant[NMAX];
} tonneau;

float volume(tonneau t);
int fact1(int n);
int fact2(int n);
int fibo1(int n);
int fibo2(int n);
void affichage(matrice m, int n);
void lecture(matrice m, int *n);
float determinant(matrice m, int dim);
void sous_copie(matrice m, matrice dest, int dim, int ligne_eviter);
void afficher_tonneau(tonneau t);

#endif // FONCTIONS_H_INCLUDED
