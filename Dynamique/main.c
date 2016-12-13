#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "conio.h"
#include "pbm.h"
#define TAILLE_MAX 1000

void Afficher_Ouverture_Fichier(void)
{
    time_t secondes;//La valeur renvoyée correspond au nombre de secondes écoulées depuis le premier janvier 1970
    struct tm instant;//structure contenant deja des varaibles de temps

    time(&secondes);
    instant=*localtime(&secondes);

    FILE* fichier = NULL;
    char chaine[TAILLE_MAX];

    fichier = fopen("affichageHorloge.txt", "w+");

    if (fichier != NULL)
    {

        // On peut lire et écrire dans le fichier
        fprintf(fichier,"%d:%d:%d\n", instant.tm_hour, instant.tm_min, instant.tm_sec);
        rewind(fichier);

        while (fgets(chaine, TAILLE_MAX, fichier) != NULL){// On lit le fichier jusqu'a qu'il n'y ai plus rien a lire donc qui il aura NULL

        printf("%s", chaine); // ca affiche la chaine qui aura stocké ce que le fgets va choper
        }

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

    time_t secondes;
    struct tm instant;

    time(&secondes);
    instant=*localtime(&secondes);

    // printf("%d:%d:%d\n", instant.tm_hour, instant.tm_min, instant.tm_sec);
}

//}

/*void Affichage_Heure()
{
   time_t secondes;//La valeur renvoyée correspond au nombre de secondes écoulées depuis le premier janvier 1970
   struct tm Horloge;//structure contenant deja des varaibles de temps

   time(&secondes);//récupération de l'heure en secondes
   Horloge=*gmtime(&secondes);//on utilise un pointeur pour ne pas avoir a recopier la valeur de la zone mémoire et gmtime recupère l'heure de grande bretagne

   printf(" %d:%d:%d\n",(Horloge.tm_hour+FRANCE+24)%24, Horloge.tm_min, Horloge.tm_sec);//affichage de l'heure actuel en france(gmt+1)

}*/

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


void lireResolution(FILE *fichier, Pbm* p) // fonction qui permet de stocker la rÈsolution de l'image
{
    char lectureLigne[50]; // char qui va permettre de stocker la ligne o˘ est Ècrit la rÈsoltuion de l'image

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
        printf("Le fichier n'a pas été ouvert");
    }
    // char touche;
    afficherTableau(tableauPourImage);// on va afficher le tableau ‡ deux dimensions qui contient le code de l'image PBM, on va afficher un "X" quand la valeur est 0 et un " " quand la valeur est 1
    quiterProgrammeAvecEspace();

}

void quiterProgrammeAvecEspace()
{
    char touche;
    touche = getch();
    system("setterm -cursor off");
    while(1)
    {
        if (touche == 32)
        {
            system("clear");
            system("setterm -cursor on");
            system("clear");
            exit(0);
        }
        else
        {
            touche = getch();
        }
    }
}

int main(int argc, char* argv[])
{

    FILE* fichier = NULL;
    char chaine[TAILLE_MAX]; //= ""; // Chaine va stocker ce que le fgets va recuperer quand il va lire

    fichier = fopen("test.txt", "r+"); // r+ pour lire et ecrire dans le fichier

    if (fichier != NULL) // si le fichier est différent de NULL on rentre dans la boucle
    {
            fseek(fichier, 0, SEEK_END);
            fprintf(fichier,"J'écris dans le fichier \n"); // Ecrit une fois le message donné

            rewind(fichier); // on se place au début pour lire depuis le debut

        while (fgets(chaine, TAILLE_MAX, fichier) != NULL){// On lit le fichier jusqu'a qu'il n'y ai plus rien a lire donc qui il aura NULL

             if (fgets(chaine, TAILLE_MAX, fichier)=0){
                printf("x");
             }
             else {
                printf("y")
             }
        }

        fclose(fichier); // On ferme le fichier
    }

    else
    {
        // On affiche un message d'erreur si le fichier est introuvable ou qu'il y a un problème autre
        printf("Impossible d'ouvrir le fichier test.txt\n");
    }

    manipulationFichier("j.pbm");
    system("clear");
    while(1)//boucle infini pour afficher et actualiser l'heure toutes les 10 secondes
    {
        Afficher_Ouverture_Fichier();
        Affichage_Heure();
        Actualiser_Heure();
        system("clear");
    }


    return 0;
}
