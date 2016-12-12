#include <stdio.h>
#include "ExiaSaver.h"

int main(int argc, char *argv[]){

    char* arg = argv[1];

    if(argc == 1){
        lancerCommandes();

        choixProgramme();
    }else{

        verifstat(arg);
    }
    return 0;
}
