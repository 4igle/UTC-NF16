#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"

int main1()
{
    liste l = construire_liste();
    afficher_liste(l);
    tri(&l);
    //l = inverser_liste(l);
    afficher_liste(l);
    return 0;
}

int main()
{
    arbre a = construire_arbre();
    afficher_arbre(a);
    printf("\n\n");
    afficher_arbre_propre(a);
    printf("\nNb feuilles : %d\nNb noeuds interne : %d\nHauteur : %d\n", nombre_feuilles(a), nombre_noeuds_internes(a), hauteur(a));
    return 0;
}
