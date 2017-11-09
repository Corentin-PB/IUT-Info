#ifndef JSON_H
#define JSON_H

#include <fstream>

// csv vers json : colonnes dans le csv
const int JSON_NB_COLONNES = 4;
const int JSON_COL_X = 0;
const int JSON_COL_Y = 1;
const int JSON_COL_TEXT = 2;
const int JSON_COL_ICONE = 3;

void jsonInsererDebut(std::fstream &fichierJson);

void jsonInsererPoint(std::fstream &fichierJson, std::string x, std::string y,
					  std::string txt, std::string icone);

void jsonInsererFin(std::fstream &fichierJson);

#endif // JSON_H
