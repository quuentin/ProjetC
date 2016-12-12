#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>

void exiaSaver(int argc, char* argv[]){

    int pidCommandes, pidTypes;
    int* lancerProgramme;
    lancerProgramme = NULL;

    system("CLEAR");
    pidCommandes = creerProccessusFils();
    pidTypes = creerProccessusFils();
    verifStat(argv[1], pidTypes);
    Aleatoire(lancerProgramme);
    choixProgramme(&lancerProgramme, pidTypes);
}

void verifstat(char* argv[], int pidTypes){

    if(argv[1] == -stat){
        pidTypes = execl("C:/ProjetC/stat.c", 0);
    }
}

int* Aleatoire(int* lancerProgramme){

    int nombreAleatoire;
    lancerProgramme->nombreAleatoire;

    srand(time(NULL));
    nombreAleatoire = rand()%3;
    return lancerProgramme;
}

int creerProccessusFils(){

    int pid;

    do{
    pid = fork();
    }while(pid == -1);
    return pid;
}

void lancerCommandes(int pidCommandes){

    if(pidCommandes == 0){
        execl("C:/ProjetC/commandes.c", 0);
    }
}

void choixProgramme(int* lancerProgramme, int pidTypes){


    char *getenv(EXIASAVER_HOME);
    DIR *opendir(EXIASAVER_HOME);
    if(pidTypes == 0){
        switch(&lancerProgramme){
            case '0' :
            lancerStatique();
            break;

            case '1' :
            lancerDynamique();
            break;

            case 'default' :
            lancerInteractif();
            break;
    }
}

void lancerStatique(){

    execl("TypeStatique.c", 0);
    closedir(EXIASAVER_HOME);
}



    execl("TypeDynamique.c", 0);
    closedir(EXIASAVER_HOME);


    execl("TypeInteractif.c", 0);
    closedir(EXIASAVER_HOME);
