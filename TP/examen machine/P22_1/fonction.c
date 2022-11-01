#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"
#include <string.h>

T_Liste ajouter(T_Liste maListe, char * nom, char * prenom, char * code_postal, int nb_p)
{
    if (nom == NULL || prenom == NULL || code_postal == NULL || nb_p < 0)
    {
        return NULL;
    }

    T_Client * nouv = malloc(sizeof(T_Client));
    if (nouv == NULL)
    {
        return NULL;
    }

    nouv->nom = malloc(sizeof(nom));
    nouv->prenom = malloc(sizeof(prenom));
    nouv->code_postal = malloc(sizeof(code_postal));

    strcpy(nouv->nom, nom);
    strcpy(nouv->prenom, prenom);
    strcpy(nouv->code_postal, code_postal);

    nouv->suivant = NULL;
    nouv->nb_passages = nb_p;

    T_Client * actuel = maListe;

    if (actuel == NULL)
    {
        return nouv;
    }

    T_Client * precedent = NULL;

    while ((actuel != NULL) && (strcmp(nouv->nom, actuel->nom) > 0 || strcmp(nouv->prenom, actuel->prenom) > 0))
    {
        precedent = actuel;
        actuel = actuel->suivant;
    }

    if (actuel != NULL && strcmp(nouv->nom, actuel->nom) == 0 && strcmp(nouv->prenom, actuel->prenom) == 0)
    {
        actuel->nb_passages += nouv->nb_passages;
        free(nouv);
        return maListe;
    }

    if (precedent == NULL)
    {
        nouv->suivant = maListe;
        return nouv;
    }
    else
    {
        nouv->suivant = actuel;
        precedent->suivant = nouv;
        return maListe;
    }
}

T_Liste supprimer(T_Liste maListe, char * nom, char * prenom)
{
    if (maListe == NULL)
    {
        return maListe;
    }


    T_Client * precedent = NULL;
    T_Client * actuel = maListe;

    while ((actuel != NULL) && (strcmp(nom, actuel->nom) > 0 || strcmp(prenom, actuel->prenom) > 0))
    {
        precedent = actuel;
        actuel = actuel->suivant;
    }

    if (actuel == NULL)
    {
        return maListe;
    }

    if (strcmp(nom, actuel->nom) != 0 || strcmp(prenom, actuel->prenom) != 0)
    {
        return maListe;
    }

    if (precedent == NULL)
    {
        maListe = maListe->suivant;
        free(actuel);
        return maListe;
    }
    else
    {
        precedent->suivant = actuel->suivant;
        free(actuel);
        return maListe;
    }

}


void affichage(T_Liste maListe)
{
    if (maListe == NULL)
    {
        printf("La liste est vide ! \n\n");
        return;
    }

    while (maListe != NULL)
    {
        printf("Nom : %s\nPrenom : %s\nCode Postal : %s\nNombre Passages : %u\n\n", maListe->nom, maListe->prenom, maListe->code_postal, maListe->nb_passages);
        maListe = maListe->suivant;
    }
}

void vider(T_Liste maListe)
{
    while (maListe != NULL)
    {
        maListe = supprimer(maListe, maListe->nom, maListe->prenom);
    }
}


/*=====================================================================================================================*/


void insererSommet(T_Arbre * arbre, int val)
{
    if (arbre == NULL)
    {
        return;
    }

    T_Sommet * nouv = malloc(sizeof(T_Sommet));

    if (nouv == NULL)
    {
        return;
    }

    nouv->cle = val;
    nouv->fils_gauche = NULL;
    nouv->fils_droit = NULL;
    nouv->pere = NULL;

    T_Sommet * actuel = *arbre;
    T_Sommet * pere = NULL;

    if (actuel == NULL)
    {
        *arbre = nouv;
        return;
    }

    while (actuel != NULL)
    {
        if (actuel->cle == nouv->cle)
        {
            return;
        }
        else if (actuel->cle > nouv->cle)
        {
            pere = actuel;
            actuel = actuel->fils_gauche;
        }
        else
        {
            pere = actuel;
            actuel = actuel->fils_droit;
        }
    }
    if (pere == NULL)
    {
        *arbre = nouv;
    }
    else
    {
        nouv->pere = pere;
        if (pere->cle > nouv->cle)
        {
            pere->fils_gauche = nouv;
        }
        else
        {
            pere->fils_droit = nouv;
        }
    }
}

void afficherArbre(T_Arbre arbre)
{
    if (arbre != NULL)
    {
        printf("(");
        afficherArbre(arbre->fils_gauche);
        printf(", %d,", arbre->cle);
        afficherArbre(arbre->fils_droit);
        printf(")");
    }
    else
    {
        printf("_");
    }
}

int successeur(T_Sommet * sommet)
{
    if (sommet == NULL)
    {
        return -1;
    }

    if (sommet->fils_droit != NULL)
    {
        sommet = sommet->fils_droit;

        while (sommet->fils_gauche != NULL)
        {
            sommet = sommet->fils_gauche;
        }
        return sommet->cle;
    }
    else
    {
        while (sommet->pere != NULL && sommet->pere->fils_gauche != sommet)
        {
            sommet = sommet->pere;
        }
        if (sommet->pere == NULL)
        {
            return -1;
        }
        return sommet->pere->cle;
    }
}

void supprimerSommet(T_Arbre * arbre, int val)
{
    if (arbre == NULL)
    {
        return;
    }

    T_Sommet * actuel = *arbre;

    while (actuel != NULL && actuel->cle != val)
    {
        if (actuel->cle > val)
        {
            actuel = actuel->fils_gauche;
        }
        else
        {
            actuel = actuel->fils_droit;
        }
    }

    if (actuel == NULL)
    {
        return;
    }

    if (actuel->fils_gauche == NULL && actuel->fils_droit == NULL) // pas de fils
    {
        if (actuel->pere == NULL) // Pas de pere ==> Un seul noeud dans tout l'arbre
        {
            free(actuel);
            *arbre = NULL;
            return;
        }
        else // sinon noeud simple mais juste sans fils
        {
            if (actuel == actuel->pere->fils_gauche)
            {
                actuel->pere->fils_gauche = NULL;
                free(actuel);
                return;
            }
            else
            {
                actuel->pere->fils_droit = NULL;
                free(actuel);
                return;
            }
        }
    }
    else if (actuel->fils_droit == NULL || actuel->fils_gauche == NULL) // un seul fils (ne peux pas remplir les 2 clauses du ou car tombe dans le cas precedent
    {
        if (actuel->fils_gauche != NULL) // le noeud a un fils gauche
        {
            actuel->fils_gauche->pere = actuel->pere; // on met le pere du fils gauche au pere du noeud a supprimer, qu'il soit NULL ou non
            if (actuel->pere == NULL) // cas de la racine
            {
                *arbre = actuel->fils_gauche;
                free(actuel);
                return;
            }
            else // sinon on rattache le pere avec le fils gauche du noeud a supprimer
            {
                if (actuel == actuel->pere->fils_gauche)
                {
                    actuel->pere->fils_gauche = actuel->fils_gauche;
                    free(actuel);
                    return;
                }
                else
                {
                    actuel->pere->fils_droit = actuel->fils_gauche;
                    free(actuel);
                    return;
                }
            }
        }
        else // le noeud a un fils droit
        {
            actuel->fils_droit->pere = actuel->pere; // on met le pere du fils droit au pere du noeud a supprimer, qu'il soit NULL ou non

            if (actuel->pere == NULL) // cas de la racine
            {
                *arbre = actuel->fils_droit;
                free(actuel);
                return;
            }
            else // sinon on rattache le pere avec le fils droit du noeud a supprimer
            {
                if (actuel == actuel->pere->fils_gauche)
                {
                    actuel->pere->fils_gauche = actuel->fils_droit;
                    free(actuel);
                    return;
                }
                else
                {
                    actuel->pere->fils_droit = actuel->fils_droit;
                    free(actuel);
                    return;
                }
            }
        }
    }
    else
    {
        int suc = successeur(actuel);
        actuel->cle = suc;
        supprimerSommet(&(actuel->fils_droit), suc);
    }
}

int hauteurArbre(T_Arbre arbre)
{
    if (arbre == NULL)
    {
        return -1;
    }
    int gauche = hauteurArbre(arbre->fils_gauche);
    int droit = hauteurArbre(arbre->fils_droit);

    if (gauche > droit)
    {
        return gauche + 1;
    }
    else
    {
        return droit + 1;
    }
}

void viderArbre(T_Arbre * arbre)
{
    if (arbre == NULL)
    {
        return;
    }

    while (*arbre != NULL)
    {
        supprimerSommet(arbre, (*arbre)->cle);
    }
}
