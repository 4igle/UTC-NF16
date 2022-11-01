#ifndef TP4_H_INCLUDED
#define TP4_H_INCLUDED


// les structures phrase et liste_phrases sont egalement utilisees
// pour faire des lignes et des listes de lignes, nous n'avons pas cree de structure
// supplementaire pour les lignes, car elles seraient identiques.
typedef struct Phrase{
    char *mot;
    struct Phrase *suivant;
} phrase;

typedef struct ListePhrases{
    phrase *phrase;
    struct ListePhrases *suivant;
}liste_phrases;

typedef struct t_position{
    int numero_ligne;
    int ordre;
    int numero_phrase;
    struct t_position *suivant;
}t_Position;

typedef struct t_listePositions{
    t_Position *debut;
    int nb_elements;
}t_ListePositions;

typedef struct t_noeud{
    char *mot;
    int nb_occurences;
    t_ListePositions *positions;
    struct t_noeud *filsGauche;
    struct t_noeud *filsDroit;
}t_Noeud;

typedef struct t_index{
    t_Noeud *racine;
    int nb_mots_differents;
    int nb_mots_total;
    liste_phrases *liste_phrases;
    liste_phrases *liste_lignes;
}t_Index;



t_ListePositions* creer_liste_positions();
int ajouter_position(t_ListePositions *listeP, int ligne, int ordre, int num_phrase);
t_Index* creer_index();
t_Noeud* rechercher_mot(t_Index *index, char *mot);
int ajouter_noeud(t_Index *index, t_Noeud *noeud);
int indexer_fichier(t_Index *index, char *filename);
void afficher_index(t_Index *index);
void afficher_max_apparition(t_Index *index);
void afficher_occurences_mot(t_Index *index, char *mot);
void construire_texte(t_Index *index, char *filename);

//ajouter en plus
void minuscule(char *mot);
char majuscule(char c);
void afficher_noeud(t_Noeud *noeud);
void afficher_arbre(t_Noeud *noeud, char *dernier);
t_Noeud * trouver_max(t_Noeud *noeud);
phrase * initialiser_phrase(char * mot);
void ajouter_mot(phrase *liste, char *mot);
void ajouter_phrase(t_Index *index, phrase *p);
void ajouter_ligne(t_Index *index, phrase *p);
void liberer_arbre(t_Noeud *racine);
void liberer_liste_phrases(liste_phrases *liste);
int equilibre(t_Noeud *racine);
int hauteur(t_Noeud *racine);


#endif // TP4_H_INCLUDED
