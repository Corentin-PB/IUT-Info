// Evenements.h

#include <SDL/SDL.h>

#include "Mouvement.h"
#include "Niveaux.h"

#ifndef EVENEMENTS_H
#define EVENEMENTS_H

using namespace std;

void Evenements(SDL_Event &event, Bouton &boutonPlay, Bouton &boutonQuitter, Bouton &boutonRestart, Bouton &boutonParam, Bouton &boutonRetour, SDL_Surface *screen, SDL_Surface *fondJeu, Niveau &n, Sprite sprites, SDL_Rect &lecturePlay, SDL_Rect lectureQuitter, SDL_Rect lectureParam,
                bool &quit, bool &menuPrin, bool &menuJeu, bool &menuTuto, bool &nivTermine, bool &jeuTermine, int &niveauCourant, int &direction);

#endif // EVENEMENTS_H
