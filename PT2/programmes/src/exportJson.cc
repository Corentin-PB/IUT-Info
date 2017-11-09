/* Ce programme convertit des points extraits de la base de données, stockés
 * dans un fichier CSV, vers un format JSON utilisable pour les cartes Google.
 */
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <string>
#include "utils/chaines.h"
#include "utils/csv.h"
#include "utils/json.h"
#include "utils/sql.h"
using namespace std;

/*
 * Exporte tous les points d'une catégorie vers un fichier Json.
 */
void exportJsonPointsCategorie(string nomFichierCsv, string nomFichierJson,
							   string cheminIcones) {
    ifstream fichierCsv;
    fstream fichierJson;
    string ligne;

    // ouverture fichier csv en lecture
    fichierCsv.open(nomFichierCsv.c_str(), ios::in);
    if (fichierCsv.fail()) {
        cerr << "ouverture du fichier yep" << nomFichierCsv << " impossible."
			 << endl;
        exit(EXIT_FAILURE);
    }

    // ouverture fichier json en ecriture
    fichierJson.open(nomFichierJson.c_str(), ios::out);
    if (fichierJson.fail()) {
        cerr << "ouverture du fichier yo" << nomFichierJson << " impossible."
			 << endl;
        exit(EXIT_FAILURE);
    }
	jsonInsererDebut(fichierJson);

    // lecture des lignes du fichier csv des points extraits
	bool premiereLigne = true;
    while (getline(fichierCsv, ligne)) {
        int nbCol;
        TabLigne colonnes;
        coupeEnPlusieurs(ligne, CSV_SEP, nbCol, colonnes);
        if (nbCol<JSON_NB_COLONNES) {
            cerr << "Une ligne du fichier " << nomFichierCsv;
            cerr << " ne contient pas assez de colonnes : " << endl;
			cerr << ligne << endl;
        }
		if (!premiereLigne) {
		  fichierJson << "," << endl;
		} else {
		  premiereLigne = false;
		}
        jsonInsererPoint(fichierJson,
						 colonnes[JSON_COL_X], colonnes[JSON_COL_Y],
						 supprimeEspacesDroite(colonnes[JSON_COL_TEXT]),
						 cheminIcones +
						 supprimeEspacesDroite(colonnes[JSON_COL_ICONE]));
    }
	jsonInsererFin(fichierJson);
    fichierJson.close();
    fichierCsv.close();
}

/*
 * Export des points d'une catégorie au format Json, ville par ville.
 */
void exportJsonPointsCategorieVilles(const infoCategorie &categorie,
										string cheminSqlExtraction,
										string cheminJson,
										string cheminIcones,
										vector<infoVille> &villes) {
  for (infoVille ville : villes) {
	// pour chaque ville, on exporte ses points au format json
	string nomFichierCsv =
	  nomFichierCsvVille(cheminSqlExtraction, ville, categorie);
	string nomFichierJson = cheminJson
	  + int2string(ville.id) + "-" + categorie.id + ".json";
	exportJsonPointsCategorie(nomFichierCsv, nomFichierJson, cheminIcones);
  }
}

/*
 * Ouverture du fichier config.csv, et pour chacune de ses lignes,
 * traitement de la categorie correspondante.
 */
void traiterFichierConfig(string configCsv, string nomVillesCsv,
						  string cheminCsv, string cheminJson,
						  string cheminSqlExtraction, string cheminIcones) {

    ifstream configCsvFic;
    string ligne;

	// chargement des villes
	vector<infoVille> villes;
	chargerVilles(nomVillesCsv, villes);

    // ouverture fichier config.csv en lecture
    configCsvFic.open(configCsv.c_str(), ios::in);
    if (configCsvFic.fail()) {
        cerr << "ouverture du fichier qsqdqsq " << configCsv
			 << " impossible." << endl;
        exit(EXIT_FAILURE);
    }

    // lecture des lignes du fichier config.csv
	bool premiereLigne = true;
    while (getline(configCsvFic, ligne)) {
	    if (premiereLigne) { // on ne traite pas la ligne des titres
		    premiereLigne = false;
		    continue;
	    }
		infoCategorie categorie;
		bool ok = lireLigneConfigCsv(ligne, configCsv, categorie);
		if (!ok) {
		  return;
		}
		string nomFichierCsv  = cheminCsv  + categorie.id + ".sql.csv";
		string nomFichierJson = cheminJson + categorie.id + ".json";
		// export de tous les points de la catégorie
		exportJsonPointsCategorie(nomFichierCsv, nomFichierJson,
								  cheminIcones);
		// export de tous les points de la catégorie, pour chaque ville
		if (categorie.colVille != -1) {
		  exportJsonPointsCategorieVilles(categorie, cheminSqlExtraction,
											 cheminJson, cheminIcones,
											 villes);
		}
    }
    configCsvFic.close();
}

/*
 * Analyse de la ligne de commande.
 */
void analyserLigneDeCommande(int argc, char *argv[], string &configCsv,
               string &villesCsv,
							 string &cheminCsv,
							 string &cheminJson, string &cheminSqlExtraction,
							 string &cheminIcones) {

    if( argc != 7 ) {
	  cout << "Erreur : nombre d'arguments incorrect." << endl;
	  cout << "Usage : " << argv[0]
		   << " config.csv cheminCsv cheminJson cheminRequetesExtraction cheminIcones"
		   << endl;
	  exit(-1);
	}
	configCsv = argv[1];
	villesCsv = argv[2];
	cheminCsv = argv[3];
	cheminJson = argv[4];
	cheminSqlExtraction = argv[5];
	cheminIcones = argv[6];
}

/*
 * Procédure principale.
 */
int main( int argc, char* argv[] )
{
  string configCsv, cheminCsv, cheminJson, cheminSqlExtraction, villesCsv;
  string cheminIcones;
  analyserLigneDeCommande(argc, argv, configCsv,villesCsv, cheminCsv,
						  cheminJson, cheminSqlExtraction, cheminIcones);
  traiterFichierConfig(configCsv,villesCsv, cheminCsv, cheminJson,
					   cheminSqlExtraction, cheminIcones);
  return EXIT_SUCCESS;
}
