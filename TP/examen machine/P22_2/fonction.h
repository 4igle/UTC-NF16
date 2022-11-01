#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

typedef struct element{
    int valeur;
    struct element * suivant;
} element;

typedef element * liste;



element * creer_element(int val);
void ajouter_element(liste * l, element * n);
liste construire_liste();
void afficher_liste(liste l);
liste inverser_liste(liste l);
void tri(liste *l);


typedef struct noeud{
    int valeur;
    struct noeud * gauche;
    struct noeud * droite;
} noeud;

typedef noeud * arbre;

noeud * creer_noeud(int val);
void ajouter_noeud(arbre * a, noeud * n);
arbre construire_arbre();
void afficher_arbre(arbre a);
void afficher_arbre_propre(arbre a);
int nombre_feuilles(arbre a);
int nombre_noeuds(arbre a);
int nombre_noeuds_internes(arbre a);
int hauteur(arbre a);

#endif // FONCTION_H_INCLUDED
