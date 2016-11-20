// Structures.h

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <array>

#ifndef STRUCTURES_H
#define STRUCTURES_H

using namespace std;

// Initialisation des variables constantes du programme
const int SCREEN_WIDTH=320;
const int SCREEN_HEIGHT=568;
const int SCREEN_BPP=32;
const int NB_MAX = 45;

enum enumMonster {
    VIVANT,
    DORMEUR,
    MORT
};

struct Monster {
    enumMonster typeMonster;
    int x;
    int y;
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
};

struct Obstacle {
    int x;
    int y;
};

void initVariables();

struct Niveau {
    array <Monster,NB_MAX> tabMonster;
    int nbMonsterSleep;
};

#endif // STRUCTURES_H
