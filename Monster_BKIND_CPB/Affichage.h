// Affichage.h

#include <SDL/SDL.h>

#include "Structures.h"

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

using namespace std;

void Affichage(bool menuPrin, bool menuJeu, SDL_Surface *menu, SDL_Surface *screen, SDL_Surface *fondJeu, SDL_Rect lectureFen, Sprite sprites, Niveau n, int &niveauCourant);

#endif // AFFICHAGE_H
