// Affichage.h

#include <SDL/SDL.h>

#include "Niveaux.h"

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

using namespace std;

SDL_Surface *load_image( string filename );
void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
void showMessageScreen(string message,int x,int y, TTF_Font *font,int fontSize,SDL_Color textColor,SDL_Surface* &screen);
SDL_Surface * loadImageWithColorKey(string filename, int r, int g, int b);
void showMonster(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
void showObstacle(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
void Affichage(bool menuPrin, bool menuJeu, int &niveauCourant, bool &nivTermine, bool jeuTermine,
               SDL_Surface *menu, SDL_Surface *screen, SDL_Surface *fondJeu, SDL_Surface *nivTerm, SDL_Rect lectureFen, SDL_Surface *jeuTerm, Sprite sprites, Niveau &n);

#endif // AFFICHAGE_H
