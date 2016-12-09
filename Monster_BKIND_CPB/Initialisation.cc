// Initialisation.cc

#include <iostream>
#include <cstdlib>

#include "Initialisation.h"

using namespace std;

/****************** Nom de la fonction **********************
* initRect                                                  *
******************** Auteur , Dates *************************
* Nom/Date : Multiples auteurs                              *
********************* Description ***************************
* Initialise les champs d'un SDL_Rect en fonction des       *
* paramètres              *                                 *
*********************** Entrées *****************************
* Champs du SDL_Rect                                        *
*********************** Sorties *****************************
* Renvoie le SDL_Rect en référence                          *
************************************************************/
void initRect(SDL_Rect &Rect, int a, int b, int c, int d)
{
    Rect.x=a;
    Rect.y=b;
    Rect.w=c;
    Rect.h=d;
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/****************** Nom de la fonction **********************
* initBouton                                                *
******************** Auteur , Dates *************************
* Nom/Date : Multiples auteurs                              *
********************* Description ***************************
* Initialise les champs d'un Bouton (structure) en fonction *
* des paramètres                                            *
*********************** Entrées *****************************
* Champs du Bouton                                          *
*********************** Sorties *****************************
* Renvoie le Bouton en référence                            *
************************************************************/
void initBouton(Bouton &b, int x, int y, int w, int h)
{
    b.x=x;
    b.y=y;
    b.w=w;
    b.h=h;
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/****************** Nom de la fonction **********************
* initMonster                                               *
******************** Auteur , Dates *************************
* Nom/Date : Auteurs multiples                              *
********************* Description ***************************
* Initialise les champs d'un monstre en fonction des        *
* paramètres                                                *
*********************** Entrées *****************************
* Les champs à modifier pour le monstre et le monstre       *
*********************** Sorties *****************************
* Renvoie le monstre modifié en référence                   *
************************************************************/
Monster initMonster(int x, int y, enumMonster typeMonster) {
    Monster m;
    m.x=x;
    m.y=y;
    m.w=54;
    m.h=52;
    m.typeMonster=typeMonster;
    return m;
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/****************** Nom de la fonction **********************
* initObstacle                                              *
******************** Auteur , Dates *************************
* Nom/Date : Auteurs multiples                              *
********************* Description ***************************
* Initialise les champs d'un obstacle en fonction des       *
* paramètres                                                *
*********************** Entrées *****************************
* Les champs à modifier pour l'obstacle                     *
*********************** Sorties *****************************
* Renvoie l'obstacle modifié en référence                   *
************************************************************/
void initObstacle (Obstacle &o, int x, int y, enumObstacle typeObstacle) {
    o.x=x;
    o.y=y;
    o.w=54;
    o.h=52;
    o.typeObstacle = typeObstacle;
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/****************** Nom de la fonction **********************
* initTypeMonster                                           *
******************** Auteur , Dates *************************
* Nom/Date : Auteurs multiples                              *
********************* Description ***************************
* Initialise le type du monstre (vivant, mort, dormeur) et  *
* permet notemment de rafraichîr à chaque lancement de cette*
* fonction le type du monstre pour l'affichage              *
*********************** Entrées *****************************
* Le monstre et la feuille de sprite (Structure sprite      *
* contenant des rectangles de lectures pour chaque sprite)  *
*********************** Sorties *****************************
* Renvoie le type de monstre en SDL_Rect                    *
************************************************************/
SDL_Rect initTypeMonstre(Monster m, Sprite sprites) {
    SDL_Rect lecture;
    if (m.typeMonster==VIVANT) {
        lecture=sprites.lecture_Monster;
    } else if (m.typeMonster==DORMEUR) {
        lecture=sprites.lecture_MonsterSleep;
    } else if (m.typeMonster==MORT) {
        lecture=sprites.lecture_Rien;
    }
    return lecture;
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/****************** Nom de la fonction **********************
* initJeu                                                   *
******************** Auteur , Dates *************************
* Nom/Date : Auteurs multiples                              *
********************* Description ***************************
* Initialise les principales variables et structures        *
* nécessaires                                               *
*********************** Entrées *****************************
* Le monstre et la feuille de sprite (Structure sprite      *
* contenant des rectangles de lectures pour chaque sprite)  *
*********************** Sorties *****************************
* Renvoie le type de monstre en SDL_Rect                    *
************************************************************/
void initJeu(Niveau &n, int &niveauCourant, Bouton &boutonRestart, Bouton &boutonPlay, Bouton &boutonQuitter, SDL_Rect &lectureFen, Sprite &sprites) {
    initNiveaux(n,niveauCourant);
    initBouton(boutonRestart,70,507,55,55);
    initRect(lectureFen,0,0,320,568);
    initBouton(boutonPlay,100,265,95,95);
    initBouton(boutonQuitter,195,345,50,50);
    initRect(sprites.lecture_MonsterSleep,54,0,54,52);
    initRect(sprites.lecture_Monster,0,52,54,52);
    initRect(sprites.lecture_Biblio,54,52,54,52);
    initRect(sprites.lecture_Glace,0,0,54,52);
    initRect(sprites.lecture_Right,54,156,54,52);
    initRect(sprites.lecture_Left,0,156,54,52);
    initRect(sprites.lecture_Up,54,104,54,52);
    initRect(sprites.lecture_Down,0,104,54,52);
    initRect(sprites.lecture_Rien,0,208,54,262);
}
