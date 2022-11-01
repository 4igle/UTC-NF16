#include <stdio.h>
#include <stdlib.h>

void permutation(int *x, int *y);
int gagne(char tab[]);
void afficher(char tab[]);
int verifier(char trouve[], char mot_secret[], char c);

int main()
{

    // Ex 1.1
    /*
    float x, y;
    printf("Entrez deux reels separes d'un espace : ");
    scanf("%f %f", &x, &y);
    printf("x = %f y = %f\n", x, y);
    float z = x + y;
    printf("x + y = %f\n", z);
    */

    // Ex 1.2
    /*
    float x, y, temp;
    printf("Entrez deux reels separes d'un espace : ");
    scanf("%f %f", &x, &y);
    printf("x = %f y = %f\n", x, y);
    temp = x;
    x = y;
    y = temp;
    printf("x = %f y = %f\n", x, y);
    */

    // Ex 1.3
    /*
    float y, p, x;
    printf("Entrez un nombre et le pourcentage voulu separes d'un espace : ");
    scanf("%f %f", &y, &p);
    x = (y * p) / 100.0;
    printf("%f pourcent de %f = %f", p, y, x);
    */

    // Ex 1.4
    /*
    float cel, far;
    printf("Entrez une temperature en Fahrenheit : ");
    scanf("%f", &far);
    cel = (5.0 / 9.0) * (far - 32);
    printf("La temperature en Celsius est %f", cel);
    */

    // Ex 1.5
    /*
    int n;
    printf("Entrez une entier : ");
    scanf("%d", &n);
    printf("decimal : %d, octal : %o, hexadecimal : %x", n, n, n);
    */

    // Ex 1.6
    /*
    int n;
    printf("Entrez une entier : ");
    scanf("%d", &n);
    if (n == 0)
    {
        printf("Le nombre est 0, il est pair");
    }
    else if (n % 2 == 0)
    {
        printf("Le nombre est pair");
    }
    else
    {
        printf("Le nombre est impair");
    }
    */

    // Ex 1.7
    /*
    char c;
    c = '5';
    printf("c = %c\n", c);
    c = 96;
    printf("c = %c\n", c);
    */

    // Ex 2.1
    /*
    char c;
    printf("Entrez un caractere : ");
    scanf("%c", &c);

    if ((c >= '0') && (c <= '9'))
    {
        printf("Le caractere saisi est un chiffre");
    }
    else if ((c >= 'a') && (c <= 'z'))
    {
        printf("Le caractere saisi est une lettre minuscule");
    }
    else if ((c >= 'A') && (c <= 'Z'))
    {
        printf("Le caractere saisi est une lettre majuscule");
    }
    */

    // Ex 2.2
    /*
    unsigned int n;
    do
    {
        printf("Entrez un nombre positif");
        scanf("%u", &n);
    } while (n != -1);
    */

    // Ex 2.3
    /*
    char c;
    int i, n;
    do
    {
        printf("Quelle table de multiplication voulez-vous, tapez 0 (zero) pour sortir ? ");
        scanf("%c", &c); // On nous demande de saisir sous forme de caractère
        while(getchar() != '\n'); // On vide le buffer
        if (c >= '1' && c <= '9')
        {
            // c est un chiffre sous forme de char, on le récu^ère en int
            n = c - '0';
            for (i = 0; i <= 9; i++)
            {
                printf("%c * %d = %d\n", c, i, i*n);
            }
        }
        else if (c != '0')
        {
            printf("Ce n'est pas dans les possibilites du programme, recommencez !\n");
        }
    } while (c != '0');
    */

    // Ex 2.4
    /*
    printf("Saisissez un caractere : ");
    switch(getchar())
    {
        case '1':
            printf("un");
            break;
        case '2':
            printf("deux");
            break;
        case '3':
            printf("trois");
            break;
        default:
            printf("autre caractre");
    }
    */

    // Ex 3.1
    /*
    int tab[10];
    int i;
    for (i = 0; i <= 9; i++)
    {
        tab[i] = 0;
    }
    */

    // Ex 3.2
    /*
    int tab[5] = {4, 3, 2, 1, 0}
    */

    // Ex 3.3
    /*
    int tab[3][4];
    int n = 12;
    int i, j;
    for (i = 0; i <= 2; i++)
    {
        for (j = 0; j <= 3; j++)
        {
            tab[i][j] = n;
            n++;
        }
    }

    for (i = 0; i <= 2; i++)
    {
        for (j = 0; j <= 3; j++)
        {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
    */

    // Ex 4.1
    /*
    int a, b;
    a = 5;
    b = 6;
    printf("a = %d, b = %d\n", a, b);
    permutation(&a, &b);
    printf("a = %d, b = %d\n", a, b);
    */

    // Ex 4.2
    /* On doit utiliser des pointeurs car en passant par des
     * valeurs, la fonction crée une copie des variables interne
     * à la fonction, les valeurs ne sont pas réellement modifiées */

    // Ex 4.3
    /*
    int i;
    int *j;
    i = 5;
    j = &i;
    printf("i = %d, j = %d\n", i, *j);
    */

    // Ex 4.4
    /*
    int i;
    int *j;
    i = 5;
    j = &i;
    printf("i = %d, *j = %d\n", i, *j);
    *j += 1;
    printf("i = %d\n", i);
    i *= 5;
    printf("*j = %d\n", *j);
    j += 1;
    printf("*j = %d", *j);
    */

    // Ex 4.5
    /*
    int tab[3][4];
    int n = 12;
    int i, j;
    for (i = 0; i <= 2; i++)
    {
        for (j = 0; j <= 3; j++)
        {
            *(tab+i)[j] = n;
            n++;
        }
    }

    for (i = 0; i <= 2; i++)
    {
        for (j = 0; j <= 3; j++)
        {
            printf("%d ", *(tab+i)[j]);
        }
        printf("\n");
    }*/

    // Ex 4.7
    /*
    int tab[5];
    int i, *ptr;
    ptr = tab;
    for (i = 0; i < 5; i++)
    {
        printf("Entrez la valeur %d du tableau : ", i);
        scanf("%d", ptr);
        ptr++;
    }
    ptr = tab;
    for (i = 0; i < 5; i++)
    {
        printf("%d\n", *ptr);
        ptr++;
    }
    printf("\n");


    ptr = tab;
    for (i = 0; i < 4; i++)
    {
        permutation(ptr, ptr + 1);
        ptr++;
    }
    ptr = tab;
    for (i = 0; i < 5; i++)
    {
        printf("%d\n", *ptr);
        ptr++;
    }
    printf("\n");


    ptr = &tab[4];
    for (i = 4; i > 0; i--)
    {
        permutation(ptr, ptr - 1);
        ptr--;
    }
    ptr = tab;
    for (i = 0; i < 5; i++)
    {
        printf("%d\n", *ptr);
        ptr++;
    }
    */


    // 5.1 TP
    /*
    char chaine[] = "bonjour bonbon";
    char sous_chaine[] = "bon";
    int i = 0;
    int j = 0;
    int position;
    int nombre = 0;
    while (chaine[i] != '\0'){
        if (chaine[i] == sous_chaine[0]){
            position = i;
            while (sous_chaine[j] != '\0' && sous_chaine[j] == chaine[i+j]){
                j++;
            }
            if (sous_chaine[j] == '\0'){
                nombre++;
                printf("position : %d\n", position);
            }
            j = 0;
        }
        i++;
    }
    printf("nombre = %d", nombre);
    */

    // 5.2 TP
    /*
    char chaine[] = "bonjour";
    int i = 0;

    while (chaine[i] != '\0'){
        if (chaine[i] >= 'a' && chaine[i] <= 'z'){
            chaine[i] -= 'a' - 'A';
        }
        i++;
    }
    printf("chaine = %s", chaine);
    */

    // Ex 5.3
    char mot_secret[100];
    char trouve[100];
    char *ptr, c;
    int i;
    int taille = 0;
    int coups_restants = 10;
    printf("Entrez le mot secret : ");
    scanf("%s", mot_secret);
    while (getchar() != '\n');
    printf("\n\n\n\n\n\n\n\n\n\n\n\n");

    ptr = mot_secret;
    while (*ptr != '\0')
    {
        taille++;
        ptr++;
    }
    //printf("Taille du mot : %d", taille);
    for (i = 0; i < taille; i++)
    {
        trouve[i] = '*';
    }
    trouve[taille] = '\0';

    while (coups_restants >= 1 && !gagne(trouve))
    {
        printf("%d coups restants\n", coups_restants);
        printf("Mot : ");
        afficher(trouve);
        printf("Caractere : ");
        scanf("%c", &c);
        while (getchar() != '\n');
        if (!verifier(trouve, mot_secret, c))
        {
            coups_restants--;
        }
    }
    if (coups_restants == 0)
    {
        printf("Vous avez perdu, le mot etait ");
        afficher(mot_secret);
    }
    else
    {
        printf("Vous avez gagne, le mot etait bien ");
        afficher(trouve);
    }







    return 0;
}

void permutation(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int gagne(char tab[])
{
    char *ptr = tab;
    while (*ptr != '\0')
    {
        if (*ptr == '*')
        {
            return 0;
        }
        ptr++;
    }
    return 1;
}

void afficher(char tab[])
{
    char *ptr = tab;
    while (*ptr != '\0')
    {
        printf("%c", *ptr);
        ptr++;
    }
    printf("\n");
}

int verifier(char trouve[], char mot_secret[], char c)
{
    int i = 0;
    int bonne_lettre = 0;
    while(mot_secret[i] != '\0')
    {
        if (mot_secret[i] == c)
        {
            bonne_lettre = 1;
            trouve[i] = c;
        }
        i++;
    }
    return bonne_lettre;
}
