//
//  statique.h
//  test
//
//  Created by Quentin bechade on 12/12/2016.
//  Copyright © 2016 Quentin bechade. All rights reserved.
//

#ifndef statique_h
#define statique_h

void choixAleatoireImage(Pbm* p); // fonction qui va permettre de choisir un PBM alÈatoirement
void lireResolution(FILE *fichier, Pbm* p); // permet de stocker la rÈsolution de notre image
void insererImageCentreeDansTableau(FILE *fichier, Pbm* p, int tableauPourImage[80][24]); // permet de charger l'image dans le tableau ‡ deux dimensions tout en la centrant
void afficherTableau(int tableauPourImage[80][24]); // va nous permettre d'afficher le tableau 2D
void manipulationFichier(); // elle effectue touss les mainpulation dans le fichier effectue un choix aléatoire pour le PBM, charge l'image et centre l'image.


#endif /* statique_h */
