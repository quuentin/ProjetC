#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

int creerProccessusFils(){

    int pid;

    do{
    pid = fork();
    }while(pid == -1);
    return pid;
}

void lancerCommandes(){

    int pidCommandes;

    pidCommandes = creerProccessusFils();
    if(pidCommandes == 0){
        printf("commandes est en marche");
    }
}

void lancerStats(){

    int pidStats;

    pidStats = creerProccessusFils();
    if(pidStats == 0){
        printf("Stat est en marche");
    }
}

void verifstat(char* arg){
    char stat[6]="-stats";

    if(strcmp(arg, stat) == 0){
        lancerStats();
    }else{
        printf("Erreur, veuillez lancer le programme sans paramètres ou avec -stats en paramètre");
    }
}

void aleatoire(int *pointeurNombreAleatoire){

    srand(time(NULL));
    *pointeurNombreAleatoire = rand()%3;
}

void lancerStatique(){

    printf("Je Suis Statique");
}

void lancerDynamique(){

    printf("Je Suis Dynamique");
}

void lancerInteractif(){

    printf("Je Suis Interactif");
}

void choixProgramme(int* p){

    int pidTypes;
    int nombreAleatoire;

    aleatoire(&nombreAleatoire);
    printf("Résultat aléatoire : %d", nombreAleatoire);
    pidTypes = creerProccessusFils();

    if(pidTypes == 0){
        switch(nombreAleatoire){
            case 0 :
            lancerStatique();
            break;

            case 1 :
            lancerDynamique();
            break;

            case 2 :
            lancerInteractif();
            break;
        }
    }
}
