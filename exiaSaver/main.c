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

#define TAILLE_MAX 40                                                   //Définit TAILLE_MAX à 40                                                      //Définit FALSE comme 0

void statistiques()                                                 //Fonction permettant l'affichage des statistiques
{
    char chainehisto[255][40];
    FILE* fichierstats = NULL;
    char chaine[TAILLE_MAX];                                  //Variable chaine définie avec une taille par DEFINE qui contiendra la chaine en cours d'utilisation
    int modetri=0;                                                    //Varibale qui contient le mode de triage choisit par l'utilisateur
    int i=0, j=0, n=0;                                                        //Variable qui sert de compteur pour le nombre de ligne dans le fichier historique                                                        //Compteur
    fichierstats = fopen("historique.txt", "r" );                       //Ouvre le fichier d'historique avec les droits de lecture
    if (fichierstats==NULL)
    {
        printf("Erreur d'ouverture fichier");               //Affiche une erreur si le fichier n'est pas ouvrable
    }
    while (fgets(chaine, TAILLE_MAX, fichierstats) != NULL)                                   //Tant que la variable chaine ne contient pas un blanc....
    {
        fgets(chaine, TAILLE_MAX, fichierstats);                    //On récupère ligne par ligne le fichier historique et....
        if (strcmp(chaine," ")!=0)                                  //Si ce qu'on recupère n'est toujours pas un blanc
        {
            strcat(chainehisto[i], chaine);                         //On colle ce qu'on vient de récuperer dans une variable char tampon qui contiendra alors l'ensemble du fichier historique sous forme de varibale, le tout dans le bon format (saut de lignes inclus)
        }
        i++;                                                        //On incrément i pour ajouter chaine dans une autre ligne du tableau chainehisto ( pour garder un format lisible)
    }
    fclose(fichierstats);                                           //On ferme le fichier historique
    i=i-1;                                                          //On decrémente i une fois car la boucle while nous compte une ligne de trop
    while (modetri!=1 && modetri!=2)                  //Ici tant que l'utilisateur rentre pas un mode de tri valide on continue de demander
    {
        printf("Pour trier l'ouverture des différents types ouverts du plus récents au plus ancien tapez 1, du plus ancien au plus récents tapez 2 :\n");
        scanf("%d",&modetri);                                       //On place dans la varible modetri le choix de l'utilisateur
    }
    system("clear");
    printf("Voici votre historique ");
    switch(modetri)                                                 //Ici en fonction du choix de l'utilisateur, on lance nos différents tri
    {
    case 1:                                                     //Si modetri=1 ....
        printf("trié par date:\n\n");
        for (j=0; j<i; j++)                                     //Ici on affiche ligne par ligne avec le compteur j qu'on incrémente...                 //les différentes lignes du tableau chainehisto
        {
            printf("%s\n",chainehisto[j]);
        }
        printf("Vous avez lancé %d fois ExiaSaver !\n",i);      //On indique à l'utilisateur combien de fois il a utilisé l'ES
        break;                                                  //Met fin au cas 1
    case 2:                                                     //Si modetri=3 ....
        printf("Trié par dates inversées:\n\n");
        for (j=i; j>=0; j--)                                   //On inverse la boucle du mode 1
        {
            printf("%s\n",chainehisto[j]);                      //les entrées de chainehisto
        }
        printf("Vous avez lancé %d fois ExiaSaver !\n",i);      //On indique à l'utilisateur combien de fois il a lancé l'ES
        break;
    }

}

void entreehistorique(int level, char *info) /*Fonction pour ecrire dans le fichier historique en fonction du type de SS et les infos émises*/
{
    FILE* fichierstats = NULL;
    int t;
    char insertion[5];
    level=level+1;
    sprintf(insertion,"%d",level);

    fichierstats = fopen("historique.txt", "r+" );/*Ouvre le fichier historique avec les droits ecriture et lecture*/

    fseek(fichierstats, -1, SEEK_END);   /*Place le curseur virtuel au bout du fichier*/
    time_t now = time (NULL);         /*Récupère le temps dans la variable now*/
    struct tm tm_now = *localtime (&now);    /*Converti now en heure locale*/
    char s_now[sizeof "JJ/MM/AAAA HH:MM:SS"];  /*Creer une chaine basique ...*/
    strftime (s_now, sizeof s_now, "%d/%m/%Y %H:%M:%S", &tm_now); /*...pour l'affichage de l'heure*/

    if (fichierstats!=NULL)
    {
        fprintf(fichierstats,"%s",s_now); /*Ecrit le format du cahier des charges dans le fichier historique*/
        fputs(";", fichierstats);
        fputs(insertion, fichierstats);
        fputs(";", fichierstats);
        fputs(info, fichierstats);
        fputs("\n ", fichierstats);   /*Ecrit le format du cahier des charges dans le fichier historique*/
        fclose(fichierstats);  /*Ferme le fichier*/
    }
}

int choixAleatoireEcrans()             // Random permettant de choisir un programme aléatoirement
{
    int random;
    srand(time(NULL));
    random = rand();
    random = (random%4);
    if (random ==0)
    {
        random = random +1;
    }
    return random;
}

pid_t creerProcessusFils(){

    pid_t pid;

    do{
        pid = fork();
    }while(pid == -1);

    return pid;
}


char* preparerAleatoireStatique(char* nomsfichiers, int i){
    i=0;
    char separateur[4] = ".pbm";
    char* arg;
    int random = choixAleatoireEcrans();
    

    arg = strtok(nomsfichiers, separateur);
    for(i=0; i<random; i++){
        arg = strtok(NULL, separateur);
    }
    strcat(arg, separateur);

    return arg;
}

char* sauvegardeContenuNoms(struct dirent *Images, char* str, char* nomfichiersuivant, char* nomsfichiers, int* i){
    if((strcmp(Images->d_name, str)) != 0 && (strcmp(Images->d_name, ".")) !=0 && (strcmp(Images->d_name, "..")) !=0 ){
        if(strcmp(nomsfichiers, "") == 0){
            strcpy(nomsfichiers, Images->d_name);
        }else{
            strcpy(nomfichiersuivant, Images->d_name);
            strcat(nomsfichiers, nomfichiersuivant);
        }
    }
    i++;
    return nomsfichiers;
}

char* preparerStatique(){

    char* str;
    char* nomsfichiers;
    int i;
    DIR *dossierPBM;
    struct dirent *Images;
    char nomfichiersuivant[255];

    dossierPBM = opendir(str);
    while((Images = readdir(dossierPBM)) != NULL){
        sauvegardeContenuNoms(Images, str, nomfichiersuivant, nomsfichiers, &i);
    }
    closedir(dossierPBM);

    return nomsfichiers;
}

void executerImageStatique(int random){

   // char* arg = preparerStatique();
   // printf("caca");
  //  DIR *repertoireExecutables;
    char* str = getenv("EXIASAVER_HOME");
    char* arguments[] = {"statique", "avion.pbm", NULL};

    //repertoireExecutables = opendir(str);
  //  entreehistorique(random, arguments[1]);
    printf("Demarrage du statique\n");
    execv("pwd EXIASAVER_HOME", arguments);
   // closedir(repertoireExecutables);
    exit(1);
}

char* variableEnvironnement(char* env){

    char *strenv = getenv(env);

    return strenv;
}

void lancementsEcrans()                 // Lancements des ecrans, creation de nouveau processus
{
    int random = choixAleatoireEcrans();
    char donnee[16];
    char nomsfichiers[1024] = "";
    char *fichier;
    int f, i, wstatus;
    char arg[255];
    char env[255];
    printf("Lancement du screensaver...\n");

    sprintf(env, "EXIASAVER%d_PBM", random);
    char* str = variableEnvironnement(env);

    if (random==1)
    {
        f=fork();
        if (f==0)
        {

    // preparerStatique(str, nomsfichiers, i);
    // strcpy(arg, preparerAleatoireStatique(nomsfichiers, i));
     executerImageStatique(random);
/*
            char *arguments[] = { "statique", "avion.pbm", NULL };
            entreehistorique(random,arguments[1]);
            // fichier="afficheur";
            printf("Demarrage du statique\n");
            execv("/home/quentin/Bureau/statique/bin/Debug/statique", arguments);*/
            exit(1);
        }
        else
        {
            waitpid(f, &wstatus, 0);
        }
    }
    if (random==2)
    {
        f=fork();
        if (f==0)
        {
            strcpy(donnee,"horloge.pbm");
            entreehistorique(random,donnee);
            printf("Demarrage du dynamique\n");
            exit(1);
        }
        else
        {
            waitpid(f, &wstatus, 0);
        }
    }
    if (random==3)
    {
        f=fork();
        if (f==0)
        {
            strcpy(donnee,"avion.pbm");
            entreehistorique(random,donnee);
            fichier="avion.pbm";
            printf("Demarrage de l'interactif\n");
            execl(fichier,fichier,NULL);
            exit(1);
        }
        else
        {
            waitpid(f, &wstatus, 0);
        }
    }

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
            statistiques();
        }
    }
    else                                // Si on envoi pas d'arguments on lance un des ecrans
    {
       // choixAleatoireEcrans();
        lancementsEcrans();
    }
    return 0;
}

