#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pile_l_double.h"
#include "abr.h"
#include "autre.h"





int main5() // abr reservations
{
    res * r1 = create_reservation(1, 2);
    res * r2 = create_reservation(3, 4);
    res * r3 = create_reservation(10, 12);
    res * r4 = create_reservation(14, 15);
    res * r5 = create_reservation(19, 23);
    res * r6 = create_reservation(8, 9);
    res * r7 = create_reservation(5, 6);
    res * r8 = create_reservation(7, 7);


    add_reservation(r3, r2);
    add_reservation(r3, r1);
    add_reservation(r3, r4);
    add_reservation(r3, r5);
    add_reservation(r3, r6);
    add_reservation(r3, r7);
    add_reservation(r3, r8);

    //print_reservations(r3, 0);
    real_print(r3);

    delete_reservation(r3, r2);

    printf("\n\n");
    real_print(r3);

    return 0;
}


int main4() // palindrome
{
    long max = 0;
    int mi, mj;
    for (int i = 100; i <= 999; i++)
    {
        for (int j = 100; j <= 999; j++)
        {
            if (palindrome(i * j) == 1 && i * j > max)
            {
                max = i * j;
                mi = i;
                mj = j;
            }
        }
    }
    printf("%d * %d = %ld\n", mi, mj, max);
    return 0;
}



int main3() // pi
{
    int occurences = 10000;
    int range = 100000;
    float x, y;
    int cercle = 0;

    srand(time(NULL));
    for (int i = 0; i < occurences; i++)
    {
        x = (float) (rand() % range) / range;
        y = (float) (rand() % range) / range;

        if (x*x + y*y < 1)
        {
            cercle++;
        }
    }

    float pi = 4 * ((float) cercle/occurences);
    printf("Pi : %f\n", pi);
    return 0;
}


int main2() // notation polonaise
{
    printf("%d", lireExpression("5 9 8 + 4 6 * * 7 + +"));
    return 0;
}

int main1() // pile
{
    srand(time(NULL));
    Liste * p = creerListeVide();
    int val = 0;
    for (int i = 0; i < 5; i++)
    {
        val = rand() % 10;
        empiler(p, val);
    }
    afficherContenuListe(p);
    depiler(p);
    depiler(p);
    afficherContenuListe(p);
    return 0;
}
