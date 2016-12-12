#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
char toucheDirectionelle;

int main()
{
    int i,j,valeur;
    long c,t;
    int Tableau2D [20][20] = {0};
    i=10;
    j=10;
    int x=10;
    int y=10;


    Tableau2D [x][y] = 1;
    for (i=0 ; i<20; i++)
    {
        printf("\n");
        for (j=0; j<20; j++)
        {
            printf("%d",Tableau2D[i][j]);

                                        //c = t[i][j++];
             //t[i++][j];
        }
    }  while(1)
    {

toucheDirectionelle = getch();

        if (toucheDirectionelle == 115)
        {

            x++;
            Tableau2D [x][y] = 1;
            Tableau2D [x-1][y] = 0;


            for (i=0 ; i<20; i++)
            {
                printf("\n");
                for (j=0; j<20; j++)
                {

                    printf("%d",Tableau2D[i][j]);

                    //c = t[i][j++];
                    //t[i++][j];
                }
            }
        }
        else if (toucheDirectionelle == 122)
        {

            x--;
            Tableau2D [x][y] = 1;
            Tableau2D [x+1][y] = 0;


            for (i=0 ; i<20; i++)
            {
                printf("\n");
                for (j=0; j<20; j++)
                {

                    printf("%d",Tableau2D[i][j]);

                    //c = t[i][j++];
                    //t[i++][j];
                }
            }
        }
        else if (toucheDirectionelle == 113)
        {

            y--;
            Tableau2D [x][y] = 1;
            Tableau2D [x][y+1] = 0;


            for (i=0 ; i<20; i++)
            {
                printf("\n");
                for (j=0; j<20; j++)
                {

                    printf("%d",Tableau2D[i][j]);

                    //c = t[i][j++];
                    //t[i++][j];
                }
            }
        }
        else if (toucheDirectionelle == 100)
        {

            y++;
            Tableau2D [x][y] = 1;
            Tableau2D [x][y-1] = 0;


            for (i=0 ; i<20; i++)
            {
                printf("\n");
                for (j=0; j<20; j++)
                {

                    printf("%d",Tableau2D[i][j]);

                    //c = t[i][j++];
                    //t[i++][j];
                }
            }
        }


    }
}


