// Score.cc

#include <iostream>
#include <cstdlib>

#include "Score.h"

using namespace std;

void enregistreScore(string nomFic, Niveau n)
{
    fstream f;

    f.open(nomFic.c_str(), ios::out);
    if( f.fail() )
    {
        cerr << "ouverture en ecriture impossible" << endl;
        exit(EXIT_FAILURE);
    }
    for( int i = 0 ; i < NB_NIVEAU ; i++ )
    {
        f << "Niveau " << i+1 << " = " << n.score[i] << endl;
    }
    f.close();
}

