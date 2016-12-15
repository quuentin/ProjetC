#ifndef POINT_H_STATIQUE
#define POINT_H_STATIQUE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <signal.h> //Cette bibliothèque renferme les routines de traitement de signal.
#include <termios.h> /* Cette bibliothèque renferme les définitions des valeurs du «termios».  Les fonctions termios  établissent une interface générale pour les
terminaux, permettant de contrôler et tirer partis des possibilités du terminal. Permettant de contrôler les ports de communication asynchrone (ici entre clavier et console).*/
#include <unistd.h> //Cette bibliothèque renferme les types et les constantes symbole standard.






typedef struct Pbm Pbm; // on remplace "struct Pbm" par "Pbm" pour raccourcir le code
struct Pbm // définition de notre structure Pbm
{
    int largeur_image;   // ces deux int vont stocker la résolution de l'image
    int longueur_image;
    char image[100][100]; // va comporter le nom de notre fichier PBM tiré aléatoirement
};




int getch(void);
char touche();




//--------------------------------------------------------------------------------------------------------------------------------------------------------------//




void choixAleatoireImage(Pbm* pointeur_structure);
void lireResolution(char *fichier, Pbm* pointeur_structure);
void insererImageCentreeDansTableau(char *fichier, Pbm* pointeur_structure, int tableau_pour_image[80][24]);
void afficherTableau(int tableau_pour_image[80][24]);





int statique();


#endif

