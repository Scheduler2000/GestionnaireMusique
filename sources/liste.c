#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/liste.h"
#define TAILLE_MAX_BIBLIOTHEQUE 100

t_liste* InitialiserBibliothequeMusicale()
{
    t_liste* liste = malloc(sizeof(t_liste));
    if(liste == NULL)
        return NULL;
    liste->premier = NULL;
    liste->taille = 0;
    printf("\n\t\t Bibliotheque musicale initialisee\n\n");
    return liste;
}

int AjouterMusique(t_liste* liste, char* titre, int annee, char* genre, float duree)
{
    t_maillon* maillon = (t_maillon*)malloc(sizeof(t_maillon));
    maillon->titre = (char*)malloc((strlen(titre) + 1)*sizeof(char));
    maillon->morceau = (t_morceau*)malloc(sizeof(t_morceau));
    maillon->morceau->genre = (char*)malloc((strlen(genre) + 1)*sizeof(char));

    if(liste == NULL || maillon == NULL || maillon->titre == NULL  || maillon->morceau->genre == NULL)
        return 0;
    if(liste->taille >= TAILLE_MAX_BIBLIOTHEQUE)
    {
        printf("Votre bibliotheque est pleine vider là pour pouvoir ajouter des musiques !\n");
        return 0;
    }

    if(RechercherMusique(liste,titre) == NULL)
    {
        strcpy(maillon->titre,titre);
        maillon->annee = annee;
        strcpy(maillon->morceau->genre,genre);
        maillon->morceau->duree = duree;
        maillon->suivant = liste->premier;
        liste->premier = maillon;
        liste->taille++;
    }
    else
    {
        printf("La musique est deja dans votre bibliotheque !\n");
        return 0;
    }
    return 1;
}

int SupprimerMusique(t_liste* liste, char* titre)
{
    t_maillon *maillonCourant = malloc(sizeof(t_maillon));
    t_maillon *maillonSuivant = malloc(sizeof(t_maillon));
    int i;
    int value = 0;

    if(liste == NULL || maillonCourant == NULL || maillonSuivant == NULL ||liste->premier == NULL)
        return 0;
    if(strcmp(liste->premier->titre,titre) == 0)
    {
        maillonCourant = liste->premier;
        maillonSuivant = maillonCourant->suivant;
        liste->premier = maillonSuivant;
        free(maillonCourant);
        liste->taille--;
    }
    else
    {
        maillonCourant = liste->premier;
        for(i = 0; i < liste->taille && !value; i++)
        {
            maillonSuivant = maillonCourant->suivant;
            if(strcmp(titre, maillonSuivant->titre) == 0)
            {
                maillonCourant->suivant = maillonSuivant->suivant;
                free(maillonSuivant);
                liste->taille--;
                value = 1;
            }
            maillonCourant = maillonSuivant;
        }
    }
    return value;
}

t_maillon* RechercherMusique(t_liste* liste, char* titre)
{
    t_maillon* maillon = malloc(sizeof(t_maillon));
    int i = 0;
    int trouvee = 0;

    if(liste == NULL || liste->premier == NULL || maillon == NULL)
        return NULL;
    maillon = liste->premier;
    for(i = 0; i < liste->taille; i++)
    {
        if(strcmp(maillon->titre,titre) == 0)
        {
            trouvee = 1;
            break;
        }
        maillon = maillon->suivant;
    }
    if(trouvee == 1)
        return maillon;
    else
        return NULL;
}

t_liste* RechercherMusiques(t_liste* liste, char* champ)
{
    t_liste* musiques = InitialiserBibliothequeMusicale();
    t_maillon* ptmaillon = malloc(sizeof(t_maillon));
    int i = 0;
    int annee = 0;
    char genre[10];
    if(liste == NULL || liste->premier == NULL || ptmaillon == NULL|| musiques == NULL)
        return NULL;
    ptmaillon = liste->premier;
    if(strcmp(champ,"annee") == 0)
    {
        printf("Entrer l annee des morceaux a rechercher : ");
        scanf("%d",&annee);
        fflush(stdin);
    }
    else if(strcmp(champ,"genre")== 0)
    {
        printf("Entrer le genre des morceaux a rechercher : ");
        fgets(genre,10,stdin);
        for(i = 0; i < 10; i++)
            if(genre[i] == '\n')
                genre[i] = '\0';
    }
    for(i = 0; i < liste->taille; i++)
    {
        if(strcmp("annee",champ) == 0)
        {
            if(ptmaillon->annee == annee)
            {
                AjouterMusique(musiques,ptmaillon->titre,ptmaillon->annee, ptmaillon->morceau->genre,ptmaillon->morceau->duree);
            }
        }
        else if(strcmp(champ,"genre") == 0)
        {
            if(strcmp(ptmaillon->morceau->genre,genre) == 0)
            {
                AjouterMusique(musiques,ptmaillon->titre,ptmaillon->annee, ptmaillon->morceau->genre,ptmaillon->morceau->duree);
            }
        }
        ptmaillon = ptmaillon->suivant;
    }
    return musiques;
}

void AfficherMusiques(t_liste *liste)
{
    t_maillon* maillon = malloc(sizeof(t_maillon));
    int i = 0;

    if(maillon == NULL)
        return;
    if(liste == NULL || liste->premier == NULL)
        printf("Votre bibliotheque musicale est vide.");
    maillon = liste->premier;
    for(i = 0; i < liste->taille; i++)
    {
        printf("[%d] titre : %s | annee : %d | genre : %s | duree : %.2f s\n",i+1,maillon->titre,maillon->annee,maillon->morceau->genre, maillon->morceau->duree);
        maillon = maillon->suivant;
    }
}

void AfficherMusique(t_maillon* maillon)
{
    printf("titre : %s | annee : %d | genre : %s | duree : %.2f s\n",maillon->titre,maillon->annee,maillon->morceau->genre, maillon->morceau->duree);
}

t_liste* TrierMusiquesCroissantAnnee(t_liste* liste)
{
    t_maillon *maillon = malloc(sizeof(t_maillon));
    t_liste* listeTrier = InitialiserBibliothequeMusicale();
    int tri = 0;
    int i =0;
    int rnd = 1;
    if(liste == NULL || liste->premier == NULL || maillon == NULL)
        return NULL;
    AjouterMusique(listeTrier,liste->premier->titre,liste->premier->annee,liste->premier->morceau->genre,liste->premier->morceau->duree);
    while(!tri)
    {
        tri = 1;
        maillon = liste->premier;
        for(i = 0; i < liste->taille - rnd; i++)
        {
            if(maillon->annee > maillon->suivant->annee && RechercherMusique(listeTrier,maillon->suivant->titre) == NULL)
            {
                AjouterMusique(listeTrier,maillon->suivant->titre,maillon->suivant->annee,maillon->suivant->morceau->genre,maillon->suivant->morceau->duree);
                tri = 0;
            }
            maillon = maillon->suivant;
        }
        rnd++;
    }
    return listeTrier;
}
