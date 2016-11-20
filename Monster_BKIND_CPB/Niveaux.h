// Niveaux.h

#include <SDL/SDL.h>

#include "Structures.h"
#include "Fonctions.h"

#ifndef NIVEAUX_H
#define NIVEAUX_H

using namespace std;

void initNiveaux(Niveau &n);

/*
////////////////////////////////////////////////
//
//  0/0  --  x/y  --  x/y  --  x/y  --  x/y
//
//  x/y  --  x/y  --  x/y  --  x/y  --  x/y
//
//  x/y  --  x/y  --  x/y  --  x/y  --  x/y
//
//  x/y  --  x/y  --  x/y  --  x/y  --  x/y
//
//  x/y  --  x/y  --  x/y  --  x/y  --  x/y
//
//  x/y  --  x/y  --  x/y  --  x/y  --  x/y
//
//  x/y  --  x/y  --  x/y  --  x/y  --  x/y
//
//  x/y  --  x/y  --  x/y  --  x/y  --  x/y
//
//  x/y  --  x/y  --  x/y  --  x/y  --  x/y
//
////////////////////////////////////////////////
*/

//defaut: x20 y36
//x +=58
//y +=48
//
//-9y MonsterSleep
//+5x Monster
//-3x -16y Biblio
//-3x -16y Glace
//+4x +4y Up
//+4x +4y Down
//+4x +4y Left
//+4x +4y Right

#endif // NIVEAUX_H
