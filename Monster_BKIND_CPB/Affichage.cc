// Affichage.cc

#include <iostream>
#include <cstdlib>

#include "Affichage.h"
#include "Fonctions.h"
#include "Structures.h"
#include "Niveaux.h"

void Affichage(bool menuPrin, bool menuJeu, SDL_Surface *menu, SDL_Surface *screen, SDL_Surface *fondJeu, SDL_Rect lectureFen, Sprite sprites, Niveau n, int &niveauCourant)
{
    if (menuPrin)
    {
        applySurface(0,0,menu,screen,&lectureFen);
    }

    if (menuJeu)
    {
        applySurface(0,0,fondJeu,screen,&lectureFen);
        switch (niveauCourant) {
        case 1:
        {
            //showMonster(20,228,);
        } break;
        case 2:
        {

        } break;
        }
        //defaut: x20 y36
        //x +=58
        //y +=48
        //
        //-9y MonsterSleep
        //+5x Monster
        //-3x -16y Biblio
        //-3x -16y Glace
        //+4x +4y Up
        //+4x +4y Down
        //+4x +4y Left
        //+4x +4y Right
    }
}

using namespace std;

