#include <stdio.h>
#include <stdlib.h>
#include "abr.h"

int max(arbre a)
{
    if (a != NULL)
    {
        return 0;
    }

    while(a->droit != NULL)
    {
        a->droit;
    }
    return a->valeur;
}

int min(arbre a)
{
    if (a != NULL)
    {
        return 0;
    }

    while(a->gauche != NULL)
    {
        a->gauche;
    }
    return a->valeur;
}


//==============================================================//

res * create_reservation(int beg, int end)
{
    if (beg < 1 || end < 1 || beg > 31 || end > 31 || end < beg)
    {
        return NULL;
    }

    res * nouv = malloc(sizeof(res));
    if (nouv != NULL)
    {
        nouv->beg = beg;
        nouv->end = end;
        nouv->gauche = NULL;
        nouv->droit = NULL;
        nouv->pere = NULL;
    }
    return nouv;
}

res * mini(res * root)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->gauche == NULL)
    {
        return root;
    }
    return mini(root->gauche);
}

void delete_reservation(res *root, res * r)
{
    if (root == NULL || r == NULL)
    {
        return;
    }

    res * pere = r->pere;
    res * fils = NULL;
    if (r->droit == NULL && r->gauche == NULL) // aucun fils
    {
        if (pere->droit == r)
        {
            pere->droit = NULL;
        }
        else
        {
            pere->gauche = NULL;
        }
        free(r);
    }
    else
    {
        if (r->droit != NULL && r->gauche != NULL) //deux fils
        {
            fils = mini(r->droit);
            res * nfils = create_reservation(fils->beg, fils->end);

            delete_reservation(r->droit, fils);

            nfils->pere = pere;
            nfils->gauche = r->gauche;
            nfils->droit = r->droit;

            if (r->droit != NULL)
            {
                r->droit->pere = nfils;
            }
            r->gauche->pere = nfils;

            if (pere != NULL && pere->droit == r)
            {
                pere->droit = nfils;
            }
            else if (pere != NULL && pere->gauche == r)
            {
                pere->gauche = nfils;
            }
            free(r);
        }
        else // un seul fils
        {
            if (r->droit != NULL)
            {
                fils = r->droit;
            }
            else
            {
                fils = r->gauche;
            }
            fils->pere = pere;
            if (pere->droit == r)
            {
                pere->droit = fils;
            }
            else
            {
                pere->gauche = fils;
            }
            free(r);
        }
    }

}

res * add_reservation(res * root, res * r)
{
    if (root == NULL || r == NULL)
    {
        return NULL;
    }

    res * actuel = root;

    while(actuel != NULL)
    {
        if (r->end < actuel->beg)
        {
            if (actuel->gauche == NULL)
            {
                actuel->gauche = r;
                r->pere = actuel;
                return r;
            }
            actuel = actuel->gauche;
        }
        else if (r->beg > actuel->end)
        {
            if (actuel->droit == NULL)
            {
                actuel->droit = r;
                r->pere = actuel;
                return r;
            }
            actuel = actuel->droit;
        }
        else
        {
            return NULL;
        }
    }
    return NULL;
}

res * search_reservation(res * root, res * r)
{
    if (root == NULL || r == NULL)
    {
        return NULL;
    }

    res * actuel = root;
    while(actuel != NULL)
    {
        if (r->end < actuel->beg)
        {
            if (actuel->gauche == NULL)
            {
                return NULL;
            }
            actuel = actuel->gauche;
        }
        else if (r->beg > actuel->end)
        {
            if (actuel->droit == NULL)
            {
                return NULL;
            }
            actuel = actuel->droit;
        }
        else if (r->beg == actuel->beg && r->end == actuel->end)
        {
            return actuel;
        }
        else
        {
            return NULL;
        }
    }
    return NULL;
}


void print_reservations(res * root, int order)
{
    if (root == NULL || (order != 0 && order != 1))
    {
        return;
    }

    if (order == 0)
    {
        print_reservations(root->gauche, order);
        printf("[%d,%d]\n", root->beg, root->end);
        print_reservations(root->droit, order);
    }
    else
    {
        print_reservations(root->droit, order);
        printf("[%d,%d]\n", root->beg, root->end);
        print_reservations(root->gauche, order);
    }
}

void real_print(res * root)
{
    if (root == NULL)
    {
        printf("_");
        return;
    }

    printf("(");
    real_print(root->gauche);
    printf(", [%d,%d],", root->beg, root->end);
    real_print(root->droit);
    printf(")");

}
