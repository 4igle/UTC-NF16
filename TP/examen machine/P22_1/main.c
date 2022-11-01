#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"

int main()
{
    T_Arbre arbre = NULL;
    insererSommet(&arbre, 6);
    insererSommet(&arbre, 1);
    insererSommet(&arbre, 3);
    insererSommet(&arbre, 2);
    insererSommet(&arbre, 4);
    insererSommet(&arbre, 0);
    insererSommet(&arbre, 9);
    insererSommet(&arbre, 5);
    insererSommet(&arbre, 2);
    insererSommet(&arbre, 10);
    insererSommet(&arbre, 8);
    insererSommet(&arbre, 11);
    insererSommet(&arbre, -1);

    afficherArbre(arbre);
    printf("\n\n");

    supprimerSommet(&arbre, -1);

    afficherArbre(arbre);

    printf("Hauteur : %d\n\n", hauteurArbre(arbre));

    viderArbre(&arbre);

    afficherArbre(arbre);
    return 0;
}
