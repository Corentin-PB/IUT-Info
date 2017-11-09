// INITIALISATION.h

#include <SDL/SDL.h>
#include <array>
#include <SDL/SDL_ttf.h>

#ifndef INITIALISATION_H
#define INITIALISATION_H

using namespace std;

// Initialisation des variables constantes du programme
const int SCREEN_WIDTH=320;
const int SCREEN_HEIGHT=568;
const int SCREEN_BPP=32;
const int NB_MAX = 45;
const int NB_NIVEAU = 3;

enum enumObstacle {
    UP,
    DOWN,
    RIGHT,
    LEFT,
    GLACE,
    BIBLIO
};

struct Obstacle {
    enumObstacle typeObstacle;
    int x;
    int y;
    int w;
    int h;
};

struct Sprite {
    SDL_Surface *source;
    SDL_Rect lecture_Biblio;
    SDL_Rect lecture_Glace;
    SDL_Rect lecture_MonsterSleep;
    SDL_Rect lecture_Monster;
    SDL_Rect lecture_Down;
    SDL_Rect lecture_Up;
    SDL_Rect lecture_Right;
    SDL_Rect lecture_Left;
    SDL_Rect lecture_Rien;
};

struct Bouton {
    int x;
    int y;
    int w;
    int h;
    SDL_Rect lecture;
    SDL_Surface *source;
};

enum enumMonster {
    VIVANT,
    DORMEUR,
    MORT
};

struct Monster {
    enumMonster typeMonster;
    int x;
    int y;
    int w;
    int h;
};

struct Niveau {
    int nbMonster;
    int nbObstacle;
    array <Monster,NB_MAX> tabMonster;
    array <Obstacle,NB_MAX> tabObstacle;
    array <int,NB_NIVEAU> score;
};

void initNiveaux(Niveau &n, int niv);
SDL_Rect initTypeMonstre(Monster m, Sprite sprites);
void initObstacle (Obstacle &o, int x, int y, enumObstacle typeObstacle);
Monster initMonster(int x, int y, enumMonster typeMonster);
void initBouton(Bouton &b, int x, int y, int w, int h);
void initRect(SDL_Rect &Rect, int a, int b, int c, int d);
void initNiveaux(Niveau &n, int niv);
void initJeu(Niveau &n, int &niveauCourant, Bouton &boutonRestart, Bouton &boutonPlay, Bouton &boutonQuitter, Bouton &boutonParam, Bouton &boutonRetour, SDL_Rect &lectureFen, Sprite &sprites, SDL_Rect &lecturePlay, SDL_Rect &lectureParam, SDL_Rect &lectureQuitter);

#endif // INITIALISATION_H
