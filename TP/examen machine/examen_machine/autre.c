#include <stdio.h>
#include <stdlib.h>
#include "autre.h"

int facIter(int n){

    if (n < 0)
    {
        return 0;
    }
    if (n == 1 || n == 0)
    {
        return 1;
    }

    int total = 2;
    for (int i = 3; i <= n; i++)
    {
        total *= i;
    }
    return total;
}

int facRecur(int n){
    if (n < 0)
    {
        return 0;
    }
    if (n == 1 || n == 0)
    {
        return 1;
    }
    return n * facRecur(n-1);
}


/*================================================================================================================================*/

int puissance(long n, int p)
{
    if (p == 0)
    {
        return 1;
    }
    return n * puissance(n, p-1);
}


int palindrome(long n)
{
    long unite = n % 10;
    long plus_grand = n;
    int p = 0;

    while (plus_grand > 9)
    {
        plus_grand /= 10;
        p++;
    }

    if (plus_grand != unite)
    {
        return 0;
    }

    plus_grand *= puissance(10, p);

    n-= plus_grand;
    n /= 10;

    if (n == 0)
    {
        return 1;
    }

    return palindrome(n);
}

//====================================================================================================//

/*
Parcours_it ( A : Arbre ; type : Enum )
    P := creer_pile ()
    N := 1
    x := racine [ A ]
    TantQue P != vide ou ( N = 1 et x != NIL )
        Si N = 1 et x != NIL
            Si type = Prefixe
                afficher ( x )
            empiler (P , (x , 1) )
            x := gauche [ x ] // Descente a gauche
        Sinon
            (x , N ) := depiler ( P )
            Si N =1 // Remonte de la gauche
                Si type = Infixe
                    afficher ( x )
                empiler (P , (x ,2) )
                x := droit [ x ] // Descente a droite
            Si N =2 // Remonte de la droite
                Si type = Postfixe
                    afficher ( x )

*/
