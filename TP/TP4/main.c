#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"

//#include "fonction.c"

int main()
{
    int fichier_charge = 0;
    char mot[100];
    char filename[100];
    t_Index *index = creer_index();
    int choix = 0;
    while(choix != 8)
    {
        printf("\n========================================================\n");
        printf("Choisissez une option:\n");
        printf("1 - Charger un fichier\n");
        printf("2 - Caracteristiques de l'index\n");
        printf("3 - Afficher index\n");
        printf("4 - Rechercher un mot\n");
        printf("5 - Afficher le mot avec le maximum d'apparitions\n");
        printf("6 - Afficher les occurences d'un mot\n");
        printf("7 - Construire un texte à partir de l'index\n");
        printf("8 - Quitter\n");
        printf("========================================================\n");
        printf("\n-> ");
        scanf("%d", &choix);
        switch(choix) {
            case 1:
                if(fichier_charge == 0)
                {
                    printf("\nEntrez le nom du fichier à charger : ");
                    scanf("%s", filename);
                    printf("\n");
                    if (indexer_fichier(index, filename) != 0)
                    {
                        printf("\nFichier charge avec succes\n");
                        fichier_charge = 1;
                    }
                }
                else
                {
                    printf("\nVous avez dejà charge un fichier.\n");
                }
                break;

            case 2:
                if(fichier_charge == 1)
                {
                    printf("\nNombre de mots differents : %d\n", index->nb_mots_differents);
                    printf("Nombre de mots total : %d\n", index->nb_mots_total);
                    printf("Hauteur de l'arbre : %d\n", hauteur(index->racine));
                    if (equilibre(index->racine) != -2)
                    {
                        printf("\nL'arbre est equilibre.\n");
                    }
                    else
                    {
                        printf("\nL'arbre n'est pas equilibre\n");
                    }
                }
                else
                {
                    printf("\nVous devez charger un fichier avant de pouvoir afficher les caracteristiques de l'index.\n");
                }
                break;
            case 3:
                if (fichier_charge == 1)
                {
                    afficher_index(index);
                }
                else
                {
                    printf("\nVous devez charger un fichier.\n");
                }
                break;
            case 4:
                if (fichier_charge == 1)
                {
                    printf("\nEntrez le mot à rechercher: ");
                    scanf("%s", mot);
                    t_Noeud *noeud = rechercher_mot(index, mot);
                    if(noeud != NULL)
                    {
                        printf("\nLe mot '%s' est present %d fois dans l'index.\nIl apparait :\n", mot, noeud->nb_occurences);
                        t_Position *position = noeud->positions->debut;
                        while (position != NULL)
                        {
                            printf("  - Ligne %d, ordre %d, phrase %d\n", position->numero_ligne, position->ordre, position->numero_phrase);
                            position = position->suivant;
                        }
                    }
                    else
                    {
                        printf("\nLe mot '%s' n'est pas present dans l'index.\n", mot);
                    }
                }
                else
                {
                    printf("\nVous devez charger un fichier avant de pouvoir rechercher un mot.\n");
                }
                break;
            case 5:
                if (fichier_charge == 1)
                {
                    afficher_max_apparition(index);
                }
                else
                {
                    printf("\nVous devez charger un fichier avant de pouvoir afficher le mot avec le maximum d'apparitions.\n");
                }
                break;
            case 6:
                if (fichier_charge == 1)
                {
                    printf("\nEntrez le mot à rechercher: ");
                    scanf("%s", mot);
                    afficher_occurences_mot(index, mot);
                }
                else
                {
                    printf("\nVous devez charger un fichier avant de pouvoir rechercher un mot.\n");
                }
                break;
            case 7:
                if (fichier_charge == 1)
                {
                    printf("\nEntrez le nom du fichier de sortie : ");
                    scanf("%s", filename);
                    construire_texte(index, filename);
                }
                else
                {
                    printf("\nVous devez charger un fichier avant de pouvoir construire un texte.\n");
                }
                break;
            case 8:
                if (fichier_charge == 1)
                {
                    liberer_arbre(index->racine);
                    liberer_liste_phrases(index->liste_phrases);
                    liberer_liste_phrases(index->liste_lignes);
                    free(index);
                    printf("\nVous avez quitte le programme.\n");
                }
                break;
            default:
                printf("\nChoix invalide\n");
        }
    }
    return 0;
}
