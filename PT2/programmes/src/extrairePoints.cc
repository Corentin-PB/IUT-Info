/*
 * Programme générant les requêtes SQL d'extraction des points de la base,
 * par catégorie, et par catégorie + ville.
 */
#include <cstdlib>
#include <iostream>
#include <string>
#include "utils/csv.h"
#include "utils/sql.h"
using namespace std;

/* Extraction des informations d'une catégorie, et de ses points,
 * pour un ville donné : on génère les requêtes SQL SELECT correspondantes.
 */
void extraireCategorieVille(infoCategorie categorie, infoVille ville,
							   string nomFichierSql) {
    fstream fichierSql;

    // ouverture fichier sql en ecriture
    fichierSql.open(nomFichierSql.c_str(), ios::out);
    if (fichierSql.fail()) {
        cerr << "ouverture du fichier" << nomFichierSql << " impossible."
			 << endl;
        exit(EXIT_FAILURE);
    }

	// extraire les points pour cette catégorie, dans ce ville
	sqlExtrairePointsCategorieVille(categorie, ville, fichierSql);

    fichierSql.close();
}

/* Extraction des informations d'une catégorie, et de ses points :
 * on génère les requêtes SQL SELECT correspondantes.
 */
void extraireCategorie(infoCategorie categorie, string cheminSql,
                      vector<infoVille>villes) {
    fstream fichierSql;
	string nomFichierSql = cheminSql + categorie.id + ".sql";

	// ouverture fichier sql en ecriture
    fichierSql.open(nomFichierSql.c_str(), ios::out);
    if (fichierSql.fail()) {
        cerr << "ouverture du fichier" << nomFichierSql << " impossible."
			 << endl;
        exit(EXIT_FAILURE);
    }

	// extraire les points pour cette catégorie
	sqlExtrairePointsCategorie(categorie, fichierSql);

	// si les villes sont renseignés pour cette catégorie, on extrait aussi
	// pour chaque ville indépendamment (pour villes.html)
	if (categorie.colVille != -1) {
	  for (infoVille ville : villes) {
		string nomFichier =
		  nomFichierSqlVille(cheminSql, ville, categorie);
		extraireCategorieVille(categorie, ville, nomFichier);
	  }
	}

    fichierSql.close();
}

/*
 * Ouverture du fichier config.csv, et pour chacune de ses lignes,
 * traitement de la categorie correspondante.
 */
void traiterFichierConfig(string configCsv, string cheminSql,
                          vector<infoVille>villes) {

    ifstream configCsvFic;
    string ligne;

    // ouverture fichier csv en lecture
    configCsvFic.open(configCsv.c_str(), ios::in);
    if (configCsvFic.fail()) {
        cerr << "ouverture du fichier" << configCsv
			 << " impossible." << endl;
        exit(EXIT_FAILURE);
    }

    // lecture des lignes du fichier de configuration
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
		extraireCategorie(categorie, cheminSql, villes);
    }
    configCsvFic.close();
}

/*
 * Analyse de la ligne de commande.
 */
void analyserLigneDeCommande(int argc, char *argv[], string &configCsv,
							 string &villesCsv,string &cheminSql) {

    if( argc != 4 ) {
	  cout << "Erreur : nombre d'arguments incorrect." << endl;
	  cout << "Usage : " << argv[0]
		   << " config.csv villes.csv cheminSql" << endl;
	  exit(-1);
	}
	configCsv = argv[1];
  villesCsv = argv[2];
	cheminSql = argv[3];
}

/*
 * Procédure principale.
 */
int main( int argc, char* argv[] )
{
  string configCsv,villesCsv, cheminSql;
  vector<infoVille> villes;
  analyserLigneDeCommande(argc, argv, configCsv,villesCsv, cheminSql);
  chargerVilles(villesCsv, villes);
  traiterFichierConfig(configCsv, cheminSql,villes);
  return EXIT_SUCCESS;
}
