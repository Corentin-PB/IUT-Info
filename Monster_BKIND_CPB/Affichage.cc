﻿// Affichage.cc

#include <iostream>
#include <cstdlib>

#include "Affichage.h"
#include "Fonctions.h"
#include "Structures.h"
#include "Niveaux.h"

void Affichage(bool &quit, bool menuPrin, bool menuJeu, SDL_Surface *menu, SDL_Surface *screen, SDL_Surface *fondJeu, SDL_Surface *nivTerm, SDL_Rect lectureFen, Sprite sprites, Niveau &n, int &niveauCourant, bool &nivTermine, SDL_Event &event, SDL_Surface *jeuTerm, bool jeuTermine)
{
    if (menuPrin)
    {
        applySurface(0,0,menu,screen,&lectureFen);
    }
    if (menuJeu)
    {
        if (nivTermine) {
            bool continuer = true;
            while (continuer)
            {
                if (SDL_PollEvent(&event))
                {
                    switch(event.type)
                    {
                    case SDL_KEYDOWN:
                    {
                        continuer = false;
                    }
                    }
                }
                applySurface(0,0,nivTerm,screen,&lectureFen);
                SDL_Flip(screen);
            }
            niveauCourant++;
            initNiveaux(n,niveauCourant);
            nivTermine = false;
        }
        if (jeuTermine) {
            bool continuer = true;
            while (continuer)
            {
                if (SDL_PollEvent(&event))
                {
                    switch(event.type)
                    {
                    case SDL_KEYDOWN:
                    {
                        continuer = false;
                    }
                    }
                }
                applySurface(0,0,jeuTerm,screen,&lectureFen);
                SDL_Flip(screen);
            }
            quit = true;
        }
        applySurface(0,0,fondJeu,screen,&lectureFen);
        SDL_Rect typeMonstre;
        switch (niveauCourant) {
        case 1:
        {
            showObstacle(n.tabObstacle[0].x,n.tabObstacle[0].y,sprites.source,screen,&sprites.lecture_Biblio);
            typeMonstre=initTypeMonstre(n.tabMonster[0],sprites);
            showMonster(n.tabMonster[0].x,n.tabMonster[0].y,sprites.source,screen,&typeMonstre);
            typeMonstre=initTypeMonstre(n.tabMonster[1],sprites);
            showMonster(n.tabMonster[1].x,n.tabMonster[1].y,sprites.source,screen,&typeMonstre);
            typeMonstre=initTypeMonstre(n.tabMonster[2],sprites);
            showMonster(n.tabMonster[2].x,n.tabMonster[2].y,sprites.source,screen,&typeMonstre);
        } break;
        case 2:
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
        }
        //defaut: x17 y30
        //x +=58
        //y +=53
    }
}

using namespace std;

