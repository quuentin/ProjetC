#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define FRANCE +1


void Affichage_Heure()
{
    time_t secondes;
    struct tm Horloge;

    time(&secondes);
    Horloge=*gmtime(&secondes);

    printf(" %d:%d:%d\n",(Horloge.tm_hour+FRANCE+24)%24, Horloge.tm_min, Horloge.tm_sec);

}

void Actualiser_Heure()
{

int i=0;
printf("L'heure va etre actualisée d'ici quelques instants");
fflush(stdout);


while(i<10)
   {
   printf(".");
   fflush(stdout);
   sleep(1);
   i++;

   }
}



int main()
{
while(1)
{
    Affichage_Heure();
    Actualiser_Heure();
    system("clear");
    }


    return 0;
}
