#ifndef NF16_FONCTION_H
#define NF16_FONCTION_H

// structure electeur
typedef struct electeur{
    char *nom;
    long cin_num;
    int choix;
    struct electeur *suivant;
} electeur;

// pointeur vers electeur
typedef electeur *T_Electeur;

// prototype des fonctions
T_Electeur creationelecteur(void);
void afficheliste(T_Electeur);
void ajoutelecteur(T_Electeur *, char [], long, int);
int comptelecteur(T_Electeur);
int trouvelecteur(T_Electeur, long);
void Supprimelecteur(T_Electeur *, long);
void decoupeliste(T_Electeur, T_Electeur *, T_Electeur *, T_Electeur *);
void triliste(T_Electeur *);
T_Electeur fusionlistes(T_Electeur, T_Electeur);
int compteGD(T_Electeur);
void libereliste(T_Electeur);


#endif //NF16_FONCTION_H
