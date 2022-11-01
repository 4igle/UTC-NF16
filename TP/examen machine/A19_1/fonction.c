#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

void empiler(Pile * pile, int valeur)
{
    if (pile == NULL)
    {
        return;
    }

    element * nouv = malloc(sizeof(element));
    if (nouv == NULL)
    {
        return;
    }
    nouv->valeur = valeur;

    nouv->suivant = *pile;
    *pile = nouv;
}

int depiler(Pile * pile)
{
    if (pile == NULL || *pile == NULL)
    {
        return -1;
    }

    element * premier = *pile;
    int val = premier->valeur;

    *pile = (*pile)->suivant;

    free(premier);
    return val;
}


void afficher(Pile pile)
{
    while (pile != NULL)
    {
        printf("%d ", pile->valeur);
        pile = pile->suivant;
    }
    printf("\n");
}

void echanger(Pile *pile)
{
    if (pile == NULL || *pile == NULL || (*pile)->suivant == NULL)
    {
        return;
    }

    element * premier = *pile;
    element * actuel = (*pile)->suivant;
    element * precedent = premier;

    while (actuel->suivant != NULL)
    {
        precedent = actuel;
        actuel = actuel->suivant;
    }

    precedent->suivant = premier;
    actuel->suivant = premier->suivant;
    premier->suivant = NULL;
    *pile = actuel;

}
