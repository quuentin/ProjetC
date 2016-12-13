#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>


void Affichage_Heure()
{
    time_t secondes;
    struct tm instant;
    time(&secondes);
    instant=*localtime(&secondes);
    printf("%d:%d:%d\n", instant.tm_hour, instant.tm_min, instant.tm_sec);

}

void LireHeureDansConsole()
{
    char tableau[20]
    printf("%d:%d:%d\n", instant.tm_hour, instant.tm_min, instant.tm_sec);


}

void AfficherHeure()
{


    }

    switch(heure)

{
case 1 :
    break;

case 2 :
    break;

case 3 :
    break;

case 4 :
    break;

case 5 :
    break;

case 6 :
    break;

case 7 :
    break;

case 8 :
    break;
    }
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
