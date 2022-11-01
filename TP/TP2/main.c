#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "time.h"
#include "fonctions.c"


int main()
{
    // Ex 1.1, Ex 1.2
    /*
    printf("Itératif : %d, récursif : %d", fact1(5), fact2(5));
    return 0;
    */

    // Ex 1.3

    matrice m;
    int dimension;
    lecture(m, &dimension);
    affichage(m, dimension);
    printf("\n");
    float d = determinant(m, dimension);
    printf("Determinant : %f\n", d);


    // Ex 1.4
    /*
    clock_t start, end;
    double elapsed;
    start = clock(); // Lancement de la mesure
    printf("%d\n", fibo2(14));
    end = clock(); // Arrêt de la mesure
    elapsed = ((double)end - start) / CLOCKS_PER_SEC;
    printf("%f secondes \n\n", elapsed);

    elapsed = 0;
    start = clock(); // Lancement de la mesure
    printf("%d\n", fibo1(14));
    end = clock(); // Arrêt de la mesure
    elapsed = ((double)end - start) / CLOCKS_PER_SEC;
    printf("%f secondes", elapsed);
    */

    // Ex 2.1
    /*
    Un_Tableau_Entier A;
    A.ncase = 0;
    */

    /*
    tonneau t;
    t.L = 10.0;
    t.d = 30.0;
    t.D = 50.0;
    t.contenant[0] = 'V';
    t.contenant[1] = 'I';
    t.contenant[2] = 'N';
    afficher_tonneau(t);
    */

    return 0;

}



