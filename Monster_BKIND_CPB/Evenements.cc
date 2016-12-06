﻿// Evenements.cc

#include <iostream>
#include <cstdlib>

#include "Evenements.h"

using namespace std;

void Evenements(SDL_Event &event, Bouton &boutonPlay, Bouton &boutonQuitter, Bouton &boutonRestart, bool &quit, bool &menuPrin, bool &menuJeu, Niveau &n, int &direction, SDL_Surface *screen, bool &nivTermine,  int &niveauCourant, bool &jeuTermine)
{
    // Gestion des événements
    while(SDL_PollEvent(&event))
        if(event.type==SDL_QUIT)
            quit=true;

    // Récupération de la position du pointeur de la souris
    int x, y;
    SDL_GetMouseState(&x,&y);

    if (menuPrin)
    {
        // Bouton 'Jouer'
        if (x >= boutonPlay.x && x <= boutonPlay.x+95 && y >= boutonPlay.y && y <= boutonPlay.y+95)
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                menuPrin = false;
                menuJeu = true;
            }
        }
        // Bouton 'Quitter'
        if (x >= boutonQuitter.x && x <= boutonQuitter.x+50 && y >= boutonQuitter.y && y <= boutonQuitter.y+50)
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                quit = true;
            }
        }
    }
    if (menuJeu)
    {
        bool survol, trouve = false;
        int z = 0;
        Uint8 *keystates = SDL_GetKeyState( NULL );
        //Déplacement d'un monstre
        for (int i = 0; i < n.nbMonster; i++)
        {
            if (n.tabMonster[i].typeMonster == VIVANT)
            {
                if ( x >= n.tabMonster[i].x && x <= n.tabMonster[i].x+54 && y >= n.tabMonster[i].y && y <= n.tabMonster[i].y+52)
                {
                    survol = true;
                } else {
                    survol = false;
                }
                if (survol) {
                    if(keystates[SDLK_RIGHT])
                    {
                        direction = 1;
                        moveMonster(n.tabMonster[i], direction, n, screen, i, niveauCourant);
                    } else if(keystates[SDLK_LEFT])
                    {
                        direction = 3;
                        moveMonster(n.tabMonster[i], direction, n, screen, i, niveauCourant);
                    } else if(keystates[SDLK_DOWN])
                    {
                        direction = 2;
                        moveMonster(n.tabMonster[i], direction, n, screen, i, niveauCourant);
                    } else if(keystates[SDLK_UP]) {
                        direction = 4;
                        moveMonster(n.tabMonster[i], direction, n, screen, i, niveauCourant);
                    }
                }
            }
        }
        for (int i = 0; i < n.nbMonster; i++)
        {
            for (int j = 0; j < n.nbMonster; j++)
            {
                if (n.tabMonster[i].x+58 == n.tabMonster[j].x && n.tabMonster[i].y == n.tabMonster[j].y) {
                    n.tabMonster[j].typeMonster=VIVANT;
                } else if (n.tabMonster[i].x == n.tabMonster[j].x+58 && n.tabMonster[i].y == n.tabMonster[j].y) {
                    n.tabMonster[j].typeMonster=VIVANT;
                } else if (n.tabMonster[i].y+53 == n.tabMonster[j].y && n.tabMonster[i].x == n.tabMonster[j].x) {
                    n.tabMonster[j].typeMonster=VIVANT;
                } else if (n.tabMonster[i].y == n.tabMonster[j].y+53 && n.tabMonster[i].x == n.tabMonster[j].x) {
                    n.tabMonster[j].typeMonster=VIVANT;
                }
            }
        }
        nivTermine = true;
        while (z < n.nbMonster && trouve == false) {
            if (n.tabMonster[z].typeMonster == DORMEUR)
            {
                nivTermine = false;
                trouve = true;
            }
            z++;
        }
        if (x >= boutonRestart.x && x <= boutonRestart.x+52 && y >= boutonRestart.y && y <= boutonRestart.y+52)
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                initNiveaux(n,niveauCourant);
            }
        }
        if (niveauCourant == n.nbNiveau) {
            jeuTermine = true;
        }
    }
}
