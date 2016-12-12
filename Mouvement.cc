// Mouvement.cc

#include <iostream>
#include <cstdlib>

#include "Mouvement.h"

using namespace std;

void moveMonster(Monster &m, int &direction, Niveau &n, SDL_Surface *screen, SDL_Surface *fondJeu, int indice, int &niveauCourant, Sprite &sprites) {

    bool rencontre =false,rencontreBas = false, rencontreHaut = false, rencontreDroite = false, rencontreGauche = false;

    while (!rencontre)
    {
        // Vérification si il y a colision avec un monstre et dans quelle direction
        for (int i = 0; i < n.nbMonster; i++)
        {
            if (indice != i)
            {
                if (m.y+53 == n.tabMonster[i].y && m.x == n.tabMonster[i].x)
                {
                    rencontreBas=true;
                } else if (m.y == n.tabMonster[i].y+53 && m.x == n.tabMonster[i].x) {
                    rencontreHaut=true;
                } else if (m.x+58 == n.tabMonster[i].x && m.y == n.tabMonster[i].y) {
                    rencontreDroite=true;
                } else if (m.x == n.tabMonster[i].x+58 && m.y == n.tabMonster[i].y) {
                    rencontreGauche=true;
                }
            }
        }

        // Vérification si colision avec un obstacle et supression du bloc de glace si rencontre avec celui-ci
        for (int i = 0; i < n.nbObstacle; i++)
        {
            if (n.tabObstacle[i].typeObstacle != DOWN && n.tabObstacle[i].typeObstacle != UP && n.tabObstacle[i].typeObstacle != RIGHT && n.tabObstacle[i].typeObstacle != LEFT)
            {
                if (m.y+53 == n.tabObstacle[i].y && m.x == n.tabObstacle[i].x) {
                    rencontreBas=true;
                    if (n.tabObstacle[i].typeObstacle == GLACE) {
                        n.tabObstacle[i].x=-100;
                        n.tabObstacle[i].y=-100;
                        SDL_Flip(screen);
                    }
                } else if (m.y == n.tabObstacle[i].y+53 && m.x == n.tabObstacle[i].x) {
                    rencontreHaut=true;
                    if (n.tabObstacle[i].typeObstacle == GLACE) {
                        n.tabObstacle[i].x=-100;
                        n.tabObstacle[i].y=-100;
                        SDL_Flip(screen);
                    }
                } else if (m.x+58 == n.tabObstacle[i].x && m.y == n.tabObstacle[i].y) {
                    rencontreDroite=true;
                    if (n.tabObstacle[i].typeObstacle == GLACE) {
                        n.tabObstacle[i].x=-100;
                        n.tabObstacle[i].y=-100;
                        SDL_Flip(screen);
                    }
                } else if (m.x == n.tabObstacle[i].x+58 && m.y == n.tabObstacle[i].y) {
                    rencontreGauche=true;
                    if (n.tabObstacle[i].typeObstacle == GLACE) {
                        n.tabObstacle[i].x=-100;
                        n.tabObstacle[i].y=-100;
                        SDL_Flip(screen);
                    }
                }
            } else {
                if (m.y == n.tabObstacle[i].y && m.x == n.tabObstacle[i].x) {
                    if (n.tabObstacle[i].typeObstacle == DOWN) {
                        direction = 2;
                    } else if (n.tabObstacle[i].typeObstacle == UP) {
                        direction = 4;
                    } else if (n.tabObstacle[i].typeObstacle == RIGHT) {
                        direction = 1;
                    } else if (n.tabObstacle[i].typeObstacle == LEFT) {
                        direction = 3;
                    }
                    rencontreDroite = false;
                    rencontreGauche = false;
                    rencontreHaut = false;
                    rencontreBas = false;
                }
            }
        }
        SDL_Rect typeMonstre;
        SDL_Rect lectureFond;
        typeMonstre=initTypeMonstre(n.tabMonster[indice],sprites);
        switch (direction)
        {
        case 1:
        {
            if (m.x != 350 && !rencontreDroite) {
                n.tabMonster[indice].x+=1;
                showMonster(n.tabMonster[indice].x,n.tabMonster[indice].y,sprites.source,screen,&typeMonstre);
                SDL_Flip(screen);
                SDL_Delay(2);
                initRect(lectureFond,n.tabMonster[indice].x,n.tabMonster[indice].y,54,52);
                applySurface(n.tabMonster[indice].x-1,n.tabMonster[indice].y,fondJeu,screen,&lectureFond);
                SDL_Flip(screen);
            } else if (m.x == 350) {
                initNiveaux(n,niveauCourant);
                rencontre=true;
            } else {
                rencontre=true;
            }
        } break;
        case 2:
        {
            if (m.y != 600 && !rencontreBas) {
                n.tabMonster[indice].y+=1;
                showMonster(n.tabMonster[indice].x,n.tabMonster[indice].y,sprites.source,screen,&typeMonstre);
                SDL_Flip(screen);
                SDL_Delay(2);
                initRect(lectureFond,n.tabMonster[indice].x,n.tabMonster[indice].y,54,52);
                applySurface(n.tabMonster[indice].x,n.tabMonster[indice].y-1,fondJeu,screen,&lectureFond);
                SDL_Flip(screen);
            } else if (m.y == 600) {
                initNiveaux(n,niveauCourant);
                rencontre=true;
            } else {
                rencontre=true;
            }
        } break;
        case 3:
        {
            if (m.x != -60 && !rencontreGauche) {
                n.tabMonster[indice].x-=1;
                showMonster(n.tabMonster[indice].x,n.tabMonster[indice].y,sprites.source,screen,&typeMonstre);
                SDL_Flip(screen);
                SDL_Delay(2);
                initRect(lectureFond,n.tabMonster[indice].x,n.tabMonster[indice].y,54,52);
                applySurface(n.tabMonster[indice].x+1,n.tabMonster[indice].y,fondJeu,screen,&lectureFond);
                SDL_Flip(screen);
            } else if (m.x == -60) {
                initNiveaux(n,niveauCourant);
                rencontre=true;
            } else {
                rencontre=true;
            }
        } break;
        case 4:
        {
            if (m.y != -90 && !rencontreHaut) {
                n.tabMonster[indice].y-=1;
                showMonster(n.tabMonster[indice].x,n.tabMonster[indice].y,sprites.source,screen,&typeMonstre);
                SDL_Flip(screen);
                SDL_Delay(2);
                initRect(lectureFond,n.tabMonster[indice].x,n.tabMonster[indice].y,54,52);
                applySurface(n.tabMonster[indice].x,n.tabMonster[indice].y+1,fondJeu,screen,&lectureFond);
                SDL_Flip(screen);
            } else if (m.y == -90) {
                initNiveaux(n,niveauCourant);
                rencontre=true;
            } else {
                rencontre=true;
            }
        } break;
        }
    }
}
