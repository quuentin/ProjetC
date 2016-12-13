//
//  pbm.h
//  test
//
//  Created by Quentin bechade on 12/12/2016.
//  Copyright © 2016 Quentin bechade. All rights reserved.
//

#ifndef pbm_h
#define pbm_h

typedef struct Pbm Pbm; // on remplace "struct Pbm" par "Pbm" pour raccourcir le code
struct Pbm // dÈfinition de notre structure Pbm
{
    int largeurImage;   // ces deux int vont stocker la rÈsolution de l'image
    int longueurImage;
    char nomImage[100]; // va comporter le nom de notre fichier PBM tirÈ alÈatoirement
};


#endif /* pbm_h */
