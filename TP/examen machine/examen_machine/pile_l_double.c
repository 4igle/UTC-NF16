#include <stdio.h>
#include <stdlib.h>
#include "pile_l_double.h"
#include <time.h>

Noeud * creerNoeud(int cle){
    Noeud * nouv = malloc(sizeof(Noeud));
    if (nouv != NULL)
    {
        nouv->valeur = cle;
        nouv->precedent = NULL;
        nouv->suivant = NULL;
    }
    return nouv;
}

void supprimerNoeud(Noeud * noeud){
    if (noeud != NULL)
    {
        noeud->suivant->precedent = noeud->precedent;
        noeud->precedent->suivant = noeud->suivant;
        free(noeud);
    }
}

Liste * creerListeVide(){
    Liste * nouv = malloc(sizeof(Liste));
    if (nouv != NULL)
    {
        Noeud * sentinelle = creerNoeud(-1);
        if (sentinelle != NULL)
        {
            sentinelle->precedent = sentinelle;
            sentinelle->suivant = sentinelle;
            nouv->sentinelle = sentinelle;
            nouv->queue = NULL;
            nouv->tete = NULL;
        }
        else
        {
            free(nouv);
            return NULL;
        }
    }
    return nouv;
}

void afficherContenuListe(Liste * liste){
    if (liste == NULL)
    {
        return;
    }
    Noeud * actuel = liste->tete;
    printf("\nContenu de la liste : \n");
    while (actuel != liste->sentinelle)
    {
        printf("%d\n", actuel->valeur);
        actuel = actuel->suivant;
    }
}

int listeVide(Liste *liste){
    return (liste == NULL || liste->tete == NULL);
}

void viderListe(Liste * liste){
    if (liste == NULL || listeVide(liste))
    {
        return;
    }
    Noeud * actuel = liste->tete;
    Noeud * temp = NULL;
    while (actuel != liste->sentinelle)
    {
        temp = actuel;
        actuel = actuel->suivant;
        free(temp);
    }
    liste->queue = NULL;
    liste->tete = NULL;
}

void ajouterQueueListe(Liste * liste, int cle){
    if (liste == NULL)
    {
        return;
    }
    Noeud * noeud = creerNoeud(cle);
    if (noeud != NULL)
    {
        if (liste->queue == NULL && liste->tete == NULL)
        {
            liste->queue = noeud;
            liste->tete = noeud;

            liste->sentinelle->suivant = noeud;
            liste->sentinelle->precedent = noeud;

            noeud->precedent = liste->sentinelle;
            noeud->suivant = liste->sentinelle;
            return;
        }

        liste->queue->suivant = noeud;
        noeud->precedent = liste->queue;

        liste->sentinelle->precedent = noeud;
        noeud->suivant = liste->sentinelle;

        liste->queue = noeud;
    }
}

Noeud * obtenirDernierElement(Liste * liste)
{
    if (listeVide(liste))
    {
        return NULL;
    }
    return liste->queue;
}

void supprimerListe(Liste * liste)
{
    if (liste == NULL)
    {
        return;
    }
    viderListe(liste);
    free(liste);
}

int depiler(Liste * pile){
    if (pile == NULL)
    {
        return -1;
    }
    Noeud * dernier = obtenirDernierElement(pile);
    if (dernier == NULL)
    {
        return -1;
    }

    int val = dernier->valeur;

    if (dernier->precedent != pile->sentinelle)
    {
        pile->queue = dernier->precedent;
    }
    else
    {
        pile->queue = NULL;
        pile->tete = NULL;
    }

    supprimerNoeud(dernier);
    return val;
}

void empiler(Liste * pile, int val){
    if (pile == NULL)
    {
        return;
    }
    ajouterQueueListe(pile, val);
}

/*=======================================================================================*/
/*=======================================================================================*/
/*=======================================================================================*/

void inserer(ListElem **liste, int val, int pos){

    if (liste = NULL || pos < 0)
    {
        return;
    }

    ListElem * nouv = malloc(sizeof(ListElem));
    if (nouv == NULL)
    {
        return;
    }
    nouv->data = val;
    ListElem * precedent = NULL;
    ListElem * actuel = *liste;

    if (actuel == NULL)
    {
        if (pos == 0)
        {
            *liste = nouv;
        }
        else
        {
            return;
        }
    }
    else
    {
        int i = 0;
        while(i < pos && actuel != NULL)
        {
            precedent = actuel;
            actuel = actuel->next;
            i++;
        }
        if (i != pos)
        {
            return;
        }
        if (precedent == NULL)
        {
            nouv->next = *liste;
            nouv->prev = NULL;
            (*liste)->prev = nouv;
            *liste = nouv;
        }
        else
        {
            nouv->next = actuel;
            nouv->prev = precedent;
            precedent->next = nouv;
            if (actuel != NULL)
            {
                actuel->prev = nouv;
            }
        }
    }
}


void affichertout(ListElem *L){

    ListElem * actuel = L;

    while(actuel != NULL)
    {
        printf("%d\n", actuel->data);
        actuel = actuel->next;
    }
}

int nombrelement(ListElem *L){

    ListElem * actuel = L;

    int i = 0;

    while(actuel != NULL)
    {
        i++;
        actuel = actuel->next;
    }

    return i;
}

/*========================================================================================================*/

unsigned int lireExpression(char * expression){
    int i = 0;
    int nb = 0;
    int a = 0;
    int b = 0;
    int res = 0;
    Liste * pile = creerListeVide();
    while (expression[i] != '\0')
    {
        if (expression[i] >= '0' && expression[i] <= '9')
        {
            nb = 0;
            while (expression[i] >= '0' && expression[i] <= '9')
            {
                nb *= 10;
                nb += expression[i] - '0';
                i++;
            }
            empiler(pile, nb);
        }
        else
        {
            if (expression[i] != ' ')
            {
                a = depiler(pile);
                b = depiler(pile);
                switch(expression[i])
                {
                    case '+':
                        res = a + b;
                        break;
                    case '-':
                        res = a - b;
                        break;
                    case '*':
                        res = a * b;
                        break;
                    case '/':
                        res = a / b;
                        break;
                }
                printf("%d %c %d -> %d;\n", a, expression[i], b, res);
                empiler(pile, res);
            }
            i++;
        }

    }

    return depiler(pile);
}


