#ifndef __MENU__
#define __MENU__
#include "../includes/liste.h"
void AfficherMenu(t_liste* liste);
t_liste* ChargerBibliotheque(char *path);
void SauvegarderBibliotheque(t_liste* liste);
void CleanConsole(FILE* st);

#endif
