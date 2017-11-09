/*
 * Fonctions utils pour la génération des fichiers JSON.
 */
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "json.h"
#include "chaines.h"
#include "csv.h"

using namespace std;

/* Debut du fichier GeoJSON */
void jsonInsererDebut(fstream &fichierJson) {
  fichierJson << "{\"type\":\"FeatureCollection\","
			  << "\"features\":[" << endl;
}

/* Ajoute un point dans le fichier GeoJSON */
void jsonInsererPoint(fstream &fichierJson, string x, string y,
					  string txt, string icone) {

  fichierJson << "{\"type\":\"Feature\"," << endl
			  << " \"properties\":" << endl
			  << " {\"icon\":\"" << icone << "\"," << endl
			  << "  \"description\":\"" << txt << "\"}," << endl
			  << " \"geometry\":" << endl
			  << " {\"type\":\"Point\"," << endl
			  << "  \"coordinates\":[" << x << "," << y << ",0]}"
			  << "}" << endl;
}

/* Fin du fichier GeoJSON */
void jsonInsererFin(fstream &fichierJson) {
  fichierJson << "]}";
}
