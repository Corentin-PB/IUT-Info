#include <iostream>
#include <cstdlib>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <sstream>
#include <ctime>

#include "Fonctions.h"
#include "Structures.h"
#include "Evenements.h"
#include "Affichage.h"
#include "Niveaux.h"

using namespace std;

//Initialisation d'une police de caractère sans paramètres (pour le moment)
TTF_Font *fonts;

int
main()
{
    // INITIALITATIONS VARIABLES / FONTS / MENUS / OBJETS
    bool quit = false, menuPrin = true, menuJeu = false, nivTermine = false, jeuTermine = false;
    SDL_Surface *screen, *menu, *fondJeu, *nivTerm, *jeuTerm;
    SDL_Event event;
    SDL_Rect lectureFen;
    Bouton boutonPlay;
    Bouton boutonQuitter;
    Bouton boutonRestart;
    Sprite sprites;
    int niveauCourant = 1, direction;
    Niveau n;
    initNiveaux(n,niveauCourant);
    initBouton(boutonRestart,70,507,55,55);
    initRect(lectureFen,0,0,320,568);
    initBouton(boutonPlay,100,265,95,95);
    initBouton(boutonQuitter,195,345,50,50);
    initRect(sprites.lecture_MonsterSleep,54,0,54,52);
    initRect(sprites.lecture_Monster,0,52,54,52);
    initRect(sprites.lecture_Biblio,54,52,54,52);
    initRect(sprites.lecture_Glace,0,0,54,52);
    initRect(sprites.lecture_Right,0,156,54,52);
    initRect(sprites.lecture_Left,54,156,54,52);
    initRect(sprites.lecture_Up,54,104,54,52);
    initRect(sprites.lecture_Down,0,104,54,52);
    initRect(sprites.lecture_Rien,0,0,0,0);

    // Création de la fenêtre de jeu
    SDL_Init(SDL_INIT_EVERYTHING);
    screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,
                            SCREEN_BPP,SDL_SWSURFACE);

    // Définition du chemin des images pour tous les objets
    menu=load_image("menu.bmp");
    fondJeu=load_image("background.bmp");
    sprites.source=loadImageWithColorKey("sprite.bmp",255,255,255);
    nivTerm=load_image("winSprite.bmp");
    jeuTerm=load_image("winEndSprite.bmp");

    while(!quit)
    {
        // Affichage de l'écran sur la fenêtre
        SDL_FillRect(screen,&screen->clip_rect,
                     SDL_MapRGB(screen->format,255,255,255));

        Affichage(quit ,menuPrin, menuJeu, menu, screen, fondJeu, nivTerm, lectureFen,sprites, n, niveauCourant, nivTermine, event, jeuTerm, jeuTermine);

        Evenements(event, boutonPlay, boutonQuitter, boutonRestart, quit, menuPrin, menuJeu, n, direction, screen, nivTermine, niveauCourant, jeuTermine);

        SDL_Flip(screen);
    }

    // LIBERATION DES SURFACES
    SDL_FreeSurface(screen);
    SDL_FreeSurface(menu);
    SDL_FreeSurface(fondJeu);
    SDL_FreeSurface(sprites.source);
    SDL_FreeSurface(nivTerm);
    SDL_FreeSurface(jeuTerm);
    SDL_Quit();
    return EXIT_SUCCESS;
}
