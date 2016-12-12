#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include "ExiaSaver.h"

void lancerCommandes(){

    int pidCommandes;

    pidCommandes = creerProccessusFils();
    if(pidCommandes == 0){
        execl("commandes.c", 0);
    }
}

int* verifstat(char* argv[], int* pointeurpidTypes){

    int pidTypes;
    *pointeurpidTypes = &pidTypes;

    pidTypes = creerProccessusFils();
    if(argv[1] == "-stat"){
        pidTypes = execl("stat.c", 0);
    }
    return pointeurpidTypes;
}

int* aleatoire(int* p){

    int nombreAleatoire;
    *p = &nombreAleatoire;

    srand(time(NULL));
    nombreAleatoire = rand()%3;
    return p;
}

int creerProccessusFils(){

    int pid;

    do{
    pid = fork();
    }while(pid == -1);
    return pid;
}

void choixProgramme(int* p, int* pointeurpidTypes){

    int resultatAleatoire;
    resultatAleatoire = p;

    if(pointeurpidTypes == 0){
        switch(resultatAleatoire){
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
    } else {
        wait(pointeurpidTypes);
        system("CLEAR");

    }
}

void lancerStatique(){


}



    execl("TypeDynamique.c", 0);


    execl("TypeInteractif.c", 0);
