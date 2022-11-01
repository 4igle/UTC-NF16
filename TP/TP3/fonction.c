#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"
#include <string.h>


// Fonction permettant de créer un électeur
T_Electeur creationelecteur(void)
{
    // On crée un pointeur pointant vers un espace mémoire de la taille d'un électeur
    T_Electeur e = malloc(sizeof(electeur));

    // On gère le cas ou l'allocation mémoire n'a pas fonctionné
    if (e != NULL)
    {
        e->suivant=NULL;
    }
    return e;
}

// Fonction permettant d'afficher une liste
void afficheliste(T_Electeur liste)
{
    // On affiche une erreur si la liste est vide
    if (liste == NULL)
    {
        printf("\nLa liste est vide !\n");
    }

    // On parcours la liste en affichant les informations des électeurs
    else
    {
        printf("\n--------- Voici la liste des electeurs ---------\n");
        while (liste != NULL)
        {
            printf("\nNom : %s\nNumero electeur : %ld\nVote : %d\n", liste->nom, liste->cin_num, liste->choix);
            liste = liste->suivant;
        }
        printf("\n------------------------------------------------\n\n");

    }
}

// Fonction permettant d'ajouter un électeur à la liste selon l'ordre alphabétique
void ajoutelecteur(T_Electeur *liste, char nom[], long cin_num, int choix)
{
    // On crée un pointeur pointant vers un électeur,
    // l'électeur est créé dans la fonction creationelecteur() définie plus haut
    T_Electeur nouv = creationelecteur();

    // On ne traite l'ajout que dans le cas ou l'allocation mémoire a fonctionné
    if (nouv != NULL)
    {
        // On affecte les valeurs des attributs de l'électeur
        nouv->cin_num = cin_num;
        nouv->choix = choix;

        // On récupère la taille du nom avec siezof et on
        // alloue un espace mémoire de cette taille
        nouv->nom = malloc(sizeof(nom));
        strcpy(nouv->nom, nom);

        // On initialise une variable de parcours de liste
        T_Electeur actuel = *liste;

        // Si la liste est vide, on doit redéfinir liste, qui est un pointeur vers
        // le premier élément. Liste pointera maintenant vers l'élément que nous venons d'ajouter
        if (actuel == NULL)
        {
            *liste = nouv;
        }

        // Si la liste n'est pas vide, on parcours la liste jusqu'à ce qu'on trouve sa position
        // selon l'ordre alphabétique
        else
        {
            T_Electeur precedent = NULL;

            // Tant que nous ne sommes pas en fin de liste et que l'élément actuel est situé
            // avant dans l'ordre alphabétique, on avance dans la liste
            while(actuel != NULL && strcmp(nouv->nom, actuel->nom) > 0)
            {
                precedent = actuel;
                actuel = actuel->suivant;
            }

            // Si precedent est NULL, l'élément que nous venons d'ajouter est le premier de la liste
            // Il faut donc le redéfinir liste pour pointer vers cet élément
            if (precedent == NULL)
            {
                nouv->suivant = *liste;
                *liste = nouv;
            }

            // Si actuel est NULL, l'élément que nous venons d'ajouter est le dernier de la liste
            else if (actuel == NULL)
            {
                precedent->suivant = nouv;
            }

            // Sinon, l'élément que nous venons d'ajouter est situé quelquepart dans la liste
            // ni au début, ni à la fin. On le place donc entre précédent et actuel
            else
            {
                nouv->suivant = actuel;
                precedent->suivant = nouv;
            }
        }
    }
}

// Fonction renvoyant le nombre d'électeurs dans la liste
int comptelecteur(T_Electeur liste)
{
    int compte = 0;

    // On parcours la liste tout en incrémentant le compteur à chaque élément
    while (liste != NULL)
    {
        compte ++;
        liste = liste->suivant;
    }
    return compte;
}

// Fonction qui trouve un électeur dans la liste selon son numéro d'électeur et affiche ses informations
int trouvelecteur(T_Electeur liste, long cin_num)
{
    // On avance dans la liste tant que l'électeur n'est pas trouvé et que l'on est pas en bout de liste
    while (liste != NULL && liste->cin_num != cin_num)
    {
        liste = liste->suivant;
    }

    // Si liste est NULL, on est en bout de liste et l'électeur n'est pas dans la liste
    if (liste == NULL)
    {
        printf("\nCet electeur n'est pas dans la liste\n");
        return 0;
    }

    // Dans le cas contrainre, l'électeur a été trouvé, on affiche ses informations
    else
    {
        printf("\nElecteur trouve !\nInformations concernant l'electeur :\n");
        printf("\nNom : %s\nNumero electeur : %ld\nVote : %d\n", liste->nom, liste->cin_num, liste->choix);
        return 1;
    }
}

// Fonction qui supprime un électeur dans la liste selon son numéro d'électeur
void Supprimelecteur(T_Electeur *liste, long cin_num)
{
    T_Electeur actuel = *liste;
    T_Electeur precedent = NULL;

    // On avance dans la liste tant que l'électeur n'est pas trouvé et que l'on est pas en bout de liste
    while (actuel != NULL && actuel->cin_num != cin_num)
    {
        precedent = actuel;
        actuel = actuel->suivant;
    }

    // Si actuel est NULL, on est en bout de liste et l'électeur n'est pas dans la liste
    if (actuel == NULL)
    {
        printf("\nCet electeur n'est pas dans la liste\n");
    }

    // Sinon, l'électeur a été trouvé, on le supprime
    else
    {
        // Si précédent est NULL, l'élément que nous voulons de supprimer est le premier de la liste
        // Il faut donc redéfinir liste pour pointer vers l'élément suivant
        if (precedent == NULL)
        {
            *liste = (*liste)->suivant;
        }

        // Sinon, l'élément que nous voulons supprimer est ailleurs dans la liste,
        // on relie donc le précédent et le suivant
        else
        {
            precedent->suivant = actuel->suivant;
        }

        // On libère ensuite l'espace mémoire dédié à l'élément que nous venons de supprimer
        free(actuel);
        printf("\nL'electeur a ete supprime de la liste\n");
    }
}


// Fonction qui découpe la liste en trois sous-listes selon le choix de l'électeur
void decoupeliste(T_Electeur liste, T_Electeur *gauche, T_Electeur *blanc, T_Electeur *droite)
{
    // On parcourt la liste en plaçant chaque élément dans la bonne sous-liste au fur et à mesure
    while (liste != NULL)
    {
        // Si l'électeur a choisi un candidat de gauche (NOM1, NOM3), on l'ajoute à la liste gauche
        if (liste->choix == 1 || liste->choix == 3)
        {
            ajoutelecteur(gauche, liste->nom, liste->cin_num, liste->choix);
        }
        // Si l'électeur a choisi un candidat de droite (NOM2, NOM4), on l'ajoute à la liste droite
        else if (liste->choix == 2 || liste->choix == 4)
        {
            ajoutelecteur(droite, liste->nom, liste->cin_num, liste->choix);
        }
        // Sinon, on a liste->choix == 5, le candidat vote blanc et on l'ajoute à la liste blanc
        else
        {
            ajoutelecteur(blanc, liste->nom, liste->cin_num, liste->choix);
        }
        liste = liste->suivant;
    }
}

// Fonction qui trie une liste en fonction de son numéro d'électeur
// Cette fonction utilise le principe de tri à bulles
void triliste(T_Electeur *liste)
{
    int modif = 1;
    T_Electeur actuel;
    T_Electeur precedent;
    T_Electeur temp;

    // On parcourt la liste en échangeant deux éléments adjacents si
    // le numéro d'électeur du premier élément est plus grand que celui du second
    // On recommence tant que la liste n'est pas triée, c'est-à-dire
    // tant que l'on n'a pas parcouru toute la liste sans avoir eu à effectuer de modification
    while(modif == 1)
    {
        actuel = *liste;
        precedent = NULL;
        modif = 0;

        // On parcourt la liste tant que l'on n'est pas en bout de liste
        while(actuel->suivant != NULL)
        {
            // Si le numéro d'électeur du premier élément est plus grand que celui du second,
            // on échange les deux éléments
            if (actuel->cin_num > actuel->suivant->cin_num)
            {
                // Dans cette situation, nous allons effectuer un changement, on met donc modif à 1
                modif = 1;

                // Si precedent est NULL, c'est que l'élément actuel est le premier de la liste
                if (precedent == NULL)
                {
                    // On échange les deux éléments
                    temp = actuel->suivant;
                    actuel->suivant = actuel->suivant->suivant;
                    temp->suivant = actuel;

                    // On met à jour l'élément précédent
                    precedent = temp;

                    // On met à jour liste, car le premier élément à changé
                    *liste = precedent;
                }

                // Sinon, l'élément actuel est ailleurs dans la liste
                else
                {
                    // On échange les deux éléments
                    temp = actuel->suivant;
                    actuel->suivant = actuel->suivant->suivant;
                    precedent->suivant = temp;
                    temp->suivant = actuel;

                    // On met à jour l'élément précédent
                    precedent = temp;
                }
            }
            // Sinon si les deux éléments adjacents que nous comparons sont bien
            // placés l'un par rapport à l'autre, on passe à l'élément suivant
            else
            {
                precedent = actuel;
                actuel = actuel->suivant;
            }
        }
    }
}

// Fonction qui fusionne deux listes en renvoyant un pointeur sur la nouvelle liste fusionnée
// La fonction conserve l'ordre des éléments qui sont ordonnés par numéro d'électeur
T_Electeur fusionlistes(T_Electeur gauche, T_Electeur droite)
{
    T_Electeur liste = NULL;
    T_Electeur actuel;

    // On vérifie que les listes ne soient pas vides
    if(gauche != NULL && droite != NULL)
    {
        // On doit traiter le cas du premier élément de la liste fusionnée séparément,
        // car il faut faire pointer liste vers le premier élément de la liste fusionnée
        if (gauche->cin_num < droite->cin_num)
        {
            actuel = gauche;
            liste = gauche;
            gauche = gauche->suivant;
        }
        else
        {
            actuel = droite;
            liste = droite;
            droite = droite->suivant;

        }
    }

    // On ajoute ensuite les éléments tant qu'aucune des deux listes n'est vide
    while(gauche != NULL && droite != NULL)
    {
        if (gauche->cin_num < droite->cin_num)
        {
            actuel->suivant = gauche;
            gauche = gauche->suivant;
        }
        else
        {
            actuel->suivant = droite;
            droite = droite->suivant;
        }
        actuel = actuel->suivant;
    }

    // Si une des deux listes n'est pas vide, on ajoute ses éléments restants à la liste fusionnée
    if (gauche == NULL)
    {
        while(droite != NULL)
        {
            actuel->suivant = droite;
            droite = droite->suivant;
            actuel = actuel->suivant;
        }
    }
    else if (droite == NULL)
    {
        while(gauche != NULL)
        {
            actuel->suivant = gauche;
            gauche = gauche->suivant;
            actuel = actuel->suivant;
        }
    }
    return liste;
}

// Fonction qui compte le nombre d'électeurs de gauche dans une liste
int compteGD(T_Electeur liste)
{
    int gauche = 0;

    // On parcourt la liste et on incrémente gauche si l'électeur a voté pour un candidat de gauche
    while (liste != NULL)
    {
        if (liste->choix == 1 || liste->choix == 3)
        {
            gauche++;
        }
        liste = liste->suivant;
    }
    return gauche;
}

// Fonction qui libère les éléments d'une liste
void libereliste(T_Electeur liste)
{
    // On libère la mémoire occupée par chaque élément de la liste
    while (liste != NULL)
    {
        T_Electeur actuel = liste;
        liste = liste->suivant;
        free(actuel);
    }
}