#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <dirent.h>
#include <sys/wait.h>
#include "conio.h" // pour avoir la fonction getch de windows sous Linux (trouvé sur internet) Equivalent de conio.h de windows
#define TAILLE_MAX 1000
                                                   //Définit TAILLE_MAX à 40                                                      //Définit FALSE comme 0
void printStats()                                                 //Fonction permettant l'affichage des statistiques
{
    int choice;
    char* level = "";
    char* loginfo = "";
    char* date = "";
    char* hour = "";
    char* launcher = "";
    FILE* fichier = NULL;
    fichier = fopen("historique.txt", "r");
    char* item;
    int i=0;
    char line[TAILLE_MAX];
    if(fichier != NULL){
        do{
            printf("Stats\n Pour afficher l'historique trié par date du plus récent au plus ancien tapez 1: Pour trié par type tapez 2: \n ");
            scanf("%d",&choice);
            switch(choice)
            {
                case 1:
                        while(fgets(line, TAILLE_MAX, fichier) != NULL){
                            for (item = strtok(line, ";"); item != NULL; item = strtok(NULL, ";")){
                                if(i==0) date = item;
                                else if(i==2) level = item;
                                else if(i==3) loginfo = item;
                                i++;
                            }
                            if(strcmp(level, "1")==0) launcher = "statique";
                            else if(strcmp(level, "2")==0) launcher = "dynamique";
                            else if(strcmp(level, "3")==0) launcher = "interactif";
                            printf("%s, Vous avez lancé le %s avec le paramètre %s\n", date, launcher, loginfo);
                        }
                    break;
                case 2:
                    //system("sort -d historique.txt"
                    break;
                default:
                    printf("Erreur de choix\n\n");
                    break;
            }
        }while(choice != 1 && choice != 2);
        fclose(fichier);
    }else{
        printf("Erreur ouverture fichier");
    }
}
void statistique(int level, char *info) //Fonction pour ecrire dans le fichier historique en fonction du type de SS et les infos émises
{
    FILE* file = NULL;
    char text[100];
    char insertion[5];
    char tolog[255];
    sprintf(insertion,"%d",level);
    time_t timestamp;
    struct tm * t;
    timestamp = time(NULL);
    t = localtime(&timestamp);
    file = fopen("historique.txt", "a+" );
    sprintf(text, "%02u/%02u/%04u;%02u:%02u:%02u;%d;%s;\n", t->tm_mday, t->tm_mon,1900 + t->tm_year, t->tm_hour, t->tm_min, t->tm_sec, level, info);
    fputs(text, file);
    fclose(file);
}

int choixAleatoireEcrans(int borneMin, int borneMax)             // Random permettant de choisir un programme aléatoirement
{
    int random;

    srand(time(NULL));
    random = rand()%(borneMax - borneMin) +borneMin;
    return random;
}

pid_t creerProcessusFils()
{

    pid_t pid;

    do
    {
        pid = fork();
    }
    while(pid == -1);

    return pid;
}

char *selectPBM()
{

    char pbm_repertoire[1024];
    char* str = getenv("EXIASAVER1_PBM");
    if(str != NULL) strcpy(pbm_repertoire, str);
    else getcwd(pbm_repertoire, 1024);
    DIR* rep = opendir(pbm_repertoire);

    if(rep != NULL)

    {

        struct dirent * ent;

        int compteur = 0;

        while((ent = readdir(rep)) != NULL)

        {

            if(strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) compteur ++;

        }
        int random_nbr = choixAleatoireEcrans(1, compteur+1);

        rewinddir(rep);

        compteur = 0;

        while(compteur != random_nbr && (ent = readdir(rep)) != NULL)

        {

            if(strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) compteur ++;

        }

        closedir(rep);

        return ent->d_name;

    }
}
void executerImageStatique(int random)
{

    char chemin[1024];
    char* str = getenv("EXIASAVER_HOME");
    if(str != NULL) strcpy(chemin, str);
    else getcwd(chemin, 1024);
    strcat(chemin, "statique");
    char* random_pbm = selectPBM();

    char* arguments[] = {"statique", random_pbm, NULL};

    printf("Demarrage du statique\n");
    execv(chemin, arguments);
}

char* preparerAleatoireStatique(char* nomsfichiers, int i)
{

    char separateur[4] = ".pbm";
    char* arg;
    int random = choixAleatoireEcrans(0, i);

    arg = strtok(nomsfichiers, separateur);
    for(i=0; i<random; i++)
    {
        arg = strtok(NULL, separateur);
    }
    strcat(arg, separateur);

    return arg;
}

char* variableEnvironnement(char* env)
{

    char *strenv = getenv(env);

    return strenv;
}

void executerDynamique()
{

    char chemin[1024];
    char* str = getenv("EXIASAVER_HOME");
    if(str != NULL) strcpy(chemin, str);
    else getcwd(chemin, 1024);
    strcat(chemin, "horloge");
    char* arguments[] = {"horloge", NULL};

    printf("Demarrage du dynamique\n");
    execv(chemin, arguments);
    exit(1);
}

void executerInteractif()
{

    char chemin[1024];
    char* str = getenv("EXIASAVER_HOME");
    if(str != NULL) strcpy(chemin, str);
    else getcwd(chemin, 1024);
    strcat(chemin, "interactif");
    char* arguments[] = {"interactif", NULL};

    printf("Demarrage de l'interactif\n");
    execv(chemin, arguments);
    exit(1);
}

void lancementsEcrans()                 // Lancements des ecrans, creation de nouveau processus
{
    int random = choixAleatoireEcrans(1, 4);
    char donnee[16];
    char nomsfichiers[1024] = "";
    char *fichier;
    int f, i=0, wstatus;
    char arg[255];
    char env[255];
    printf("Lancement du screensaver...\n");
    char t[255] = "";
    sprintf(env, "EXIASAVER%d_PBM", random);
    char* str = variableEnvironnement(env);
    f = creerProcessusFils();

    if (f==0)
    {
        switch(random)
        {
        case 1 :
            executerImageStatique(random);
            break;

        case 2 :
            strcpy(donnee,"80x24");
            statistique(random,donnee);
            executerDynamique();
            exit(1);
            break;

        case 3 :
            strcpy(donnee,"40x12");
            statistique(random,donnee);
            executerInteractif();
            exit(1);
        }
    }
    else
    {
        waitpid(f, &wstatus, 0);
    }
    if(random == 1) statistique(1, t);
}

int main (int agrc, char * argv[1])
{
    system("clear");
    if (agrc>1)                        // Si on lui envoi un argument on rentre dans la boucle
    {
        if (strcmp(argv[1],"-stats"))   // si argv est different de -stats on lui dit erreur
        {
            printf("Erreur de paramètres\n");
        }
        else                            // sinon on lance la fonction statistique
        {
            printf("Lancement des statistiques...\n");
            printStats();
        }
    }
    else                                // Si on envoi pas d'arguments on lance un des ecrans
    {
        lancementsEcrans();
    }
    return 0;
}

