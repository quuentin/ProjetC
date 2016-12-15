#include "Lanceur.h"
#include "conio.h"
#define TAILLETOUCHE 256

int main(int argc, char* argv[]){ //main
    Avion avion; //creation de avion dans la structure
    avion.posX = 0; //initialisation
    avion.posY = 0;
    directionAleatoire(&avion);//lancement fonction pour choisir la direction
    for(int i=0; i<80; i++){
        for(int j=0; j<24; j++){
            avion.imgPbm.image[i][j] = 0;
        }
    }

    char lefichierPBM[1024];
    char* str = getenv("EXIASAVER3_PBM");//variable d'environnement
    if(str != NULL) strcpy(lefichierPBM, str);
    else getcwd(lefichierPBM, 1024);

    strcat(lefichierPBM, "/");
    strcat(lefichierPBM, avion.imgPbm.nom);
    FILE* fichier = NULL;
    fichier = fopen(lefichierPBM, "r");
    if(fichier == NULL){
        printf("Erreur lors de la lecture\n");
        return -1;
    }

    lireResolution(fichier, &avion.imgPbm);
    chargerPBM(fichier, &avion.imgPbm);
    fclose(fichier);
    afficherPBM(avion.imgPbm);
    pipe(pipeDescriptor);
    pid_t pid = creerProcessus();
    switch(pid){
        case -1:
            perror("fork");
            return -1;
        case 0:
            processus_fils();
            break;
        default:
            system("setterm -cursor off"); //permet d'enlever le curseur 
            processus_pere(&avion);
            break;
    }
    system("clear");
    system("setterm -cursor on");//on remet le curseur
    return 0;
}

void directionAleatoire(Avion *avion){ //fonction direction
int aleatoire_ab(int a, int b) // creation d'une fonction aleatoire
	{
		srand(time(NULL));
		int c = rand()%((b+1)-a)+a;
		return c;
	}
int nombre = aleatoire_ab(1, 4);
    switch(nombre){ //switch : si aleatoire = 2 la direction de l'avion sera gauche et je recupere l'image avionGauche.pbm
        case 1:
            avion->direction = "droite"; 
            strcpy(avion->imgPbm.nom, "avionDroite.pbm");
            break; //le break permet de sortir de la condition
        case 2:
            avion->direction = "gauche";
            strcpy(avion->imgPbm.nom, "avionGauche.pbm");
            break;
        case 3:
            avion->direction = "haut";
            strcpy(avion->imgPbm.nom, "avionHaut.pbm");
            break;
        case 4:
            avion->direction = "bas";
            strcpy(avion->imgPbm.nom, "avionBas.pbm");
            break;
    }
}

void lireResolution(FILE *fichier, PBM* p) //fonction lireResolution
{
    char lireLigne[10] = ""; //initialise d'une chaine de 10 caracteres
    int a, b;
    for(int i = 0; i < 1; i++)
    {
        fgets(lireLigne, 71, fichier);//-----------------------------------------------------------------------
    }
    fscanf(fichier, "%d %d", &(p->hauteur), &(p->longueur));// on recupere la hauteur et la longueur du fichier PBM
}

void chargerPBM(FILE *fichier, PBM* p)//fonction chargerPBM
{
    char lireFichier[71] = "";// chaine lire le fichierPBM
    int PBMbinaire;

    fgets(lireFichier, 71, fichier);
    while (fgets(lireFichier, 71, fichier) != NULL)//-----------------------------------------------------------------------
    {
        for(int z = 0; z < p->longueur; z++)
        {
            for(int k = 0; k < p->hauteur; k++) //on lit le fichier en fonction de la hauteur et de la longueur de celui ci
            {
                fscanf(fichier, "%d", &PBMbinaire);//-----------------------------------------------------------------------
                p->image[k + ((80 - p->hauteur)/2)][z + ((24 - p->longueur)/2)] = PBMbinaire;//-----------------------------------------------------------------------
            }
        }
    }
}
void afficherPBM(PBM p)
{
	char c[] = {226, 150, 136, 0};
    for (int i = 0 ;i < 24; i++)
    {
        for (int j = 0;j < 80; j++)
        {
            if(p.image[j][i] == 0)
            {
                printf(" ");
            }
            else
            {
                printf("%s", c);
            }
        }
        printf("\n");
    }
}

void chargerCheminResolution(Avion *avion){ //fonction pour charger le chemin et la resolution
    char fichierPBM[1024];
    char* chaine = getenv("EXIASAVER3_PBM"); //creation d'une chaine de caractere qui recupere la variable d'environnement EXIASAVER3_PBM
    if(chaine != NULL) strcpy(fichierPBM, chaine);// si chaine n'est pas nul, je copie le contenu de chaine sur fichierPBM
    else getcwd(fichierPBM, 1024);//copie le chemin d'accès du répertoire de travail courant dans la chaîne fichierPBM

    strcat(fichierPBM, "/"); //ajouter le / pour indiquer que le dernier fichier du chemin est un repertoire
    strcat(fichierPBM, avion->imgPbm.nom); //ajoute le nom de l'image defini dans directionAleatoire dans le chemin  ex : /avionDroite.pbm"
    FILE* fichier = NULL; //initialisation a NULL de la variable du fichier contenant l'image 
    fichier = fopen(fichierPBM, "r"); //ouvrir fichier PBM
    if(fichier == NULL){ //s'il n'existe pas
        printf("Impossible d'ouvir le fichier PBM\n"); // en cas d'erreur afficher message
        exit(-1); //retourne une erreur
    }

    lireResolution(fichier, &avion->imgPbm);//lancer fonction lireResolution
    for(int i=0; i<80; i++){
        for(int j=0; j<24; j++){
            avion->imgPbm.image[i][j] = 0; //----------------------------------------------------------------------
        }
    }
    chargerPBM(fichier, &avion->imgPbm); //on lance la fonction charger PBM
    fclose(fichier); //fermer le fichier (obligatoire pour eviter le gaspillage de la memoire)
}

void placePBM(PBM *dst, PBM *source, int x, int y)
{
	int i, j;

	for (i = 0; i < dst->longueur; ++i)
	{
		for (j = 0; j < dst->hauteur; ++j)
		{
            dst->image[((x+dst->longueur)+i)%dst->longueur][((y+dst->hauteur)+j)%dst->hauteur] = source->image[i][j];
		}
	}
}

void deplacerAvion(Avion* avion){ //fonction pour deplacer l'avion
    PBM ciel; // creation de ciel dans la structure
    ciel = viderCiel(); //on vide le ciel grace a la fonction viderciel
    strcpy(ciel.nom, "ciel");

    if(strcmp(avion->direction, "gauche") == 0){ //------------------------------------------------------------------------
        strcpy(avion->imgPbm.nom, "avionGauche.pbm");
        chargerCheminResolution(avion);// on charge le chemin de l'image 
        avion->posX -= 3; //on le deplace de -3 vers la gauche
        avion->posX = (avion->posX+80)%80;
        placePBM(&ciel, &avion->imgPbm, avion->posX,avion->posY);//on place l'avion dans le ciel avec la fonction placePBM

    }
    else if(strcmp(avion->direction, "haut") == 0){//pareille pour les autres deplacements
        strcpy(avion->imgPbm.nom, "avionHaut.pbm");
        chargerCheminResolution(avion);
        avion->posY -= 1; //comme la console est plus longue que large on effectue de moins grands deplacements vers le haut
        placePBM(&ciel, &avion->imgPbm, avion->posX,avion->posY);
    }
    else if(strcmp(avion->direction, "droite") == 0){
        strcpy(avion->imgPbm.nom, "avionDroite.pbm");
        chargerCheminResolution(avion);
        avion->posX += 3;
        placePBM(&ciel, &avion->imgPbm, avion->posX,avion->posY);
    }
    else if(strcmp(avion->direction, "bas") == 0){
        strcpy(avion->imgPbm.nom, "avionBas.pbm");
        chargerCheminResolution(avion);
        avion->posY += 1;
        placePBM(&ciel, &avion->imgPbm, avion->posX,avion->posY);
    }
    avion->imgPbm = ciel;//-----------------------------------------------------------------------------------------------
    system("clear");
    afficherPBM(avion->imgPbm);
}

pid_t creerProcessus(void){
    pid_t pid;
    do {
    pid = fork();
    } while ((pid == -1) && (errno == EAGAIN));
    return pid;
}

void processus_fils(){
    char touche[1];
    char t2, t3;
    int quitter = 1;
    while(quitter){
        touche[0] = getch();
        switch(touche[0]){
            case 32:
                close(pipeDescriptor[0]);
                write(pipeDescriptor[1], "q", TAILLETOUCHE);
                quitter = 0;
                break;
            case 27:
                t2 = getch();
                if(t2 == 91){
                    t3 = getch();
                    switch(t3){
                        case 68:
                            close(pipeDescriptor[0]);
                            write(pipeDescriptor[1], "l", TAILLETOUCHE);
                            break;
                        case 65:
                            close(pipeDescriptor[0]);
                            write(pipeDescriptor[1], "u", TAILLETOUCHE);
                            break;
                        case 67:
                            close(pipeDescriptor[0]);
                            write(pipeDescriptor[1], "r", TAILLETOUCHE);
                            break;
                        case 66:
                            close(pipeDescriptor[0]);
                            write(pipeDescriptor[1], "d", TAILLETOUCHE);
                            break;
                        default:
                            break;
                    }
                }
                break;
            default:
                break;
        }
    }
    exit(0);
}

void processus_pere(Avion *avion){
    char* touche = malloc(TAILLETOUCHE);
    int avancer;
    int flags = fcntl(pipeDescriptor[0], F_GETFL, 0); //permet de faire avancer l'avion tout seul
    fcntl(pipeDescriptor[0], F_SETFL, flags | O_NONBLOCK);
    int quitter = 1;
    while(quitter){
        close(pipeDescriptor[1]);
        avancer = read(pipeDescriptor[0], touche, TAILLETOUCHE);
        usleep(75000);//pause entre chaques deplacements
        if(avancer < 0 && errno == EAGAIN){
            deplacerAvion(avion);
        }else if(avancer >=0 ){
            switch(*touche){
                case 'q':
                    quitter = 0;
                    break;
                case 'l':
                    avion->direction = "gauche";
                    break;
                case 'u':
                    avion->direction = "haut";
                    break;
                case 'r':
                    avion->direction = "droite";
                    break;
                case 'd':
                    avion->direction = "bas";
                    break;
                default:
                    break;
            }
        }
    }
    free(touche);
}

