#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

int main()
{
    Pile * pile = NULL;

    for (int i = 0; i < 10; i++)
    {
        empiler(&pile, i);
    }

    afficher(pile);

    depiler(&pile);
    depiler(&pile);
    depiler(&pile);

    afficher(pile);

    echanger(&pile);
    afficher(pile);
}
