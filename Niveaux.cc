// Niveaux.cc

#include <iostream>
#include <cstdlib>

#include "Niveaux.h"

using namespace std;

/****************** Nom de la fonction **********************
* initNiveaux                                               *
******************** Auteur , Dates *************************
* Nom/Date : Auteurs multiples                              *
********************* Description ***************************
* Initialise chaque niveau de la structure niveau (nombre   *
* d'obstacles, de monstres, le nombre de niveau et pour     *
* finir remplit les champs de chaque monstre et obstacle    *
* dans un tableau de monstre et un tableau d'obstacles)     *
*********************** Entrées *****************************
* La structure niveau, et le niveau courant où le joueur    *
* se trouve                                                 *
*********************** Sorties *****************************
* Renvoie le niveau modifié en référence                    *
************************************************************/

// En cas de changement sur les niveaux :
// Position initiale : x=17 y=30
// Ligne x : x+=58
// ligne y : y+=53
// Ne pas oublier de changer les valeurs "nbNiveau", "nbObstacle", "nbMonstres"
// Sinon, risque de bugs lors de parcours des boucles

void initNiveaux(Niveau &n, int niv)
{
    n.score[niv-1]=0;
    switch (niv) {
    case 1:
    {
        n.tabMonster[0] = initMonster(75,83,VIVANT);
        n.tabMonster[1] = initMonster(17,295,DORMEUR);
        n.tabMonster[2] = initMonster(249,295,DORMEUR);
        n.nbMonster = 3;
        initObstacle(n.tabObstacle[0],75,348,BIBLIO);
        n.nbObstacle =3;
    } break;
    case 2:
    {
        n.tabMonster[0] = initMonster(75,83,VIVANT);
        n.tabMonster[1] = initMonster(17,295,DORMEUR);
        n.tabMonster[2] = initMonster(249,295,DORMEUR);
        n.nbMonster = 3;
        initObstacle(n.tabObstacle[0],75,348,BIBLIO);
        initObstacle(n.tabObstacle[1],75,242,BIBLIO);
        initObstacle(n.tabObstacle[2],17,83,DOWN);
        n.nbObstacle =4;
    } break;
    case 3:
    {
        n.tabMonster[0]= initMonster(17,242,VIVANT);
        n.tabMonster[1]= initMonster(17,83,DORMEUR);
        n.tabMonster[2]= initMonster(75,30,DORMEUR);
        n.tabMonster[3]= initMonster(249,295,DORMEUR);
        n.tabMonster[4]= initMonster(191,348,DORMEUR);
        n.nbMonster=5;

        initObstacle(n.tabObstacle[4],75,83,GLACE);
        initObstacle(n.tabObstacle[1],249,30,DOWN);
        initObstacle(n.tabObstacle[2],75,454,RIGHT);
        initObstacle(n.tabObstacle[3],191,454,UP);
        initObstacle(n.tabObstacle[0],133,242,BIBLIO);
        initObstacle(n.tabObstacle[5],191,295,BIBLIO);
        initObstacle(n.tabObstacle[6],249,348,BIBLIO);
        initObstacle(n.tabObstacle[7],133,348,BIBLIO);

        n.nbObstacle=8;


    }break;
    }
}

