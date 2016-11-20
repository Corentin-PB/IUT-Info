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
main(int argc, char* argv[])
{
    // INITIALITATIONS VARIABLES / FONTS / MENUS / OBJETS
    bool quit = false, menuPrin = true, menuJeu = false;
    SDL_Event event;
    SDL_Surface *screen, *menu, *fondJeu;
    SDL_Rect lectureFen;
    Bouton boutonPlay;
    Bouton boutonQuitter;
    Sprite sprites;
    int niveauCourant;
    Niveau n;
    //initVariables(n, niveauCourant, lectureFen, boutonPlay, boutonQuitter, sprites);

    // Création de la fenêtre de jeu
    SDL_Init(SDL_INIT_EVERYTHING);
    screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,
                            SCREEN_BPP,SDL_SWSURFACE);

    // Définition du chemin des images pour tous les objets
    menu=load_image("menu.bmp");
    fondJeu=load_image("background.bmp");
    sprites.source=loadImageWithColorKey("sprite.bmp",255,255,255);

    while(!quit)
    {
        // Affichage de l'écran sur la fenêtre
        SDL_FillRect(screen,&screen->clip_rect,
                     SDL_MapRGB(screen->format,255,255,255));
        initNiveaux(n,niveauCourant);

        Affichage(menuPrin, menuJeu, menu, screen, fondJeu, lectureFen,sprites, n, niveauCourant);

        Evenements(event, boutonPlay, boutonQuitter, quit, menuPrin, menuJeu);

        SDL_Flip(screen);
    }

    // LIBERATION DES SURFACES
    SDL_FreeSurface(screen);
    SDL_FreeSurface(menu);
    SDL_FreeSurface(fondJeu);
    SDL_Quit();
    return EXIT_SUCCESS;
}
