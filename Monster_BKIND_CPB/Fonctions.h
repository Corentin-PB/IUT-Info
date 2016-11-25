// Fonctions.h

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <array>

#include "Structures.h"

#ifndef FONCTIONS_H
#define FONCTIONS_H

using namespace std;
const int TAILLEMAX = 9;
using TJeu = array<array<int,TAILLEMAX>,TAILLEMAX>;

void initRect(SDL_Rect &Rect, int a, int b, int c, int d);
void initBouton(Bouton &b,int x, int y, int w, int h);
SDL_Surface *load_image( string filename );
SDL_Surface *loadImageWithColorKey(string filename, int r, int g, int b);
void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
void showMessageScreen(string message,int x,int y,TTF_Font *font,int fontSize,SDL_Color textColor,SDL_Surface* &screen);
void showMonster(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
void showObstacle(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
void initMonster(Monster &monster, int x, int y, enumMonster typeMonster);
void initNiveaux(Niveau &n, int niv);
Monster initMonster(int x, int y, enumMonster typeMonster);
SDL_Rect initTypeMonstre(Monster m, Sprite sprites);
void initObstacle (Obstacle &o, int x, int y);
bool collision(Monster b ,Monster x);
void moveMonster(Monster &m, int &direction, Niveau n, SDL_Surface *screen, int indice);


#endif // FONCTIONS_H
