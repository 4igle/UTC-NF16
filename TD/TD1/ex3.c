#include <stdio.h>
#include <stdlib.h>

int main3() {

    printf("Entrez un caractère\n");
    switch(getchar()) {
        case '1':
            printf("C'est un\n");
            break;
        case '2':
            printf("C'est deux\n");
            break;
        case '3':
            printf("C'est trois\n");
            break;
        default:
            printf("C'est autre chose...\n");
    }

    /*
    char c;
    printf("Entrez caractère: ");
    scanf("%c", &c);

    if (c >= '0' && c <= '9') {
        printf("Chiffre");
    }
    else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        printf("Lettre");
    }
    */

    /*
    int nombre;
    printf("Entrez nombre: ");
    scanf("%d", &nombre);

    if (nombre != 0) {
        printf("Message");
    }
    */

    /*
    int nombre;
    printf("Entrez nombre: ");
    scanf("%d", &nombre);

    if ((nombre >= 7 && nombre <= 20) || (nombre == 127)) {
        printf("Message");
    }
    */

    /*
    int nombre;
    printf("Entrez nombre: ");
    scanf("%d", &nombre);

    if (nombre >= 0 && nombre <= 10) {
        printf("Message");
    }
    */

    return 0;
}
