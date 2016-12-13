#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "pbm.h"


struct tm instant;

void Affichage_Heure()
{
    time_t secondes;
    time(&secondes);
    instant=*localtime(&secondes);
    printf("%d:%d:%d\n", instant.tm_hour, instant.tm_min, instant.tm_sec);

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

void decouperheures()
{
int H1, H2, M1, M2, S1, S2, deuxpoints;
H1 = (instant.tm_hour)/10 ;
H2 = (instant.tm_hour)-(H2*10);
M1 = (instant.tm_min)/10;
M2 = (instant.tm_min)-(M2*10);
S1 = (instant.tm_sec)/10;
S2 = (instant.tm_sec)-(S2*10);

}

void afficherHeurePBM()
{

    int valeuractuelle;
    int H1, H2, M1, M2, S1, S2, deuxpoints;
    H1=9;
    FILE* fichier = NULL;
    int i,j,k,l =0;
    char chaine[5];
    for (i ; i < 7; i++)
    {
        if (i == 0)
        {
            valeuractuelle = H1;
        }
        else if (i == 1)
        {
            valeuractuelle = H2;
        }
        else if (i == 2)
        {
            valeuractuelle = M1;
        }
        else if ( i == 3)
        {
            valeuractuelle = M2;
        }
        else if ( i == 4)
        {
            valeuractuelle = S1;
        }
        else if (i == 5)
        {
            valeuractuelle = S2;
        }
        else if ( i == 6)
        {
            valeuractuelle = deuxpoints;
        }
    }


        switch(H1)
        {
        case 0 :
            fichier = fopen("num0.pbm", "r" ); //OUVRE LE FICHIER
            break;

        case 1 :
            fichier = fopen("num1.pbm", "r" ); //OUVRE LE FICHIER
            break;

        case 2 :
            fichier = fopen("num2.pbm", "r" ); //OUVRE LE FICHIER
            break;

        case 3 :
            fichier = fopen("num3.pbm", "r" ); //OUVRE LE FICHIER
            break;

        case 4 :
            fichier = fopen("num4.pbm", "r" ); //OUVRE LE FICHIER
            break;

        case 5 :
            fichier = fopen("num5.pbm", "r" ); //OUVRE LE FICHIER
            break;

        case 6 :
            fichier = fopen("num6.pbm", "r" ); //OUVRE LE FICHIER
            break;

        case 7 :
            fichier = fopen("num7.pbm", "r" ); //OUVRE LE FICHIER
            break;

        case 8 :
            fichier = fopen("num8.pbm", "r" ); //OUVRE LE FICHIER
            break;

        case 9 :
            fichier = fopen("num8.pbm", "r" ); //OUVRE LE FICHIER
            while (fgets(chaine, 5, fichier) != NULL){// On lit le fichier jusqu'a qu'il n'y ai plus rien a lire donc qui il aura NULL

             printf("%s", chaine); // ca affiche la chaine qui aura stocké ce que le fgets va choper
        }
            break;

        default :
            fichier = fopen("num9.pbm", "r" ); //OUVRE LE FICHIER
            break;
        }
        printf("%d\n", valeuractuelle);
}
        int main()
        {
            afficherHeurePBM();
            while(1)//boucle infini pour afficher et actualiser l'heure toutes les 10 secondes
            {
                Affichage_Heure();
                Actualiser_Heure();
                system("clear");

            }
            return 0;
        }
