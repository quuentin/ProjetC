#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conio.h"
#include "pbm.h"

void lireResolution(FILE *fichier, Pbm* p) // fonction qui permet de stocker la rÈsolution de l'image
{
    char lectureLigne[50] = ""; // char qui va permettre de stocker la ligne o˘ est Ècrit la rÈsoltuion de l'image

    for(int i = 0; i < 2; i++)
    {
        fgets(lectureLigne, 71, fichier); // on saute les deux premiËres lignes afin de se diriger directement l‡ o˘ est notÈ la rÈsolution de l'image
    }
    fscanf(fichier, "%d %d", &p->largeurImage, &p->longueurImage); // on rÈcupËre les donnÈes de la rÈsolution en les stockant dans les variables de notre structures
}

void afficherTableau(int tableauPourImage[80][24]) // fonction qui va afficher notre tableau 2D
{
    char c[] = {226, 150, 136, 0};

    for (int i = 0 ; i < 24; i++) // boucle qui va commencer par la premiËre colonne puis la deuxiËme aprËs qu'on ait fini de lire toutes les valeurs de la premiËre colonne
    {
        for (int j = 0; j < 80; j++) // boucle qui va lire un par un les donnÈes de la premiËre ligne du tableau jusqu'‡ la derniËre valeur
        {
            if(tableauPourImage[j][i] == 0) // si la valeur du tableau est un 0, on va afficher "X"
            {
                printf(" ");
            }
            else // si la valeur n'est pas 0 dans le tableau, alors on affiche " " (espace)
            {
                printf("%s",c);
            }
        }
    }
}

void insererImageCentreeDansTableau(FILE *fichier, Pbm* p, int tableauPourImage[80][24])
{
    char lectureLigneFichier[71] = ""; // on crÈe un char pour la lecture des lignes de fichier
    int binaireImagePBM; // variable qui permettra de stocker les diffÈrentes valeurs de code de l'image

    fgets(lectureLigneFichier, 71, fichier); // fgets permet de lire une ligne dans un fichier, ici fgets va nous permettre de passer la troisiËme ligne qui est inutile pour directement arrivÈ l‡ o˘ le code est dÈfinie

    while (fgets(lectureLigneFichier, 71, fichier) != NULL) // ‡ partir d'ici, on va lire toutes le code de l'image jusqu'‡ la fin du fichier
    {
        for(int z = 0; z < p->longueurImage; z++) // boucle pour permettre de se positionner dans la premiËre colonne
        {
            for(int k = 0; k < p->largeurImage; k++) // boucle pour lire toutes les donnÈes de la premiËre ligne
            {
                fscanf(fichier, "%d", &binaireImagePBM); // on stocke l'entier lu dans notre variable "binaireImagePBM"
                tableauPourImage[k + ((80 - p->largeurImage)/2)][z + ((24 - p->longueurImage)/2)] = binaireImagePBM; // on stocke la valeur lue dans notre tableau 2D en partant d'un point prÈcis pour centrer l'image gr‚c ‡ un calcul
            }
        }
    }
}

/* void choixAleatoireImage(Pbm* p) // "Pbm* p" est un pointeur sur la structure
{
    char nomImage;
    //insÈrer la fonction random qui va permettre de choisir l'image
    strcpy(p->nomImage, nomImage); // on copie un chaÓne de caractËre dans un char situÈ dans notre structure
}
*/
void manipulationFichier(char* arg)
{
    Pbm image; // "image" va contenir toutes nos variables situÈes dans la structure Pbm
    strcpy(image.nomImage, arg);
    int tableauPourImage[80][24] = {0}; // on crÈer un tableau ‡ deux dimensions rempli de 0

    FILE* fichier = NULL; // notre "FILE*" permet de rÈcupÈrer le pointeur du fichier pour ensuite pouvoir le manipuler

    fichier = fopen(image.nomImage, "r"); // on ouvre le fichier qui est contenu dans le char de notre structure et on lui assigne "r" pour juste permettre de lire le fichier

    if(fichier != NULL) // peremt de s'assurer que le fichier s'est bien ouvert
    {
        lireResolution(fichier, &image); // cette fonction va permettre de stocker la rÈsoltion de l'image PBM
        insererImageCentreeDansTableau(fichier, &image, tableauPourImage);
        fclose(fichier); // aprËs avoir fini de manipuler le fichier, il faut fermer le fichier pour libÈrer la mÈmoire vive
    }
    else // permet de savoir si le fichier ne s'est pas ouvert
    {
        printf("Le fichier n'a pas ÈtÈ ouvert");
    }
    char touche;
    afficherTableau(tableauPourImage); // on va afficher le tableau ‡ deux dimensions qui contient le code de l'image PBM, on va afficher un "X" quand la valeur est 0 et un " " quand la valeur est 1
    touche = getch();
    system("setterm -cursor off");
    while(1)
    {
        if (touche == 32)
        {
            system("clear");
            system("setterm -cursor on");
            exit(0);
        }
        else
        {
            touche = getch();
        }
    }

    system("clear");

}

int main(int argc, char* argv[])
{
    if(argc != 2){
        printf("Nombre incorrect d'arguments\n");
        return -1;
    }
    char* arg = argv[1];
    manipulationFichier(arg);
}



