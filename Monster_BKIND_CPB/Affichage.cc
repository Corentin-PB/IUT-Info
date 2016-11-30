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
        SDL_Rect typeMonstre;
        switch (niveauCourant) {
        case 1:
        {
            showObstacle(n.tabObstacle[0].x,n.tabObstacle[0].y,sprites.source,screen,&sprites.lecture_Biblio);
            showObstacle(n.tabObstacle[1].x,n.tabObstacle[1].y,sprites.source,screen,&sprites.lecture_Glace);
            showObstacle(n.tabObstacle[2].x,n.tabObstacle[2].y,sprites.source,screen,&sprites.lecture_Up);
            typeMonstre=initTypeMonstre(n.tabMonster[0],sprites);
            showMonster(n.tabMonster[0].x,n.tabMonster[0].y,sprites.source,screen,&typeMonstre);
            typeMonstre=initTypeMonstre(n.tabMonster[1],sprites);
            showMonster(n.tabMonster[1].x,n.tabMonster[1].y,sprites.source,screen,&typeMonstre);
            typeMonstre=initTypeMonstre(n.tabMonster[2],sprites);
            showMonster(n.tabMonster[2].x,n.tabMonster[2].y,sprites.source,screen,&typeMonstre);
        } break;
        case 2:
        {

        } break;
        }
        //defaut: x17 y30
        //x +=58
        //y +=53
    }
}

using namespace std;

