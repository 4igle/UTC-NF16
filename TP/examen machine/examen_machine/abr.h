#ifndef ABR_H_INCLUDED
#define ABR_H_INCLUDED

typedef struct structnoeud{
    int valeur;
    struct structnoeud * gauche;
    struct structnoeud * droit;
} structnoeud;

typedef structnoeud * arbre;

int max(arbre a);
int min(arbre a);


/*===================================*/

typedef struct res{
    int beg;
    int end;
    struct res * pere;
    struct res * gauche;
    struct res * droit;
} res;

res * create_reservation(int beg, int end);
res * mini(res * root);
void delete_reservation(res *root, res * r);
res * add_reservation(res * root, res * r);
res * search_reservation(res * root, res * r);
void print_reservations(res * root, int order);
void real_print(res * root);

#endif // ABR_H_INCLUDED
