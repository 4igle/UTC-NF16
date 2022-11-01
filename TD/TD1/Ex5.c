#include <stdio.h>
#include <stdlib.h>

int factorielle(int x){
    if (x >= 1){
        return x * factorielle(x-1);
    }
    return 1;
}


int main5() {
    int n;

    printf("Saisir un nombre : ");
    scanf("%d", &n);
    printf("%d\n", factorielle(n));

    int i = 1;
    int fact = 1;

    printf("Saisir un nombre : ");
    scanf("%d", &n);

    for (i=1; i<=n; i++){
        fact = fact * i;
    }

    printf("%d", fact);

    /*
    char c;
    do{
        printf("Saisissez un caractère : ");
        c = getchar();
        while(getchar() != '\n');
        switch(c){
            case 'o' :
            case 'O' :
            case 'n' :
            case 'N' :
            case '0' :
            case '1' :
            case '2' :
            case '3' :
                printf("C'est un bon caractère\n");
                break;
            default :
                printf("Mauvais caractère\n");
        }
    } while(c != 'n' && c !='N');
    */

    /*
    char i;
    for (i = 'A'; i <= 'Z'; i++){
        printf("caractère %c, décimal %d, hexadécimal %x\n", i, i, i);
    }
    for (i = 'a'; i <= 'z'; i++){
        printf("caractère %c, décimal %d, hexadécimal %x\n", i, i, i);
    }
    */

    /*
    char i;
    for (i = 31; i <= 127; i++){
        printf("ASCII : %d, Catactère : %c\n", i, i);
    }
    */

    /*
    int i;

    i = 0;
    do{
        printf("%d", i);
        i++;
    } while(i <= 9);

    printf("\n");

    i = 0;
    while (i <= 9){
        printf("%d", i);
        i++;
    }

    printf("\n");

    for (i=0; i<=9; i++) {
        printf("%d", i);
    }
    */

    return 0;
}
