#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
//#include <ncurses.h>


#define TAILLE_LIGNE 20
#define TAILLE_COLONNE 20

int main()
{
    int i,j;
    char toucheDirectionelle;
    int Tableau2D [TAILLE_LIGNE][TAILLE_COLONNE] = {0};
    int x = 10;
    int y = 10;


    Tableau2D [x][y] = 1;
    for (i = 0 ; i < TAILLE_LIGNE; i++)
    {
        printf("\n");
        for (j = 0; j < TAILLE_COLONNE; j++)
        {
            printf("%d",Tableau2D[i][j]);

        }
    }

    while(1)
    {

        toucheDirectionelle = getch();
        toucheDirectionelle = getch();
        toucheDirectionelle = getch();

        if (toucheDirectionelle == 66) //Bas
        {


                system ("clear");
                x++;
                Tableau2D [x][y] = 1;
                Tableau2D [x-1][y] = 0;

                if (x == 20)
                {
                    x = -1;
                    Tableau2D [x][y] = 1;
                    Tableau2D [20][y] = 0;


                }


                for (i = 0 ; i < TAILLE_LIGNE; i++)
                {
                    printf("\n");
                    for (j = 0; j < TAILLE_COLONNE; j++)
                    {

                        printf("%d",Tableau2D[i][j]);

                    }
                }






        }

        else if (toucheDirectionelle == 65) //Haut
        {
            system ("clear");
            x--;
            Tableau2D [x][y] = 1;
            Tableau2D [x+1][y] = 0;


            if (x == -1)
            {
                x = 19;
                Tableau2D [x][y] = 1;
                Tableau2D [-1][y] = 0;


            }





            for (i = 0 ; i < TAILLE_LIGNE; i++)
            {
                printf("\n");
                for (j = 0; j < TAILLE_COLONNE; j++)
                {

                    printf("%d",Tableau2D[i][j]);

                }
            }






        }
        else if (toucheDirectionelle == 68) //Gauche
        {
            system ("clear");
            y--;
            Tableau2D [x][y] = 1;
            Tableau2D [x][y+1] = 0;

           if (y == -1)
            {
                y = 19;
                Tableau2D [x][y] = 1;
                Tableau2D [x][-1] = 0;


            }


            for (i = 0 ; i < TAILLE_LIGNE; i++)
            {
                printf("\n");
                for (j = 0; j < TAILLE_COLONNE; j++)
                {

                    printf("%d",Tableau2D[i][j]);

                }

            }



        }
        else if (toucheDirectionelle == 67) //Droite
        {
            system ("clear");
            y++;
            Tableau2D [x][y] = 1;
            Tableau2D [x][y-1] = 0;

             if (y == 20)
            {
                y = 0;
                Tableau2D [x][y] = 1;
                Tableau2D [x][20] = 0;


            }



            for (i = 0 ; i < TAILLE_LIGNE; i++)
            {
                printf("\n");
                for (j = 0; j < TAILLE_COLONNE; j++)
                {

                    printf("%d",Tableau2D[i][j]);


                }
            }









        }
    }
}
