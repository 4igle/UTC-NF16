#ifndef PILE_L_DOUBLE_H_INCLUDED
#define PILE_L_DOUBLE_H_INCLUDED

typedef struct noeud{
int valeur;
struct noeud *precedent;
struct noeud *suivant;
} Noeud;

typedef struct Liste {
    Noeud * tete;
    Noeud * queue;
    Noeud * sentinelle;
}Liste;


Noeud * creerNoeud(int cle);
void supprimerNoeud(Noeud * noeud);
Liste * creerListeVide();
void afficherContenuListe(Liste * liste);
int listeVide(Liste *liste);
void viderListe(Liste * liste);
void ajouterQueueListe(Liste * liste, int cle);
Noeud * obtenirDernierElement(Liste * liste);
void supprimerListe(Liste * liste);
int depiler(Liste * pile);
void empiler(Liste * pile, int val);

/*=======================================================================================*/
/*=======================================================================================*/
/*=======================================================================================*/

typedef struct ListNode{
int data;
struct ListNode *prev;
struct ListNode *next;
} ListElem;


void inserer(ListElem **liste, int val, int pos);
void affichertout(ListElem *L);
int nombrelement(ListElem *L);

//=======================================================================================//


unsigned int lireExpression(char * expression);


#endif // PILE_L_DOUBLE_H_INCLUDED
