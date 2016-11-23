// Evenements.h

#include <SDL/SDL.h>

#include "Structures.h"
#include "Fonctions.h"

#ifndef EVENEMENTS_H
#define EVENEMENTS_H

using namespace std;

void Evenements(SDL_Event &event, Bouton &boutonPlay, Bouton &boutonQuitter, bool &quit, bool &menuPrin, bool &menuJeu, Niveau &n, int temp1, int temp2, int &direction, SDL_Surface *screen);

#endif // EVENEMENTS_H
