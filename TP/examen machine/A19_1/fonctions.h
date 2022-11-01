#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

typedef struct element{
    int valeur;
    struct element * suivant;
}element;

typedef element * Pile;

void empiler(Pile * pile, int valeur);
int depiler(Pile * pile);
void afficher(Pile pile);
void echanger(Pile *pile);

#endif // FONCTIONS_H_INCLUDED
