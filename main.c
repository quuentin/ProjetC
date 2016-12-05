#include <stdio.h>
#include <stdlib.h>
#define TAILLE_MAX 1000 // Tableau de taille 1000


int main()
{

     FILE* fichier = NULL;
     char chaine[TAILLE_MAX] = ""; // Chaîne vide de taille TAILLE_MAX
    fichier = fopen("test.txt", "r+");

    if (fichier != NULL)
    {


        fseek(fichier, 0, SEEK_END);//notre curseur immaginaire se positionne à la fin de notre texte
       fprintf(fichier,"bonjour");
       // fputs("Bonjour", fichier);
        rewind(fichier);//le curseur se place au debut pour lire

        while(fgets(chaine,TAILLE_MAX,fichier)!=NULL)//tant qu'il y a des caracteres à lire la boucle ne s'arrete pas
         {
         printf("%s",chaine);//affiche notre "bonjour"
         }

        fclose(fichier);
}
else
{
printf("erreur d'ouveture");
}


    return 0;

}
