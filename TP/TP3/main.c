#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"
#include <unistd.h>


int main()
{
    // On initialise les variables
    long cin;
    int choice;
    char nom[200];
    float ratio;

    // On initialise les pointeurs (à NULL)
    T_Electeur liste=NULL;
    T_Electeur droite=NULL;
    T_Electeur gauche=NULL;
    T_Electeur blanc=NULL;

    // On initialise la variable de choix
    int c;

    // On affiche le menu jusqu'à ce que l'utilisateur quitte
    do{
        printf("\n************************ Voici le menu *******************\n");
        printf("\n  1. Ajouter des electeurs,\n  2. Supprimer un electeur, \n  3. Rechercher un electeur, \n  4. Afficher la liste des electeurs, \n  5. Calculer le nombre d'electeurs,\n  6. Decouper la liste en trois sous-listes selon les choix: droite, gauche et blanc\n    - Trier les sous-listes\n    - Afficher les sous-listes,\n    - Fusionner les deux sous-listes : gauche et droite\n  7. Calculer les pourcentages de gauche et de droite pour le 2ème tour,\n  8. Liberer les listes\n  9. Quitter\n");
        printf("\n\nEntrer le numero du menu : ");
        scanf("%d",&c);
        while(getchar() != '\n');
        switch(c){

            // Ajout d'un electeur
            case 1:
                // On rentre les données de l'electeur
                printf("\nNom d'electeur : ");
                scanf("%[^\n]s",nom);
                printf("\nCIN : ");
                scanf("%ld",&cin);
                printf("\nChoix : \nNOM1 : 1\nNOM2 : 2\nNOM3 : 3\nNOM4 : 4\nAUTRE / BLANC : 5\n-> ");
                scanf("%d",&choice);

                // On met le choix à blanc si l'utilisateur ne rentre pas un choix valide
                if (choice != 1 && choice != 2 && choice != 3 && choice != 4)
                {
                    choice = 5;
                }

                // On fait appel à la fonction d'ajout
                ajoutelecteur(&liste, nom, cin, choice);
                printf("\nL'electeur a ete ajoute a la liste\n");
                break;

            // Suppression d'un electeur
            case 2:
                // On rentre le CIN de l'electeur à supprimer
                printf("\nCIN de l'electeur a supprimer : ");
                scanf("%ld",&cin);

                // On fait appel à la fonction de suppression
                Supprimelecteur(&liste, cin);
                break;

            // Recherche d'un electeur
            case 3:
                // On rentre le CIN de l'electeur à rechercher
                printf("\nCIN de l'electeur a rechercher : ");
                scanf("%ld",&cin);

                // On fait appel à la fonction de recherche
                trouvelecteur(liste,cin);
                break;

            // Affichage de la liste des electeurs
            case 4:
                // On fait appel à la fonction d'affichage
                afficheliste(liste);
                break;

            // Affichage du nombre d'electeurs
            case 5:
                // On fait appel à la fonction de calcul du nombre d'electeurs
                printf("\nIl y a %d electeurs\n",comptelecteur(liste));
                break;

            // Decoupage de la liste en trois sous-listes selon les votes
            // puis affichage des sous-listes
            // puis tri des sous-listes en fonction de leur CIN
            // puis fusion de la liste gauche et droite
            case 6:
                // On fait appel à la fonction de décomposition en trois sous-listes
                decoupeliste(liste,&gauche,&blanc,&droite);

                // On fait appel à la fonction de tri pour les trois sous-listes
                triliste(&blanc);
                triliste(&droite);
                triliste(&gauche);

                // On affiche les trois sous-listes
                printf("\nListe blanc : \n");
                afficheliste(blanc);
                printf("\nListe droite : \n");
                afficheliste(droite);
                printf("\nListe gauche : \n");
                afficheliste(gauche);

                // On libère la liste blanc comme on ne l'utilise plus
                libereliste(blanc);
                // On met également son pointeur à NULL
                blanc = NULL;

                // On fait appel à la fonction de fusion pour réunir gauche et droite
                liste=fusionlistes(gauche,droite);

                // gauche et droite n'existent plus, leurs éléments sont dans liste, on met leurs pointeurs à NULL
                gauche = NULL;
                droite = NULL;

                break;

            // Affichage du pourcentage de votes de gauche et de droite au second tour
            case 7:
                // On calcule le ratio de votes à gauche sur la totalité des votes
                ratio = (float) compteGD(liste)/ (float) comptelecteur(liste);

                // On affiche le pourcentage d'électeurs à gauche et de droite
                printf("\nVoici le pourcetage d'electeur de gauche au second tour: %.2f %c\n", ratio*100, '%');
                printf("\nVoici le pourcetage d'electeur de droite au second tour: %.2f %c\n", 100 - (ratio*100), '%');
                break;

            // Liberation de la liste
            case 8:
                // On libère la liste
                libereliste(liste);

                // On met le pointeur de liste à NULL
                liste = NULL;
                printf("\nLa liste a ete libérée\n");
                break;

            // Afficher quitter
            case 9:
                printf("\nQuitter\n");
                break;

            // Afficher Saisie invalide
            default:
                printf("\nVeuillez entrer une instruction valide\n");
                break;

        }

        // On fait une courte pause avant la prochaine itération
        // pour laisser le temps de voir les résultats
        sleep(3);

    }while(c!=9);

    return 0;
}
