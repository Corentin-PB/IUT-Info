// Evenements.h

#include <SDL/SDL.h>

#include "Structures.h"
#include "Fonctions.h"

#ifndef EVENEMENTS_H
#define EVENEMENTS_H

using namespace std;

void Evenements(SDL_Event &event, Bouton &boutonPlay, Bouton &boutonQuitter, Bouton &boutonRestart, bool &quit, bool &menuPrin, bool &menuJeu, Niveau &n, int &direction, SDL_Surface *screen, bool &nivTermine, int &niveauCourant, bool &jeuTermine, Sprite sprites);

#endif // EVENEMENTS_H
