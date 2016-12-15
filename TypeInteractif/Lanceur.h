#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
typedef struct PBM PBM;
struct PBM
{
    int hauteur;
    int longueur;
    char nom[1024];
    int image[80][24];
};
typedef struct Avion Avion;
struct Avion{
    PBM imgPbm;
    char* direction;
    int posX, posY;
};




PBM viderCiel()
{
    PBM pbm;
    pbm.longueur = 80;
    pbm.hauteur = 24;
    for(int i=0; i<80; i++)
    {
        for(int j=0; j<24; j++)
        {
            pbm.image[i][j] = 0;
        }
    }
    return pbm;
}
int pipeDescriptor[2];
void processus_fils();
void processus_pere(Avion* avion);
void deplacerAvion(Avion* avion);
void directionAleatoire(Avion *avion);
void chargerCheminResolution(Avion *avion);
