// Evenements.h

#include <SDL/SDL.h>

#include "Structures.h"

#ifndef EVENEMENTS_H
#define EVENEMENTS_H

using namespace std;

void Evenements(SDL_Event &event, Bouton &boutonPlay, Bouton &boutonQuitter, bool &quit, bool &menuPrin, bool &menuJeu);

#endif // EVENEMENTS_H
