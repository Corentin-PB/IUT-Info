// Affichage.h

#include <SDL/SDL.h>

#include "Structures.h"

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

using namespace std;

void Affichage(bool &quit, bool menuPrin, bool menuJeu, SDL_Surface *menu, SDL_Surface *screen, SDL_Surface *fondJeu, SDL_Surface *nivTerm, SDL_Rect lectureFen, Sprite sprites, Niveau &n, int &niveauCourant, bool &nivTermine, SDL_Event &event, SDL_Surface *jeuTerm, bool jeuTermine);

#endif // AFFICHAGE_H
