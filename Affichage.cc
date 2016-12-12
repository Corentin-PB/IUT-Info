// Affichage.cc

#include <iostream>
#include <cstdlib>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <sstream>
#include <ctime>

#include "Affichage.h"

using namespace std;

/****************** Nom de la fonction **********************
* load_image                                                *
******************** Auteur , Dates *************************
* Nom/Date : Inconnu                                        *
********************* Description ***************************
* Permet de copier une image sur une SDL_Surface            *
*********************** Entrées *****************************
* Le nom du fichier                                         *
*********************** Sorties *****************************
* Renvoie la SDL_Surface                                    *
************************************************************/
SDL_Surface *
load_image( string filename )
{
    //Temporary storage for the image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;
    //Load the image
    loadedImage = IMG_Load( filename.c_str() );
    //If nothing went wrong in loading the image
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );
    }
    //Return the optimized image
    return optimizedImage;
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/****************** Nom de la fonction **********************
* applySurface                                              *
******************** Auteur , Dates *************************
* Nom/Date : Inconnu                                        *
********************* Description ***************************
* C'est le copier-coller d'une surface sur une autre : on   *
* colle le rectangle "clip" de "source" sur "destination"   *
* à partir de "x,y" des paramètres                          *
*********************** Entrées *****************************
* Les coordonnées de la surface, la surface source et la    *
* surface de destionation ainsi que le rectangle de lecture *
*********************** Sorties *****************************
* Renvoie la surface modifiée en référence                  *
************************************************************/
void
applySurface(int x, int y, SDL_Surface* source,
             SDL_Surface* destination, SDL_Rect* clip)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/****************** Nom de la fonction **********************
* showMessageScreen                                         *
******************** Auteur , Dates *************************
* Nom/Date : Inconnu                                        *
********************* Description ***************************
* Analyse la string passée en paramètre et fait l'affichage *
* mot à mot du message sur l'écran                          *
*********************** Entrées *****************************
* Le message, les coordonnées du message, la police de      *
* caractère, la taille de la police, la couleur du texte et *
* la surface sur laquelle afficher le message               *
*********************** Sorties *****************************
* Renvoie la surface modifiée en référence                  *
************************************************************/
void
showMessageScreen(string message,int x,int y,
                  TTF_Font *font,int fontSize,SDL_Color textColor,SDL_Surface* &screen)
{
    string mot="";
    string space=" ";
    int i=0,j;
    SDL_Surface *mes=NULL;

    j = message.find(space);
    while( j != string::npos )
    {
        mot=message.substr(i,j-i);
        if(mot != "")
        {
            mes=TTF_RenderText_Solid(font,mot.c_str(),textColor);
            applySurface(x,y,mes,screen,NULL);
            x+=mes->w;
            SDL_FreeSurface(mes);
        }
        x+=fontSize;
        i=j+1;
        j = message.find(space,i);
    }

    mot=message.substr(i);
    mes=TTF_RenderText_Solid(font,mot.c_str(),textColor);
    applySurface(x,y,mes,screen,NULL);
    SDL_FreeSurface(mes);
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/****************** Nom de la fonction **********************
* loadImageWithColorKey                                     *
******************** Auteur , Dates *************************
* Nom/Date : Inconnu                                        *
********************* Description ***************************
* Même chose que loadImage mais permet la disparition de    *
* certains pixels d'une même couleur                        *
*********************** Entrées *****************************
* Le nom du fichier, les entiers de chaque couleur du pixel *
* à supprimer                                               *
*********************** Sorties *****************************
* Renvoie la surface                                        *
************************************************************/
SDL_Surface *
loadImageWithColorKey(string filename, int r, int g, int b)
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );

        //If the image was optimized just fine
        if( optimizedImage != NULL )
        {
            //Map the color key
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, r, g, b );

            //Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
        }
    }
    //Return the optimized image
    return optimizedImage;
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/****************** Nom de la fonction **********************
* showMonster                                               *
******************** Auteur , Dates *************************
* Nom/Date : Auteurs multiples                              *
********************* Description ***************************
* Même chose que applySurface mais changement de nom pour   *
* plus de simplicité lors de la lecture du code             *
*********************** Entrées *****************************
* Les coordonnées de la surface, la surface source et la    *
* surface de destionation ainsi que le rectangle de lecture *
*********************** Sorties *****************************
* Renvoie la surface modifiée en référence                  *
************************************************************/
void
showMonster(int x, int y, SDL_Surface* source,
            SDL_Surface* destination, SDL_Rect* clip)
{
    applySurface(x,y,source,destination,clip);
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/****************** Nom de la fonction **********************
* showObstacle                                               *
******************** Auteur , Dates *************************
* Nom/Date : Auteurs multiples                              *
********************* Description ***************************
* Même chose que applySurface mais changement de nom pour   *
* plus de simplicité lors de la lecture du code             *
*********************** Entrées *****************************
* Les coordonnées de la surface, la surface source et la    *
* surface de destionation ainsi que le rectangle de lecture *
*********************** Sorties *****************************
* Renvoie la surface modifiée en référence                  *
************************************************************/
void
showObstacle(int x, int y, SDL_Surface* source,
             SDL_Surface* destination, SDL_Rect* clip)
{
    applySurface(x,y,source,destination,clip);
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/****************** Nom de la fonction **********************
* Affichage                                                 *
******************** Auteur , Dates *************************
* Nom/Date : Auteurs multiples                              *
********************* Description ***************************
* Fonction d'affichage principal, fait appel aux autres     *
* fonctions d'affichage afin que le programme tourne        *
* correctement                                              *
*********************** Entrées *****************************
* les booléens des différents menus du jeu ainsi que ceux   *
* en rapport avec les niveaux et les surfaces utilisées pour*
* l'affichage                                               *
*********************** Sorties *****************************
* Renvoie en paramètre certains booléens modifiés et        *
* le niveau                                                 *
************************************************************/
void Affichage(bool menuPrin, bool menuJeu, bool menuTuto, int &niveauCourant, bool &nivTermine, bool jeuTermine,
               SDL_Surface *menu, SDL_Surface *screen, SDL_Surface *fondJeu, SDL_Surface *tuto, SDL_Surface *nivTerm, SDL_Rect lectureFen, SDL_Surface *jeuTerm, Sprite sprites, Niveau &n, Bouton boutonQuitter, SDL_Surface *boutonQuitterDefaut, SDL_Rect lectureQuitter)
{
    //Affichage du menu principal
    if (menuPrin)
    {
        applySurface(0,0,menu,screen,&lectureFen);
        applySurface(boutonQuitter.x-2,boutonQuitter.y+3,boutonQuitterDefaut,screen,&lectureQuitter);
    }

    //Affichage du menu du tutoriel
    if (menuTuto)
    {
        applySurface(0,0,tuto,screen,&lectureFen);
    }

//    //Affichage du menu de l'éditeur de niveau
//    if (menuEditeur)
//    {

//    }

    //Affichage du menu du jeu
    if (menuJeu)
    {
        if (nivTermine) {
            if (jeuTermine) {
                applySurface(0,0,jeuTerm,screen,&lectureFen);
                SDL_Flip(screen);
                SDL_Delay(1500);
                SDL_FreeSurface(screen);
                SDL_FreeSurface(menu);
                SDL_FreeSurface(fondJeu);
                SDL_FreeSurface(sprites.source);
                SDL_FreeSurface(nivTerm);
                SDL_FreeSurface(jeuTerm);
                SDL_Quit();
            } else {
                applySurface(0,0,nivTerm,screen,&lectureFen);
                SDL_Flip(screen);
                SDL_Delay(1000);
            }
            niveauCourant++;
            initNiveaux(n,niveauCourant);
            nivTermine = false;
        }
        applySurface(0,0,fondJeu,screen,&lectureFen);

        // Ce SDL_Rect typeMonstre permet de mettre à jour le type du monstre (dormeur, vivant, etc...) afin que l'affichage corresponde au statut du monstre
        SDL_Rect typeMonstre;

        // Affichage des monstres et obstacle en fonction du niveau
        switch (niveauCourant) {
        case 1:
        {
            showObstacle(n.tabObstacle[0].x,n.tabObstacle[0].y,sprites.source,screen,&sprites.lecture_Biblio);
            for (int i = 0; i < n.nbMonster; i++) {
                typeMonstre=initTypeMonstre(n.tabMonster[i],sprites);
                showMonster(n.tabMonster[i].x,n.tabMonster[i].y,sprites.source,screen,&typeMonstre);
            }
        } break;
        case 2:
        {
            showObstacle(n.tabObstacle[0].x,n.tabObstacle[0].y,sprites.source,screen,&sprites.lecture_Biblio);
            showObstacle(n.tabObstacle[1].x,n.tabObstacle[1].y,sprites.source,screen,&sprites.lecture_Biblio);
            showObstacle(n.tabObstacle[2].x,n.tabObstacle[2].y,sprites.source,screen,&sprites.lecture_Down);
            for (int i = 0; i < n.nbMonster; i++) {
                typeMonstre=initTypeMonstre(n.tabMonster[i],sprites);
                showMonster(n.tabMonster[i].x,n.tabMonster[i].y,sprites.source,screen,&typeMonstre);
            }
        } break;
        case 3:
        {
            showObstacle(n.tabObstacle[0].x,n.tabObstacle[0].y,sprites.source,screen,&sprites.lecture_Biblio);
            showObstacle(n.tabObstacle[1].x,n.tabObstacle[1].y,sprites.source,screen,&sprites.lecture_Down);
            showObstacle(n.tabObstacle[2].x,n.tabObstacle[2].y,sprites.source,screen,&sprites.lecture_Right);
            showObstacle(n.tabObstacle[3].x,n.tabObstacle[3].y,sprites.source,screen,&sprites.lecture_Up);
            showObstacle(n.tabObstacle[4].x,n.tabObstacle[4].y,sprites.source,screen,&sprites.lecture_Glace);
            showObstacle(n.tabObstacle[5].x,n.tabObstacle[5].y,sprites.source,screen,&sprites.lecture_Biblio);
            showObstacle(n.tabObstacle[6].x,n.tabObstacle[6].y,sprites.source,screen,&sprites.lecture_Biblio);
            showObstacle(n.tabObstacle[7].x,n.tabObstacle[7].y,sprites.source,screen,&sprites.lecture_Biblio);
            showObstacle(n.tabObstacle[0].x,n.tabObstacle[0].y,sprites.source,screen,&sprites.lecture_Biblio);
            for (int i = 0; i < n.nbMonster; i++) {
                typeMonstre=initTypeMonstre(n.tabMonster[i],sprites);
                showMonster(n.tabMonster[i].x,n.tabMonster[i].y,sprites.source,screen,&typeMonstre);
            }

        } break;
        }
    }
}
