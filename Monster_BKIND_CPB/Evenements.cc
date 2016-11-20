// Evenements.cc

#include <iostream>
#include <cstdlib>

#include "Evenements.h"
#include "Structures.h"

using namespace std;

void Evenements(SDL_Event &event, Bouton &boutonPlay, Bouton &boutonQuitter, bool &quit, bool &menuPrin, bool &menuJeu)
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
}
