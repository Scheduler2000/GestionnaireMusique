#ifndef __LISTE__
#define __LISTE__

typedef struct Morceau
{
	char* genre;
	float duree;
}t_morceau;

typedef struct Maillon
{
	char* titre;
	int annee;
	t_morceau* morceau;
	struct Maillon* suivant;
}t_maillon;

typedef struct Liste
{
	t_maillon* premier;
	int taille;
}t_liste;

t_liste* InitialiserBibliothequeMusicale();
int AjouterMusique(t_liste* liste, char* titre, int annee, char* genre, float duree);
int SupprimerMusique(t_liste*liste,char *titre);
t_maillon* RechercherMusique(t_liste* liste, char* titre);
t_liste* RechercherMusiques(t_liste* liste, char * champ); // annee || genre
void AfficherMusiques(t_liste *liste);
void AfficherMusique(t_maillon* maillon);
t_liste* TrierMusiquesCroissantAnnee(t_liste* liste); // Trie en fonction de l'annee
#endif
