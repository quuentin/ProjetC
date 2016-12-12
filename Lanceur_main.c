#include <stdio.h>

int main(int argc, char *argv[]){

    int* p, pointeurpidTypes;

    system("CLEAR");

    lancerCommandes();

    verifstat(argv[2], pointeurpidTypes);

    aleatoire(p);

    choixProgramme(p, pointeurpidTypes);

}
