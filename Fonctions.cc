// Fonctions.cc

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

#include "Fonctions.h"

using namespace std;

void initRect(SDL_Rect &Rect, int a, int b, int c, int d)
{
    Rect.x=a;
    Rect.y=b;
    Rect.w=c;
    Rect.h=d;
}

void initBouton(Bouton &b, int x, int y, int w, int h)
{
    b.x=x;
    b.y=y;
    b.w=w;
    b.h=h;
}

// -- loadImage ---------------------------------
// chargement d'une image
// ----------------------------------------------
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

// -- applySurface ------------------------------
// c'est le copier-coller d'une surface sur une
// autre : on colle le rectangle "clip" de "source"
// sur "destination" à partir de "x,y"
// ----------------------------------------------
void
applySurface(int x, int y, SDL_Surface* source,
             SDL_Surface* destination, SDL_Rect* clip)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}

// -- showMessageScreen ----------------------
// ici nous sommes confrontés à un petit problème.
// La fonction "TTF_RenderText_Solid" est sensée
// afficher un message. Mais celui-ci ne doit pas
// comporter d'espaces, sinon le programme plante.
// Nous allons donc analyser la string passée en
// paramètre et faire l'affichage mot à mot...
// (x,y) sont les coordonnées du message
// ----------------------------------------------
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

// -- loadImageWithColorKey ---------------------
// chargement d'une image
// * paramètres entrées :
// - "filename" : nom de l'image
// - "r,g,b"    : couleur de la ColorKey; cette
//   couleur devient transparente !
// * paramètre de sortie : SDL_Surface contenant
//   l'image.
// ----------------------------------------------
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

void
showMonster(int x, int y, SDL_Surface* source,
            SDL_Surface* destination, SDL_Rect* clip)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}

void
showObstacle(int x, int y, SDL_Surface* source,
             SDL_Surface* destination, SDL_Rect* clip)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}

Monster initMonster(int x, int y, enumMonster typeMonster) {
    Monster m;
    m.x=x;
    m.y=y;
    m.w=54;
    m.h=52;
    m.typeMonster=typeMonster;
    return m;
}

void initObstacle (Obstacle &o, int x, int y, enumObstacle typeObstacle) {
    o.x=x;
    o.y=y;
    o.w=54;
    o.h=52;
    o.typeObstacle = typeObstacle;
}

SDL_Rect initTypeMonstre(Monster m, Sprite sprites) {
    SDL_Rect lecture;
    if (m.typeMonster==VIVANT) {
        lecture=sprites.lecture_Monster;
    } else if (m.typeMonster==DORMEUR) {
        lecture=sprites.lecture_MonsterSleep;
    } else if (m.typeMonster==MORT) {
        lecture=sprites.lecture_Rien;
    }
    return lecture;
}

void initNiveaux(Niveau &n, int niv)
{
    n.nbNiveau=2;
    switch (niv) {
    case 1:
    {
        n.tabMonster[0] = initMonster(75,83,VIVANT);
        n.tabMonster[1] = initMonster(17,295,DORMEUR);
        n.tabMonster[2] = initMonster(249,295,DORMEUR);
        n.nbMonster = 3;
        initObstacle(n.tabObstacle[0],75,348,BIBLIO);
        n.nbObstacle =3;
    } break;
    case 2:
    {
        n.tabMonster[0] = initMonster(75,83,VIVANT);
        n.tabMonster[1] = initMonster(17,295,DORMEUR);
        n.tabMonster[2] = initMonster(249,295,DORMEUR);
        n.nbMonster = 3;
        initObstacle(n.tabObstacle[0],75,348,BIBLIO);
        initObstacle(n.tabObstacle[1],249,30,GLACE);
        initObstacle(n.tabObstacle[2],75,30,RIGHT);
        n.nbObstacle =3;
    } break;
    }
}

void moveMonster(Monster &m, int &direction, Niveau &n, SDL_Surface *screen, int indice, int &niveauCourant) {
    bool rencontre =false,rencontreBas = false, rencontreHaut = false, rencontreDroite = false, rencontreGauche = false;
    while (!rencontre)
    {
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

        switch (direction)
        {
        case 1:
        {
            if (m.x != 350 && !rencontreDroite) {
                m.x+=1;
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
                m.y+=1;
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
                m.x-=1;
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
                m.y-=1;
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

