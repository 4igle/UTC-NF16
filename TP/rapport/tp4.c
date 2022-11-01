#include "tp4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE_MAX 1000

// creation d'une liste de positions
t_ListePositions* creer_liste_positions()
{
    // on alloue la memoire pour la liste
    t_ListePositions *nouv=malloc(sizeof(t_ListePositions));
    if(nouv!=NULL)
    {
        nouv->debut=NULL;
        nouv->nb_elements=0;
    }
    return nouv;
}


// ajout d'une position dans la liste
int ajouter_position(t_ListePositions *listeP, int ligne, int ordre, int num_phrase)
{
    // si la position est non valide
    if (ligne < 1 || ordre < 1 || num_phrase < 1)
    {
        printf("Erreur: numero de ligne, ordre ou numero de phrase invalide\n");
        return 0;
    }

    // si la liste n'est pas initialisee
    if (listeP == NULL)
    {
        printf("Erreur: liste de positions non initialisee\n");
        return 0;
    }

    t_Position *actuel=listeP->debut;
    t_Position *precedent=NULL;
    t_Position *nouv=malloc(sizeof(t_Position));
    if(nouv!=NULL)
    {
        nouv->numero_ligne=ligne;
        nouv->ordre=ordre;
        nouv->numero_phrase=num_phrase;
        nouv->suivant=NULL;

        // si la liste est vide
        if(actuel==NULL)
        {
            listeP->debut=nouv;
            listeP->nb_elements=1;
        }
        else
        {
            // on parcourt la liste jusqu'a la fin ou jusqu'a la position a ajouter
            while(actuel!=NULL && (actuel->numero_ligne<ligne || actuel->ordre<ordre))
            {
                precedent=actuel;
                actuel=actuel->suivant;
            }
            // si la position existe deja
            if (actuel != NULL && actuel->numero_ligne == ligne && actuel->ordre == ordre)
            {
                printf("Erreur: position deja existante\n");
                return 0;
            }
            // si on ajoute au debut de la liste
            if(precedent==NULL)
            {
                nouv->suivant=listeP->debut;
                listeP->debut=nouv;
            }
            // si on ajoute a la fin de la liste
            else if(actuel==NULL)
            {
                precedent->suivant=nouv;
            }
            // sinon on ajoute au milieu de la liste, entre deux elements
            else
            {
                nouv->suivant=actuel;
                precedent->suivant=nouv;
            }
            listeP->nb_elements++;
        }
        return 1;
    }
    else
    {
        printf("Erreur: allocation memoire\n");
        return 0;
    }
}

// creation de l'index
t_Index* creer_index()
{
    t_Index *nouv=malloc(sizeof(t_Index));
    if(nouv!=NULL)
    {
        nouv->nb_mots_differents=0;
        nouv->nb_mots_total=0;
        nouv->racine=NULL;
        nouv->liste_lignes = NULL;
        nouv->liste_phrases = NULL;
    }
    return nouv;
}

// recherche d'un mot dans l'index
t_Noeud* rechercher_mot(t_Index *index, char *mot)
{
    if (index == NULL || mot == NULL)
    {
        return NULL;
    }

    t_Noeud *noeud=index->racine;
    // les mots sont stockes en minuscule dans l'arbre, on convertit donc le mot recherche en minuscule
    minuscule(mot);

    // on utilise le principe de recherche dichotomique
    while(noeud!=NULL && strcmp(noeud->mot,mot)!=0)
    {
        if(strcmp(noeud->mot,mot)>0)
        {
            noeud=noeud->filsGauche;
        }
        else
        {
            noeud=noeud->filsDroit;
        }
    }
    return noeud;
}

// fonction qui convertit une chaine de caracteres en minuscule
void minuscule(char *mot)
{
    if (mot == NULL)
    {
        return;
    }
    for(int i=0;i<strlen(mot);i++)
    {
        if(mot[i]>='A' && mot[i]<='Z')
        {
            mot[i]=mot[i]+32;
        }
    }
}

// fonction qui renvoie la version minuscule d'un caractere
char majuscule(char c)
{
    if(c>='a' && c<='z')
    {
        return c-32;
    }
    else
    {
        return c;
    }
}

// fonction qui ajoute un noeud dans l'index
int ajouter_noeud(t_Index *index, t_Noeud *noeud)
{
    if (index == NULL || noeud == NULL)
    {
        return 0;
    }

    // on verifie que le mot n'existe pas deja
    if(rechercher_mot(index,noeud->mot)==NULL)
    {
        t_Noeud *pere=NULL;
        t_Noeud *actuel=index->racine;

        // on cherche ou inserer le noeud
        while(actuel!=NULL)
        {
            pere=actuel;
            if(strcmp(actuel->mot,noeud->mot)>0)
            {
                actuel=actuel->filsGauche;
            }
            else
            {
                actuel=actuel->filsDroit;
            }
        }

        // si le noeud est a inserer a la racine (premier noeud)
        if(pere==NULL)
        {
            index->racine=noeud;
        }

        // sinon on insere le noeud dans l'arbre
        else
        {
            if(strcmp(pere->mot,noeud->mot)>0)
            {
                pere->filsGauche=noeud;
            }
            else
            {
                pere->filsDroit=noeud;
            }
        }
        return 1;
    }
    else
    {
        printf("Erreur: noeud deja existant\n");
        return 0;
    }
}

// fonction qui lit un fichier et ajoute ses mots dans l'index
int indexer_fichier(t_Index *index, char *filename)
{
    if (index == NULL || filename == NULL)
    {
        return 0;
    }

    int nb_mots=1;
    int num_phrase=1;
    FILE* fichier = NULL;
    char chaine[TAILLE_MAX] = "";
    unsigned long taille;
    int changer_phrase=0;
    phrase *phrase_courante=NULL;
    int nouvelle_phrase=1;
    phrase *ligne_courante=NULL;
    int nouvelle_ligne=1;

    fichier = fopen(filename, "r");


    // on verifie que le fichier existe et qu'on a reussi a l'ouvrir
    if (fichier != NULL)
    {
        int ligne=1;
        int ordre;
        const char * separateurs = " ";

        // on lit le fichier ligne par ligne
        while (fgets(chaine, TAILLE_MAX, fichier) != NULL)
        {
            // si la ligne est vide (saut de ligne), on passe a l'iteration suivante
            if (strcmp(chaine, "\n") == 0)
            {
                continue;
            }

            ordre=1;

            // on convertit la chaine de caracteres en minuscule
            minuscule(chaine);

            // on remplace le retour a la ligne par une fin de chaine
            taille = strlen(chaine);
            if (chaine[taille-1] == '\n')
            {
                chaine[taille - 1] = '\0';
            }

            // on lit les mots de la ligne un a un, les mots etant separes par des espaces
            char * mot = strtok ( chaine, separateurs );

            while ( mot != NULL )
            {
                taille = strlen(mot);

                // si le dernier caractere est un point, on le retire et on stocke le fait qu'on change de phrase,
                // afin de declencher le code de changement de phrase plus tard dans la fontion
                if (mot[taille-1] == '.')
                {
                    mot[taille - 1] = '\0';
                    changer_phrase=1;
                }

                // on recherche le mot a ajouter pour savoir si il faut creer un nouveau noeud ou juste ajouter une position
                t_Noeud *noeud=rechercher_mot(index,mot);

                // mot non existant dans l'index, creation du noeud
                if (noeud==NULL)
                {
                    noeud=malloc(sizeof(t_Noeud));
                    t_ListePositions *listeP=creer_liste_positions();
                    if(noeud!=NULL && listeP!=NULL)
                    {
                        noeud->mot = malloc(sizeof(mot));
                        strcpy(noeud->mot,mot);

                        noeud->nb_occurences=1;

                        noeud->filsGauche=NULL;
                        noeud->filsDroit=NULL;

                        ajouter_position(listeP,ligne,ordre,num_phrase);
                        noeud->positions=listeP;

                        ajouter_noeud(index,noeud);

                        index->nb_mots_differents++;
                        index->nb_mots_total++;
                    }
                    else
                    {
                        printf("Erreur: allocation memoire\n");
                        return 0;
                    }
                }
                // mot existant dans l'index, ajout de la position

                else
                {
                    noeud->nb_occurences++;
                    ajouter_position(noeud->positions,ligne,ordre,num_phrase);
                    index->nb_mots_total++;
                }

                // si on a change de phrase, on en cree une nouvelle
                if (nouvelle_phrase==1)
                {
                    phrase_courante = initialiser_phrase(mot);
                    nouvelle_phrase=0;
                }
                // sinon on ajoute le mot a la phrase courante
                else
                {
                    ajouter_mot(phrase_courante,mot);
                }

                // si on a change de ligne, on en cree une nouvelle
                if (nouvelle_ligne==1)
                {
                    ligne_courante = initialiser_phrase(mot);
                    nouvelle_ligne=0;
                }
                // sinon on ajoute le mot a la ligne courante
                else
                {
                    ajouter_mot(ligne_courante,mot);
                }


                mot = strtok ( NULL, separateurs );
                ordre++;
                nb_mots++;

                // si on change de phrase, on ajoute la phrase courante a la liste de phrases de l'index,
                // on incremente le numero de phrase, et on annonce qu'on a change de phrase pour l'iteration suivante
                if (changer_phrase==1)
                {
                    ajouter_phrase(index,phrase_courante);
                    num_phrase++;
                    changer_phrase = 0;
                    nouvelle_phrase=1;
                }
            }

            // on change de ligne, donc on ajoute la ligne courante a la liste de lignes de l'index,
            // on incremente le numero de ligne, et on annonce qu'on a change de ligne pour l'iteration suivante
            ligne++;
            ajouter_ligne(index,ligne_courante);
            nouvelle_ligne=1;
        }
        fclose(fichier);
        return nb_mots;
    }
    else
    {
        printf("Erreur: fichier non trouve\n");
        return 0;
    }
}

// fonction qui affiche le mot d'un noeud et ses positions
void afficher_noeud(t_Noeud *noeud)
{
    if (noeud == NULL)
    {
        return;
    }
    // on affiche le mot avec sa premiere lettre en majuscule
    noeud->mot[0]=majuscule(noeud->mot[0]);
    printf("|-- %s\n",noeud->mot);
    minuscule(noeud->mot);
    t_Position *pos=noeud->positions->debut;

    // on affiche les positions du mot
    while(pos!=NULL)
    {
        printf("|---- (l:%d, o:%d, p:%d)\n", pos->numero_ligne, pos->ordre, pos->numero_phrase);
        pos = pos->suivant;
    }
    printf("|\n");
}

// afficher l'index : parcours de l'arbre
void afficher_index(t_Index *index)
{
    if (index == NULL)
    {
        return;
    }
    t_Noeud *noeud = index->racine;

    // on initialise l'initiale du dernier mot affiche
    char dernier[] = "_";
    if (noeud != NULL)
    {
        afficher_arbre(noeud, dernier);
    }
    else
    {
        printf("Aucun mot dans l'index\n");
    }
}

// algo parcours infixe vu en cours pour parcourir par ordre alphabetique
void afficher_arbre(t_Noeud *noeud, char *dernier)
{
    if(noeud!=NULL && dernier != NULL)
    {
        // affichage du sous arbre gauche
        afficher_arbre(noeud->filsGauche, dernier);

        // affichage du noeud courant
        // on affiche l'initiale du mot si elle est differente de l'initiale du dernier mot affiche
        if (dernier[0] == '_' || majuscule((noeud->mot)[0]) != dernier[0] )
        {
            printf("\n%c\n", majuscule((noeud->mot)[0]));
            dernier[0] = majuscule((noeud->mot)[0]);

            // on affiche le noeud
            afficher_noeud(noeud);
        }
        else
        {
            // on affiche le noeud
            afficher_noeud(noeud);
        }

        // affichage du sous arbre droit
        afficher_arbre(noeud->filsDroit, dernier);
    }
}

// fonction qui affiche le mot le plus present dans l'index, avec son nombre d'occurences
void afficher_max_apparition(t_Index *index)
{
    if (index == NULL)
    {
        return;
    }
    t_Noeud *noeud = index->racine;
    if (noeud != NULL)
    {
        noeud = trouver_max(noeud);
        printf("\nLe mot le plus apparu est : %s, avec %d occurences\n", noeud->mot, noeud->nb_occurences);
    }
    else
    {
        printf("\nAucun mot dans l'index\n");
    }
}

// fonction qui trouve le noeud representant le mot le plus present dans l'index
// voici le principe : pour chaque arbre / sous abre, le noeud representant le mot le plus present, celui ayant le nombre
// max d'occurences, est le maximum entre le nombre d'occurences du mot de la racine, et le max du sous arbre gauche, et du sous arbre droit

// grossierement, la fonction revient a ce principe :
// max_occurences(r) = max(r, max_occurences(r->filsGauche), max_occurences(r->filsDroit))

t_Noeud * trouver_max(t_Noeud *noeud)
{
    if (noeud != NULL)
    {
        // on recupere les max des deux sous arbres (noeuds representant les mots qui apparaissent le plus)
        t_Noeud * max_gauche = trouver_max(noeud->filsGauche);
        t_Noeud * max_droit = trouver_max(noeud->filsDroit);

        // on gere les quatre cas : le noeud courant a deux fils, n'a pas de fils, n'a que le fils gauche, et n'a que le fils droit
        // pour chacun de ces cas on retourne le noeud representant le mot le plus present
        if (max_gauche != NULL && max_droit != NULL)
        {
            if (max_gauche->nb_occurences > max_droit->nb_occurences)
            {
                if (noeud->nb_occurences > max_gauche->nb_occurences)
                {
                    return noeud;
                }
                else
                {
                    return max_gauche;
                }
            }
            else
            {
                if (noeud->nb_occurences > max_droit->nb_occurences)
                {
                    return noeud;
                }
                else
                {
                    return max_droit;
                }
            }
        }
        else if (max_gauche != NULL)
        {
            if (noeud->nb_occurences > max_gauche->nb_occurences)
            {
                return noeud;
            }
            else
            {
                return max_gauche;
            }
        }
        else if (max_droit != NULL)
        {
            if (noeud->nb_occurences > max_droit->nb_occurences)
            {
                return noeud;
            }
            else
            {
                return max_droit;
            }
        }
        else
        {
            return noeud;
        }
    }
    return NULL;
}

// fonction qui cree une phrase (liste chainee de mots)
// cette fonction peut donc aussi servir a initialiser un mot qui ne sera pas forcement le premier de sa phrase.
phrase * initialiser_phrase(char * mot)
{

    if (mot == NULL)
    {
        return NULL;
    }

    phrase *p = malloc(sizeof(phrase));
    if (p != NULL)
    {
        p->mot = malloc(sizeof(mot));
        strcpy(p->mot, mot);
        p->suivant = NULL;
    }
    return p;
}

// fonction qui ajoute un mot a une phrase deja existante
void ajouter_mot(phrase *liste, char *mot)
{
    if (liste != NULL && mot != NULL)
    {
        if (liste->suivant == NULL)
        {
            liste->suivant = initialiser_phrase(mot);
        }
        else
        {
            // si liste n'est pas un pointeur sur le dernier element de la liste chainee,
            // on fait appel a la fonction avec le suivant de liste, ceci est l'equivalent recursif du parcours de la liste
            // avec une boucle while
            ajouter_mot(liste->suivant, mot);
        }
    }
}

// fonction qui ajoute une phrase a la liste de phrases de l'index
void ajouter_phrase(t_Index *index, phrase *p)
{
    if (index == NULL || p == NULL)
    {
        return;
    }
    liste_phrases * nouv = malloc(sizeof(liste_phrases));
    if (nouv != NULL)
    {
        nouv->phrase = p;
        nouv->suivant = NULL;
        if (index->liste_phrases == NULL)
        {
            index->liste_phrases = nouv;
        }
        else
        {
            liste_phrases *courant = index->liste_phrases;
            while (courant->suivant != NULL)
            {
                courant = courant->suivant;
            }

            courant->suivant = nouv;
        }
    }
}

// fonction qui ajoute une ligne a la liste de lignes de l'index
void ajouter_ligne(t_Index *index, phrase *p)
{
    if (index == NULL || p == NULL)
    {
        return;
    }
    liste_phrases * nouv = malloc(sizeof(liste_phrases));
    if (nouv != NULL)
    {
        nouv->phrase = p;
        nouv->suivant = NULL;
        if (index->liste_lignes == NULL)
        {
            index->liste_lignes = nouv;
        }
        else
        {
            liste_phrases *courant = index->liste_lignes;
            while (courant->suivant != NULL)
            {
                courant = courant->suivant;
            }
            courant->suivant = nouv;
        }
    }
}

// fonction qui affiche les phrases dans lesquelles se trouve un mot donne
void afficher_occurences_mot(t_Index *index, char *mot)
{
    if (index == NULL || mot == NULL)
    {
        return;
    }
    int debut_phrase;
    int i = 1;
    liste_phrases *p = index->liste_phrases;
    phrase *m = NULL;
    minuscule(mot);
    t_Noeud *noeud = rechercher_mot(index, mot);
    if (noeud != NULL)
    {
        mot[0] = majuscule(mot[0]);
        printf("Mot = \"%s\"\n", mot);
        printf("Occurences = %d\n", noeud->nb_occurences);
        t_Position *pos = noeud->positions->debut;
        while (pos != NULL)
        {
            debut_phrase = 1;

            // on retrouve la phrase grace a la liste de phrases
            while (i < pos->numero_phrase)
            {
                p = p->suivant;
                i++;
            }
            printf("| Ligne %d, mot %d : ", pos->numero_ligne, pos->ordre);
            m = p->phrase;
            while (m != NULL)
            {
                if (debut_phrase)
                {
                    m->mot[0] = majuscule(m->mot[0]);
                    printf("%s", m->mot);
                    minuscule(m->mot);
                    debut_phrase = 0;
                }
                else
                {
                    printf("%s", m->mot);
                }
                if (m->suivant != NULL)
                {
                    printf(" ");
                }
                m = m->suivant;
            }
            printf(".\n");
            pos = pos->suivant;
        }
    }
    else
    {
        printf("Le mot '%s' n'est pas dans l'index\n", mot);
    }
}

// fonction qui reconstruit le texte stocke dans l'index et le place dans un fichier
// on iterera a la fois sur la liste de lignes et sur la liste de phrases de l'index
// afin de savoir quand placer les points et quand placer les retours a la ligne
void construire_texte(t_Index *index, char *filename)
{
    if (index == NULL || filename == NULL)
    {
        return;
    }
    int debut_phrase = 1;
    FILE *f = fopen(filename, "w");
    if (f != NULL)
    {
        liste_phrases *l = index->liste_lignes;
        liste_phrases *lp = index->liste_phrases;
        phrase *m = lp->phrase;
        while (l != NULL)
        {
            phrase *p = l->phrase;
            while (p != NULL)
            {
                if (m->suivant != NULL)
                {
                    m = m->suivant;

                    // on met des majuscules en debut de phrase
                    if (debut_phrase == 1)
                    {
                        p->mot[0] = majuscule(p->mot[0]);
                        fprintf(f, "%s ", p->mot);
                        minuscule(p->mot);
                        debut_phrase = 0;
                    }
                    else
                    {
                        fprintf(f, "%s ", p->mot);
                    }
                }

                // on met des points en fin de phrase
                else
                {
                    lp = lp->suivant;
                    if (lp != NULL)
                    {
                        m = lp->phrase;
                    }

                    // on met des majuscules en debut de phrase
                    if (debut_phrase == 1)
                    {
                        p->mot[0] = majuscule(p->mot[0]);
                        fprintf(f, "%s. ", p->mot);
                        minuscule(p->mot);
                    }
                    else
                    {
                        fprintf(f, "%s. ", p->mot);
                        debut_phrase = 1;
                    }
                }
                p = p->suivant;
            }
            // change de ligne en fin de ligne
            fprintf(f, "\n");
            l = l->suivant;
        }
        fclose(f);
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier\n");
    }
}

// fonction qui libere la memoire allouee pour les noeuds et toutes les autres structures
// pour lesquelles on a alloue manuellement de la memoire qui concerne les noeuds (les positions par exemple)
void liberer_arbre(t_Noeud *racine)
{
    if (racine != NULL)
    {
        liberer_arbre(racine->filsGauche);
        liberer_arbre(racine->filsDroit);

        if (racine->positions != NULL)
        {
            t_Position *pos = racine->positions->debut;
            t_Position *suivant = NULL;
            while (pos != NULL)
            {
                suivant = pos->suivant;
                free(pos);
                pos = suivant;
            }
            free(racine->positions);
        }
        free(racine);
    }
}

// fonction qui libere la memoire allouee pour une liste de phrases et pour les phrases qui la composent
// on peut egalement faire appel a cette fonction pour liberer une liste de ligne
void liberer_liste_phrases(liste_phrases *liste)
{
    if (liste != NULL)
    {
        liberer_liste_phrases(liste->suivant);

        phrase *pos = liste->phrase;
        phrase *suivant = NULL;
        while (pos != NULL)
        {
            suivant = pos->suivant;
            free(pos);
            pos = suivant;
        }

        free(liste);
    }
}

// Fonction qui renvoie la hauteur de l'arbre si l'arbre est equilibre, -2 sinon
int equilibre(t_Noeud *racine)
{
    if (racine == NULL)
    {
        return -1;
    }
    else
    {
        int gauche = equilibre(racine->filsGauche);
        int droit = equilibre(racine->filsDroit);

        // Si l'ecart entre la hauteur des deux sous arbres est superieur a 1, alors l'arbre n'est pas equilibre
        // Si un des deux sous arbres n'est pas equilibre, alors l'arbre n'est pas equilibre
        if (abs(gauche - droit) > 1 || gauche == -2 || droit == -2)
        {
            return -2;
        }

        if (gauche > droit)
        {
            return gauche + 1;
        }
        else
        {
            return droit + 1;
        }
    }
}

// Fonction qui renvoie la hauteur de l'arbre
int hauteur(t_Noeud *racine)
{
    if (racine == NULL)
    {
        return -1;
    }
    else
    {
        int gauche = hauteur(racine->filsGauche);
        int droit = hauteur(racine->filsDroit);

        if (gauche > droit)
        {
            return gauche + 1;
        }
        else
        {
            return droit + 1;
        }
    }
}
