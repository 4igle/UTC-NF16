#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"


element * creer_element(int val)
{
    element * nouv = malloc(sizeof(element));
    if (nouv != NULL)
    {
        nouv->suivant = NULL;
        nouv->valeur = val;
    }
    return nouv;
}

void ajouter_element(liste * l, element * n)
{
    if (l == NULL || n == NULL)
    {
        return;
    }

    if (*l == NULL)
    {
        *l = n;
        return;
    }

    element * actuel = *l;

    if (n->suivant != NULL)
    {
        n->suivant = NULL;
    }

    while (actuel->suivant != NULL)
    {
        actuel = actuel->suivant;
    }
    actuel->suivant = n;
}

liste construire_liste()
{
    int rep = 1;
    int val;
    element * n = NULL;
    liste l = NULL;

    while (rep != 0)
    {
        printf("Entrez une valeur : ");
        scanf("%d", &val);

        n = creer_element(val);
        if (n == NULL)
        {
            printf("Erreur allocation memoire\n");
            return NULL;
        }

        ajouter_element(&l, n);

        printf("\nVoulez vous continuer ? (0/1) : ");
        scanf("%d", &rep);
        printf("\n");
    }
    return l;
}

void afficher_liste(liste l)
{
    if (l == NULL)
    {
        printf("La liste est vide \n");
    }

    printf("[");
    while (l != NULL)
    {
        printf("%d", l->valeur);
        if (l->suivant != NULL)
        {
            printf(", ");
        }
        l = l->suivant;
    }
    printf("]\n");
}

liste inverser_liste(liste l)
{
    if (l != NULL)
    {
        element * n = l;
        l = inverser_liste(l->suivant);
        ajouter_element(&l, n);
    }
    return l;
}


void tri(liste *l)
{
    if (l == NULL || *l == NULL)
    {
        return;
    }

    int changement = 0;
    element * precedent;
    element * actuel;
    element * tmp;

    do
    {
        precedent = NULL;
        actuel = *l;
        changement = 0;

        while (actuel->suivant != NULL)
        {
            if (actuel->valeur > actuel->suivant->valeur)
            {
                changement = 1;
                if (precedent == NULL)
                {
                    tmp = actuel->suivant;
                    *l = actuel->suivant;
                    actuel->suivant = actuel->suivant->suivant;
                    tmp->suivant = actuel;
                    precedent = tmp;
                }
                else
                {
                    tmp = actuel->suivant;
                    precedent->suivant = actuel->suivant;
                    actuel->suivant = actuel->suivant->suivant;
                    tmp->suivant = actuel;
                    precedent = tmp;
                }
            }
            else
            {
                precedent = actuel;
                actuel = actuel->suivant;
            }
        }
    } while (changement != 0);
}

/*==============================================================================================*/

noeud * creer_noeud(int val)
{
    noeud * nouv = malloc(sizeof(noeud));
    if (nouv != NULL)
    {
        nouv->gauche = NULL;
        nouv->droite = NULL;
        nouv->valeur = val;
    }
    return nouv;
}

void ajouter_noeud(arbre * a, noeud * n)
{
    if (a == NULL || n == NULL)
    {
        return;
    }

    if (*a == NULL)
    {
        *a = n;
        return;
    }

    noeud * pere = NULL;
    noeud * actuel = *a;

    while (actuel != NULL)
    {
        if (actuel->valeur == n->valeur)
        {
            printf("Erreur, le noeud est deja dans l'arbre");
            return;
        }
        if (actuel->valeur > n->valeur)
        {
            pere = actuel;
            actuel = actuel->gauche;
        }
        else
        {
            pere = actuel;
            actuel = actuel->droite;
        }
    }
    if (pere->valeur > n->valeur)
    {
        pere->gauche = n;
    }
    else
    {
        pere->droite = n;
    }
}

arbre construire_arbre()
{
    int rep = 1;
    int val;
    noeud * n = NULL;
    arbre a = NULL;

    while (rep != 0)
    {
        printf("Entrez une valeur : ");
        scanf("%d", &val);

        n = creer_element(val);
        if (n == NULL)
        {
            printf("Erreur allocation memoire\n");
            return NULL;
        }

        ajouter_noeud(&a, n);

        printf("\nVoulez vous continuer ? (0/1) : ");
        scanf("%d", &rep);
        printf("\n");
    }
    return a;
}

void afficher_arbre(arbre a)
{
    if (a != NULL)
    {
        afficher_arbre(a->gauche);
        printf("%d, ", a->valeur);
        afficher_arbre(a->droite);
    }
}

void afficher_arbre_propre(arbre a)
{
    if (a == NULL)
    {
        printf("_");
        return;
    }
    printf("(");
    afficher_arbre_propre(a->gauche);
    printf(", %d,", a->valeur);
    afficher_arbre_propre(a->droite);
    printf(")");
}


int nombre_feuilles(arbre a)
{
    if (a != NULL)
    {
        if (a->gauche == NULL && a->droite == NULL)
        {
            return 1;
        }
        else
        {
            return nombre_feuilles(a->gauche) + nombre_feuilles(a->droite);
        }
    }
    return 0;
}

int nombre_noeuds(arbre a)
{
    if (a != NULL)
    {
        return nombre_noeuds(a->gauche) + nombre_noeuds(a->droite) + 1;
    }
    return 0;
}

int nombre_noeuds_internes(arbre a)
{
    if (a != NULL)
    {
        return nombre_noeuds(a) - nombre_feuilles(a) - 1;
    }
    return 0;
}

int hauteur(arbre a)
{
    if (a == NULL)
    {
        return -1;
    }

    int gauche = hauteur(a->gauche);
    int droite = hauteur(a->droite);

    if (gauche > droite)
    {
        return gauche + 1;
    }
    return droite + 1;
}
