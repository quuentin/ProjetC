#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "horloge.h"



void Affichage_Heure()//fonction qui affiche l'heure
{
    int i;//i va permettre de centrer horizontalement l'heure
    int j;//j va permettre de centrer verticallement l'heure
    time_t actuelle = time (NULL);//on initialise l'heure actuelle à NULL
    struct tm tm_actuelle = *localtime (&actuelle);//grâce a la structure tm contenu dans la bibliothèque time.h on récupère l'heure actuelle
    char heure[sizeof "HH:MM:SS"];//on stocke l'heure dans une chaine de caractère
    strftime (heure, sizeof heure, "%H:%M:%S", &tm_actuelle);//Formate une date/heure locale avec la configuration locale

    for(j=0; j<10; j++)
    {
        printf("\n");
    }
    for(i=0; i<34; i++)
    {
        printf(" ");
    }

    printf("%s",heure);
}


void Actualiser_Heure()
{
    int i=0;
    int k;
    int j;
    char* str = getenv("EXIASAVER2_SLEEP");
//str = NULL; //pour tester si le else fonctionne correctement

    char dodo[2];

    if(str != NULL)
        strcpy(dodo, str);
    else
        strcpy(dodo, "10");

    int n = atoi(dodo);
    for(j=0; j<10; j++)
    {
        printf("\n");
    }
    for(k=0; k<10; k++)
    {
        printf(" ");
    }
    printf("L'heure va etre actualisée d'ici quelques instants");//message d'actualisation de l'heure
    fflush(stdout);//permet d'afficher les différents messages dans la console au fur et à mesure


    while(i<n)//boucle qui affiche un point d'actualisation toutes les secondes jusqu'à ,10 points
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
        Affichage_Heure();//lancement de ma fonction affichage de l'heure
        Actualiser_Heure();
        system("clear");//nettoie la console
    }


    return 0;
}
