#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define FRANCE +1

void Afficher_Ouverture_Fichier(void)
{
  time_t secondes;//La valeur renvoyée correspond au nombre de secondes écoulées depuis le premier janvier 1970
    struct tm Horloge;//structure contenant deja des varaibles de temps

    time(&secondes);//récupération de l'heure en secondes
    Horloge=*gmtime(&secondes);

 FILE* fichier = NULL;

    fichier = fopen("affichageHorloge.txt", "w+");

    if (fichier != NULL)
    {

        // On peut lire et écrire dans le fichier
    fprintf(fichier,"%d:%d:%d\n",(Horloge.tm_hour+FRANCE+24)%24, Horloge.tm_min, Horloge.tm_sec);


        fclose(fichier); // On ferme le fichier qui a été ouvert
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier test.txt");
    }

}


void Affichage_Heure()
{
    time_t secondes;//La valeur renvoyée correspond au nombre de secondes écoulées depuis le premier janvier 1970
    struct tm Horloge;//structure contenant deja des varaibles de temps

    time(&secondes);//récupération de l'heure en secondes
    Horloge=*gmtime(&secondes);//on utilise un pointeur pour ne pas avoir a recopier la valeur de la zone mémoire et gmtime recupère l'heure de grande bretagne

    printf(" %d:%d:%d\n",(Horloge.tm_hour+FRANCE+24)%24, Horloge.tm_min, Horloge.tm_sec);//affichage de l'heure actuel en france(gmt+1)

}

void Actualiser_Heure()
{

int i=0;
printf("L'heure va etre actualisée d'ici quelques instants");//message d'actualisation de l'heure
fflush(stdout);//permet d'afficher les différents messages dans la console au fur et à mesure


while(i<10)//boucle qui affiche un point d'actualisation toutes les secondes jusqu'à ,10 points
   {
   printf(".");
   fflush(stdout);
   sleep(1);//pause entre 2 points de 1 seconde
   i++;//la valeur de i augmente de 1

   }
}

void compteur()
{
FILE* fichier = NULL;

fichier = fopen("compteur.txt", "r+");

    if (fichier != NULL)
    {
    fseek(fichier, 0, SEEK_END);
        // On peut lire et écrire dans le fichier
    fputs("1\n",fichier);


        fclose(fichier); // On ferme le fichier qui a été ouvert
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier test.txt");
    }
}

int main()
{
compteur();
while(1)//boucle infini pour afficher et actualiser l'heure toutes les 10 secondes
{
    Afficher_Ouverture_Fichier();
    Affichage_Heure();
    Actualiser_Heure();
    system("clear");
    }


    return 0;
}
