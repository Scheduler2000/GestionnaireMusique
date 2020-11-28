#include <stdio.h>
#include <stdlib.h>
#include "../includes/liste.h"
#include "../includes/menu.h"

int main(int argc, char const *argv[])
{
	t_liste* liste = ChargerBibliotheque("Bibliotheque.txt");
	AfficherMenu(liste);
	return 0;
}
