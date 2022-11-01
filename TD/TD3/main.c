#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NMAX 10
#define TAILLETAB 20
#define TAILLECHAINE 60

typedef struct menu{
    char tab[TAILLETAB][TAILLECHAINE];
    int ncase;
}menu;

int min_tab(int *tab, int taille);
int en_domain(int a, int b, int c);
void min_to_maj(char *chaine);
int factorielle(int n);
int my_strlen(char *chaine);
int max_length_str(menu m);
void affichage_menu(menu m);
int choix(menu m);


int main() {
    // Ex 8.5
    /*
    int tab[5] = {15, 2, 3, 5, 1};
    printf("Le min est : %d", min_tab(tab, 5));
    */

    // Ex 8.6
    /*
    int a = 50;
    int b = 1;
    int c = 10;
    if (en_domain(a, b, c)){
        printf("'a' est dans le domaine");
    }
    else{
        printf("'a' n'est pas dans le domaine");
    }
     */

    // Ex 8.7
    /*
    char chaine[] = "Bonjour comment ça va ? 789";
    printf("Chaîne avant modif : %s\n", chaine);
    min_to_maj(chaine);
    printf("Chaîne après modif : %s\n", chaine);
    */

    //Ex 8.9
    /*
    printf("%d", factorielle(4));
    */

    // Ex 9.1
    /*
    typedef struct point {
        float x;
        float y;
    } point;

    point p1 = {1.0, 3.0};
    p1.x += 1;
    printf("%.2f\n", p1.x);

    point *p2;
    p2 = &p1;

    (*p2).x++;
    printf("%.2f\n", p2->x);
    */

    // Ex 9.2
    /*
    typedef struct Un_Tableau_Entier{
        int tab[NMAX];
        int ncase;
    } Un_Tableau_Entier;
    */

    // Ex 9.3 9.4 9.5 9.6
    menu m;
    m.ncase = 3;
    strcpy(m.tab[0], "plat");
    strcpy(m.tab[1], "autre plat");
    strcpy(m.tab[2], "encore un autre plat");
    //printf("%d", max_length_str(m));
    //affichage_menu(m);
    int c = choix(m);
    printf("\nVotre choix : %d", c);





    return 0;
}

int min_tab(int *tab, int taille){
    int min = tab[0];
    for (int i = 1; i < taille; i++){
        if (tab[i] < min){
            min = tab[i];
        }
    }
    return min;
}

int en_domain(int a, int b, int c){
    return (a >= b && a <= c);
}

void min_to_maj(char *chaine){
    int i = 0;
    while (chaine[i] != '\0'){
        if (chaine[i] >= 'a' && chaine[i] <= 'z'){
            chaine[i] -= 'a' - 'A';
        }
        i++;
    }
}

int factorielle(int n){
    if (n < 0){
        return -1;
    }
    if (n <= 1){
        return n;
    }
    return factorielle(n-1) * n;
}

int max_length_str(menu m){
    int max = -1;
    for (int i = 0; i < m.ncase; i++){
        if (my_strlen(m.tab[i]) > max){
            max = strlen(m.tab[i]);
        }
    }
    return max;
}

void affichage_menu(menu m){

    int max = max_length_str(m);

    for (int i = 0; i < m.ncase; i++){
        printf("%d ", i+1);
        for (int j = 0; j < (max - my_strlen(m.tab[i])) / 2; j++){
            printf(" ");
        }
        printf("%s\n", m.tab[i]);
    }
}

int my_strlen(char *chaine){
    int cpt=0;
    while (chaine[cpt] != '\0'){
        cpt++;
    }
    return cpt;
}

int choix(menu m){
    char chaine[TAILLECHAINE];

    do{
        system("clear");
        printf("\n");
        affichage_menu(m);
        printf("Entrez menu désiré : ");
        scanf("%[^\n]%*c", chaine);

        for (int i = 0; i < m.ncase; i++){
            if (strcmp(chaine, m.tab[i]) == 0){
                return i+1;
            }
        }
    }while(strcmp(chaine, "q") != 0 && strcmp(chaine, "Q") != 0);

    return 0;
}