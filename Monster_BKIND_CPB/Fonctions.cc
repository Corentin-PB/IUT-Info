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

/*Monst initMonster(int a, int b, int c, int d)
{
    Monst Monster;
    Monster.x=x;
    Monster.y=y;
}*/

/*// -- Collision ----------------------
// Fonction permettant de gérer les collisions
// de la balle et des autres objets rencontrés
// sur le chemin de la balle (direction opposée
// en cas de collision.
// ----------------------------------------------
bool
collision(SDL_Rect b ,Objet x)
{
    int leftBall, leftPx;
    int rightBall, rightPx;
    int topBall, topPx;
    int bottomBall, bottomPx;

    leftBall = b.x;
    rightBall = b.x + b.w;
    topBall = b.y;
    bottomBall = b.y + b.h;

    leftPx = x.x;
    rightPx = x.x + x.w;
    topPx = x.y;
    bottomPx = x.y + x.h;

    if(bottomBall <= topPx)
        return false;
    if(topBall >= bottomPx)
        return false;
    if(rightBall <= leftPx)
        return false;
    if(leftBall >= rightPx)
        return false;

    return true;
}*/


/*// -- moveBall ----------------------
// Fonction permettant de définir les mouvements
// de la balle quand elle se déplace et quand elle
// rencontre un obstacle.
// ----------------------------------------------
void
moveBall(ball &b, Objet player1, Objet player2)
{
    SDL_Rect tmp;

    b.x+=b.mvt_x;

    tmp.x=b.x-TAILLE/2;
    tmp.y=b.y-TAILLE/2;
    tmp.h=TAILLE;
    tmp.w=TAILLE;

    // Correction Mouvement Horizontal
    if((b.x+TAILLE/2>SCREEN_WIDTH) || (b.x-TAILLE/2<0) || collision(tmp,player1) || collision(tmp,player2))
    {
        b.x-=b.mvt_x;
        b.mvt_x*=-1;
    }


    b.y+=b.mvt_y;

    tmp.x=b.x-TAILLE/2;
    tmp.y=b.y-TAILLE/2;

    // Correction Mouvement Vertical
    if((b.y+TAILLE/2>SCREEN_HEIGHT) || (b.y-TAILLE/2<25) || collision(tmp,player1) || collision(tmp,player2))
    {
        b.y-=b.mvt_y;
        b.mvt_y*=-1;
    }
}*/


