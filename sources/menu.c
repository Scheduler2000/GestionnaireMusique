#include <stdio.h>
#include <stdlib.h>
#include "../includes/menu.h"

void AfficherMenu(t_liste * liste)
{
	int sortir = 0;
	char choix = '\0';
	char titre[30];
	char titreTemp[30];
	char genre[15];
	char genreTemp[30];
	char recherche[10];
	int annee;
	int i = 0;
	float duree;
	do
	{
		choix = '\0';
		titre[30] = '\0';
		genre[15] = '\0';
		recherche[7] = '\0';
		annee = 0;
		duree = 0;
		printf("\n\n\n");
		printf("Gestionnaire des fichiers de votre bibliotheque musicale \n\n");
		printf("\t1. Ajouter une nouvelle musique.\n");
		printf("\t2. Afficher la bibliotheque musicale entiere.\n");
		printf("\t3. Rechercher une musique particuliere.\n");
		printf("\t4. Effectuer une recherche globale.\n");
		printf("\t5. Trier la bibliotheque musicale.\n");
		printf("\t6. Sauvegarder la bibliotheque musicale.\n");
		printf("\t7. Sortir du gestionnaire musicale.\n\n...\n");
		choix = fgetc(stdin);
		CleanConsole(stdin);
		switch(choix)
		{
			case '1':
			printf("\nEntrer le nom de votre musique : ");
			fgets(titreTemp,29,stdin);
			printf("\nEntrer l'annee de votre musique : ");
			scanf("%d",&annee);
            CleanConsole(stdin);
			printf("\nEntrer le genre de votre musique : ");
			fgets(genreTemp,14,stdin);
			printf("\nEntrer la duree de votre musique : ");
			scanf("%f",&duree);
            CleanConsole(stdin);
            for(i = 0; i < strlen(titreTemp) - 2; i++)
                titre[i] = titreTemp[i];
            for(i = 0; i < strlen(genreTemp) - 2; i++)
                genre[i] = genreTemp[i];
			AjouterMusique(liste,titre,annee,genre,duree);
			break;
			case '2':
			AfficherMusiques(liste);
			break;
			case '3':
			printf("\nEntrer le nom votre musique que vous souhaitez trouver : ");
			fgets(titreTemp,29,stdin);
			for(i = 0; i < strlen(titreTemp) - 1;i++)
                titre[i] = titreTemp[i];
			t_maillon* Maillon = RechercherMusique(liste,titre);
			AfficherMusique(Maillon);
			break;
			case '4':
			printf("\nSouhaitez vous rechercher des musiques via son annee ou son genre : ");
			fgets(recherche,6,stdin);
			CleanConsole(stdin);
			AfficherMusiques(RechercherMusiques(liste,recherche));
			break;
			case '5': // A debugger
			liste = TrierMusiquesCroissantAnnee(liste);
			printf("Votre bibliotheque musicale est triee.\n");
			break;
			case '6':
			SauvegarderBibliotheque(liste);
			break;
			case '7':
			sortir = 1;
			break;
			default:
			continue;
		}

	}while(!sortir);
}

t_liste* ChargerBibliotheque(char* path)
{
	FILE* fichier = fopen(path,"r+");
	t_liste* liste = InitialiserBibliothequeMusicale();
	char typeInformation;
	char informations[50] = "\0";
	char ligne[50] = "\0";
	char titre[25] = "\0";
	char genre[16] = "\0";
	int annee;
	int i = 0;
	int nbrMusiques = 1;
	float duree;
    t_liste* bibliotheque = malloc(sizeof(t_liste));

    if(fichier != NULL && bibliotheque != NULL && liste != NULL)
    {
        while(fgets(ligne,50,fichier) != NULL)
        {
            typeInformation = ligne[0];
            for(i = 0; i < strlen(ligne) - 2; i++)
                informations[i] = ligne[i+1];
            switch(typeInformation)
            {
            case 't':
                strcpy(titre,informations);
                break;
            case 'a':
                annee = atoi(informations);
                break;
            case 'g':
                strcpy(genre,informations);
                break;
            case 'd':
                duree = atof(informations);
                break;
            case '-':
                AjouterMusique(liste,titre,annee,genre,duree);
                nbrMusiques++;
                break;
            }
            memset(informations,'\0',50);
        }
        fclose(fichier);
        printf(" [%d] fichiers ont ete charges.\n",nbrMusiques);
    }
    else
        return NULL;
    return liste;
}

void SauvegarderBibliotheque(t_liste* liste)
{
	FILE* fichier = fopen("Bibliotheque.txt","r+");
	int i = 0;
	t_maillon* maillon;

	if(fichier != NULL && liste != NULL && liste->premier != NULL)
	{
		maillon = liste->premier;
		for(i = 0; i < liste->taille;i++)
		{
			fprintf(fichier, "t%s\n",maillon->titre);
			fprintf(fichier, "a%d\n",maillon->annee);
			fprintf(fichier,"g%s\n",maillon->morceau->genre);
			fprintf(fichier,"d%f.2\n",maillon->morceau->duree);
            fputs("-------------------------\n",fichier);
			maillon = maillon->suivant;
		}
		fclose(fichier);
		printf("[%d] fichiers ont ete sauvegardes.\n",liste->taille);
	}
}

void CleanConsole(FILE* st)
{
    {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
}
