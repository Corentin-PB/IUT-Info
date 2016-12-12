// Evenements.cc

#include <iostream>
#include <cstdlib>

#include "Evenements.h"

using namespace std;

/****************** Nom de la fonction **********************
* Evenements                                                *
******************** Auteur , Dates *************************
* Nom/Date : Multiples auteurs                              *
********************* Description ***************************
* Gère tous les événements du programme, allant de la       *
* souris, au clavier en passant par la vérification des     *
* conditions de victoire du joueur ou encore le changement  *
* d'état des monstres ou des éléments du jeu                *
*********************** Entrées *****************************
* Les différentes surfaces à tester, plusieurs booléens de  *
* tests à renvoyer à d'autres fonctions et les variables    *
* relatives aux niveaux (et bien sûr la variable event)     *
*********************** Sorties *****************************
* Renvoie en paramètre la variable event, les différentes   *
* surfaces en cas de modification, les booléens de test     *
* et les niveaux qui peuvent aussi être modifiés            *
************************************************************/
void Evenements(SDL_Event &event, Bouton &boutonPlay, Bouton &boutonQuitter, Bouton &boutonRestart, Bouton &boutonParam, Bouton &boutonRetour, SDL_Surface *screen, SDL_Surface *fondJeu, Niveau &n, Sprite sprites, SDL_Rect &lecturePlay, SDL_Rect lectureQuitter, SDL_Rect lectureParam,
                bool &quit, bool &menuPrin, bool &menuJeu, bool &menuTuto, bool &nivTermine, bool &jeuTermine,  int &niveauCourant, int &direction)
{
    // Gestion des événements
    while(SDL_PollEvent(&event))
        if(event.type==SDL_QUIT)
            quit=true;

    // Récupération de la position du pointeur de la souris
    int x, y;
    SDL_GetMouseState(&x,&y);

    if (menuPrin)
    {
        // Bouton 'Jouer'
        if (x >= boutonPlay.x && x <= boutonPlay.x+110 && y >= boutonPlay.y && y <= boutonPlay.y+110)
        {
            applySurface(boutonPlay.x-11,boutonPlay.y-13,boutonPlay.source,screen, &lecturePlay);
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                menuPrin = false;
                menuJeu = true;
            }
        }
        // Bouton 'Quitter'
        if (x >= boutonQuitter.x && x <= boutonQuitter.x+70 && y >= boutonQuitter.y && y <= boutonQuitter.y+60)
        {
            applySurface(boutonQuitter.x-2,boutonQuitter.y+3,boutonQuitter.source,screen,&lectureQuitter);
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                quit = true;
            }
        }
        // Bouton 'Param'
        if (x >= boutonParam.x && x <=boutonParam.x+60 && y >= boutonParam.y && y <= boutonParam.y+60)
        {
            applySurface(boutonParam.x,boutonParam.y,boutonParam.source,screen,&lectureParam);
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                menuTuto = true;
                menuPrin = false;
            }
        }
    }
    if (menuTuto)
    {
        // Bouton 'Retour' (menu du tutoriel)
        if (x >= boutonRetour.x && x <= boutonRetour.x+60 && y >= boutonRetour.y && y <= boutonRetour.y+60)
        {
            applySurface(boutonRetour.x,boutonRetour.y,boutonRetour.source,screen,&lectureParam);
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                menuTuto = false;
                menuPrin = true;
            }
        }
    }
    if (menuJeu)
    {
        bool survol, trouve = false;
        int z = 0;
        Uint8 *keystates = SDL_GetKeyState( NULL );

        //Déplacement d'un monstre (fait appel à la fonction présente dans le fichier Mouvement.cc tout en indiquant la direction du déplacement)
        for (int i = 0; i < n.nbMonster; i++)
        {
            if (n.tabMonster[i].typeMonster == VIVANT)
            {
                if ( x >= n.tabMonster[i].x && x <= n.tabMonster[i].x+54 && y >= n.tabMonster[i].y && y <= n.tabMonster[i].y+52)
                {
                    survol = true;
                } else {
                    survol = false;
                }
                if (survol) {
                    if(keystates[SDLK_RIGHT])
                    {
                        direction = 1;
                        moveMonster(n.tabMonster[i], direction, n, screen, fondJeu, i, niveauCourant, sprites);
                    } else if(keystates[SDLK_LEFT])
                    {
                        direction = 3;
                        moveMonster(n.tabMonster[i], direction, n, screen, fondJeu, i, niveauCourant, sprites);
                    } else if(keystates[SDLK_DOWN])
                    {
                        direction = 2;
                        moveMonster(n.tabMonster[i], direction, n, screen, fondJeu, i, niveauCourant, sprites);
                    } else if(keystates[SDLK_UP]) {
                        direction = 4;
                        moveMonster(n.tabMonster[i], direction, n, screen, fondJeu, i, niveauCourant, sprites);
                    }
                }
            }
        }

        // Met à jour le type du monstre (si un monstre dormeur rencontre un vivant)
        for (int i = 0; i < n.nbMonster; i++)
        {
            for (int j = 0; j < n.nbMonster; j++)
            {
                if (n.tabMonster[i].x+58 == n.tabMonster[j].x && n.tabMonster[i].y == n.tabMonster[j].y) {
                    n.tabMonster[j].typeMonster=VIVANT;
                } else if (n.tabMonster[i].x == n.tabMonster[j].x+58 && n.tabMonster[i].y == n.tabMonster[j].y) {
                    n.tabMonster[j].typeMonster=VIVANT;
                } else if (n.tabMonster[i].y+53 == n.tabMonster[j].y && n.tabMonster[i].x == n.tabMonster[j].x) {
                    n.tabMonster[j].typeMonster=VIVANT;
                } else if (n.tabMonster[i].y == n.tabMonster[j].y+53 && n.tabMonster[i].x == n.tabMonster[j].x) {
                    n.tabMonster[j].typeMonster=VIVANT;
                }
            }
        }

        // Bouton 'Restart' (Réinitialisation du niveau)
        if (x >= boutonRestart.x && x <= boutonRestart.x+52 && y >= boutonRestart.y && y <= boutonRestart.y+52)
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                initNiveaux(n,niveauCourant);
            }
        }

        // Vérification du type de tout les monstres afin de vérifier si le niveau est terminé
        nivTermine = true;
        while (z < n.nbMonster && trouve == false) {
            if (n.tabMonster[z].typeMonster == DORMEUR)
            {
                nivTermine = false;
                trouve = true;
            }
            z++;
        }

        // Vérification du niveau courant pour savoir si la fin du jeu est atteinte
        if (niveauCourant == n.nbNiveau) {
            jeuTermine = true;
        }
    }
}
