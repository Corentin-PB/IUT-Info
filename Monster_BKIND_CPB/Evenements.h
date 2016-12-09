// Evenements.h

#include <SDL/SDL.h>

#include "Mouvement.h"
#include "Niveaux.h"

#ifndef EVENEMENTS_H
#define EVENEMENTS_H

using namespace std;

void Evenements(SDL_Event &event, Bouton &boutonPlay, Bouton &boutonQuitter, Bouton &boutonRestart, SDL_Surface *screen, Niveau &n, Sprite sprites,
                bool &quit, bool &menuPrin, bool &menuJeu, bool &nivTermine, bool &jeuTermine, int &niveauCourant, int &direction);

#endif // EVENEMENTS_H
