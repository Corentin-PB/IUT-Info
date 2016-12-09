// Mouvement.h

#include <SDL/SDL.h>

#include "Initialisation.h"
#include "Affichage.h"

#ifndef MOUVEMENT_H
#define MOUVEMENT_H

using namespace std;

void moveMonster(Monster &m, int &direction, Niveau &n, SDL_Surface *screen, int indice, int &niveauCourant, Sprite &sprites);

#endif // MOUVEMENT_H
