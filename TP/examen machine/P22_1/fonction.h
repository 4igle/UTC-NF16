#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

typedef struct Client{
    char * nom;
    char * prenom;
    char * code_postal;
    unsigned int nb_passages;
    struct Client * suivant;
} T_Client;

typedef T_Client * T_Liste;

T_Liste ajouter(T_Liste maListe, char * nom, char * prenom, char * code_postal, int nb_p);
T_Liste supprimer(T_Liste maListe, char * nom, char * prenom);
void affichage(T_Liste maListe);
void vider(T_Liste maListe);

typedef struct Sommet{
    int cle;
    struct Sommet * fils_gauche;
    struct Sommet * fils_droit;
    struct Sommet * pere;
}T_Sommet;

typedef T_Sommet * T_Arbre;

void insererSommet(T_Arbre * arbre, int val);
void afficherArbre(T_Arbre arbre);
int successeur(T_Sommet * sommet);
void supprimerSommet(T_Arbre * arbre, int val);
int hauteurArbre(T_Arbre arbre);
void viderArbre(T_Arbre * arbre);

#endif // FONCTION_H_INCLUDED
