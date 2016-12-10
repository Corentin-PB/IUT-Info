#include <iostream>
#include <cstdlib>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <sstream>
#include <ctime>

#include "Evenements.h"
#include "Affichage.h"
#include "Initialisation.h"

using namespace std;

//Initialisation d'une police de caractère sans paramètres (pour le moment)
TTF_Font *fonts;

int main()
{
    // Initialisation des variables de base nécessaires au programme pour fonctionner
    bool quit = false, menuPrin = true, menuJeu = false, menuTuto=false, nivTermine = false, jeuTermine = false;
    int niveauCourant = 1, direction;
    SDL_Surface *screen, *menu, *fondJeu, *tuto, *nivTerm, *jeuTerm, *boutonQuitterDefaut;
    SDL_Event event;
    SDL_Rect lectureFen, lecturePlay, lectureParam, lectureQuitter;
    Bouton boutonPlay;
    Bouton boutonQuitter;
    Bouton boutonRestart;
    Bouton boutonParam;
    Bouton boutonRetour;
    Sprite sprites;
    Niveau n;

    //Affecte les valeurs aux variables créées
    initJeu(n, niveauCourant, boutonRestart, boutonPlay, boutonQuitter, boutonParam, boutonRetour, lectureFen, sprites, lecturePlay, lectureParam, lectureQuitter);

    // Création de la fenêtre de jeu
    SDL_Init(SDL_INIT_EVERYTHING);
    screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,
                            SCREEN_BPP,SDL_SWSURFACE);

    // Définition du chemin des images pour tous les objets
    menu=loadImageWithColorKey("menu.bmp",0,0,255);
    fondJeu=load_image("background.bmp");
    sprites.source=loadImageWithColorKey("sprite.bmp",255,255,255);
    nivTerm=load_image("winSprite.bmp");
    jeuTerm=load_image("winEndSprite.bmp");
    boutonPlay.source=loadImageWithColorKey("boutonAppuieJouer.bmp",0,0,255);
    boutonParam.source=load_image("boutonAppuieParam.bmp");
    boutonRetour.source=loadImageWithColorKey("boutonRetourAppuie.bmp",0,0,255);
    boutonQuitter.source=loadImageWithColorKey("boutonQuitter.bmp",0,0,255);
    boutonQuitterDefaut=loadImageWithColorKey("boutonQuitterDefaut.bmp",0,0,255);
    tuto=load_image("tuto.bmp");


    while(!quit)
    {
        // Affichage de l'écran sur la fenêtre
        SDL_FillRect(screen,&screen->clip_rect,
                     SDL_MapRGB(screen->format,255,255,255));

        // Affichage de l'ensemble des objets du programme
        Affichage(menuPrin, menuJeu, menuTuto, niveauCourant, nivTermine, jeuTermine, menu, screen, fondJeu, tuto, nivTerm, lectureFen, jeuTerm, sprites, n, boutonQuitter, boutonQuitterDefaut, lectureQuitter);

        // Gestion de tous les événements du programme
        Evenements(event, boutonPlay, boutonQuitter, boutonRestart, boutonParam, boutonRetour, screen, n, sprites, lecturePlay, lectureQuitter, lectureParam, quit, menuPrin, menuJeu, menuTuto, nivTermine, jeuTermine, niveauCourant, direction);

        // Rafraîchissement de l'écran
        SDL_Flip(screen);
    }

    // Libération des surfaces et sortie du programme
    SDL_FreeSurface(screen);
    SDL_FreeSurface(menu);
    SDL_FreeSurface(fondJeu);
    SDL_FreeSurface(sprites.source);
    SDL_FreeSurface(nivTerm);
    SDL_FreeSurface(jeuTerm);
    SDL_Quit();
    return EXIT_SUCCESS;
}
