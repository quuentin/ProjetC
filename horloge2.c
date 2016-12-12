#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define FRANCE +1


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



int main()
{
while(1)//boucle infini pour afficher et actualiser l'heure toutes les 10 secondes
{
    Affichage_Heure();
    Actualiser_Heure();
    system("clear");
    }


    return 0;
}
