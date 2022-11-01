#include <stdio.h>

#define NMAX 10
#define TC 10
#define NROW 3
#define NCOL 4

void swap(int *a, int *b);
int my_ascii (char c);
int my_strlen(char *chaine);
int lecture_tab(int *tab);

int main() {


    // Ex 6
    /*
    int i = 5;
    printf("&i = %d\n", &i);
    int *j = &i;
    printf("adresse j : %d, valeur de j : %d, valeur pointée par j : %d\n", &j, j, *j);
    (*j)++;
    printf("(*j)++\nvaleur i : %d, valeur de j : %d, valeur pointée par j : %d\n", i, j, *j);
    i *= 5;
    printf("i *= 5\nvaleur i : %d, valeur de j : %d, valeur pointée par j : %d\n", i, j, *j);
    j++;
    printf("j++\nvaleur i : %d, valeur de j : %d, valeur pointée par j : %d\n", i, j, *j);
    */

    // Ex 7

    // 7.1
    /*
    int tab[NMAX];
    for (int i =0; i < NMAX; i++){
        *(tab + i) = 7;
        printf("tab[%d] = %d\n", i, tab[i]);
    }*/

    // 7.2
    /*
    int tab[NMAX];
    for (int i =0; i < NMAX; i++){
        *(tab + i) = NMAX - i - 1;
        printf("tab[%d] = %d\n", i, tab[i]);
    }*/

    // 7.3
    /*
    char chaine[TC] = {'b', 'o', 'n', 'j', 'o', 'u', 'r', '\0'};
    printf("%s\n", chaine);
    int i = 0;
    while (chaine[i] != '\0'){
        printf("%c", *(chaine + i));
        i++;
    }
    */
    // 7.4
    /*
    char chaine[NMAX];
    printf("Entrez une chaine de caractères : ");
    scanf("%s", chaine);

    int i = 0;
    while (chaine[i] != '\0' && chaine[i] != 'o'){
        i++;
    }
    if (chaine[i] == 'o'){
        chaine[i] = 'a';
    }
    i = 0;
    while (chaine[i] != '\0' && chaine[i] != 'n'){
        i++;
    }
    if (chaine[i] == 'n'){
        chaine[i] = 'd';
    }
    printf("%s\n", chaine);
    */

    // 7.5, 7.6
    /*
    int tab[NMAX];
    int somme = 0;

    for (int i = 0; i < NMAX; i++){
        printf("tab[%d] = ", i);
        scanf("%d", tab+i);
        somme += *(tab + i);
    }

    printf("somme = %d\n", somme);

    float moyenne = (float) somme / NMAX;

    printf("moyenne = %.2f\n", moyenne);

    for (int i = 0; i < NMAX; i++){
        printf("tab[%d] = %d", i, tab[i]);
        if (tab[i] >= moyenne){
            printf(" ADMIS");
        }
        printf("\n");
    }
    */

    // 7.7
    /*
    int tab[NROW][NCOL]; // = {12,13,14,15,16,17,18,19,20,21, 22, 23};

    int val = 12;
    for (int i = 0; i < NROW; i++){
        for (int j = 0; j < NCOL; j++){
            tab[i][j] = val;
            printf("tab[%d][%d] = %d\n", i, j, tab[i][j]);
            val++;
        }
    }
    */

    // 7.8
    /*
    int tab[NROW][NCOL]; // = {12,13,14,15,16,17,18,19,20,21, 22, 23};

    int val = 12;
    for (int i = 0; i < NROW; i++){
        for (int j = 0; j < NCOL; j++){
            *(*(tab+i)+j) = val;
            printf("tab[%d][%d] = %d\n", i, j, (*(tab + i))[j]);
            val++;
        }
    }
    */

    // Ex8
    // 8.1
    /*
    int x = 5;
    int y = 10;
    printf("x = %d, y = %d\n", x, y);
    swap(&x, &y);
    printf("x = %d, y = %d\n", x, y);
     */

    // 8.4

    int tab[NMAX];
    lecture_tab(tab);


    return 0;
}

void swap(int *a, int *b){
    int buffer = *a;
    *a = *b;
    *b = buffer;
}

int my_ascii (char c){
    return (c >= 0 && c <=127);
}

int my_strlen(char *chaine){
    int cpt=0;
    while (chaine[cpt] != '\0'){
        cpt++;
    }
    return cpt;
}

int lecture_tab(int *tab){
    int n;
    do{
        printf("Saisir un nombre entre 1 et 10 : ");
        scanf("%d", &n);
    } while(n > 10 || n < 0);

    for (int i = 0; i < n; i++){
        printf("Saisir la valeur %d du tableau : ", i);
        scanf("%d", tab+i);
    }
    return n;
}
