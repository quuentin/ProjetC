// AFFICHER UN CARRE NOIR MAMENE
//#include <stdio.h>
//#include <stdlib.h>
//int main(void)
//{
//char c[] = {226, 150, 136, 0};
//printf("%s%s%s%s%s%s%s",c,c,c,c,c,c,c) ;
//}
#include <stdio.h>
#include <stdlib.h>
#define TAILLE_MAX 1000

int main(int argc, const char * argv[]) {

    FILE* fichier = NULL;
    char chaine[TAILLE_MAX]; //= ""; // Chaine va stocker ce que le fgets va recuperer quand il va lire

    fichier = fopen("Ex1.pbm", "r+"); // r+ pour lire et ecrire dans le fichier

    if (fichier != NULL) // si le fichier est différent de NULL on rentre dans la boucle
    {

            rewind(fichier); // on se place au début pour lire depuis le debut

        while (fgets(chaine, TAILLE_MAX, fichier) != NULL){// On lit le fichier jusqu'a qu'il n'y ai plus rien a lire donc qui il aura NULL

             printf("%s", chaine); // ca affiche la chaine qui aura stocké ce que le fgets va choper
        }

        fclose(fichier); // On ferme le fichier
    }

    else
    {
        // On affiche un message d'erreur si le fichier est introuvable ou qu'il y a un problème autre
        printf("Impossible d'ouvrir le fichier test.txt\n");
    }

    return 0;
}
