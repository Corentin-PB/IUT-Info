/*
 * Programme générant les requêtes SQL d'insertion des villes dans la base.
 */
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <string>
#include "utils/csv.h"
#include "utils/sql.h"

using namespace std;

/*
 * Traiter une ligne de villes.csv, c'est-à-dire un ville.
 */
void traiterVille(string ligne, string nomFichierCsv, fstream &fichierSql,
					 int colCle, int colNom) {
  // lecture de la ligne d'un ville dans le fichier csv
  int nbCol;
  TabLigne colonnes;
  const int nbColConfig = 2;
  coupeEnPlusieurs(ligne, CSV_SEP, nbCol, colonnes);
  if (nbCol!=nbColConfig) {
	cerr << "Une ligne du fichier " << nomFichierCsv;
	cerr << " ne contient pas le bon nombre de colonnes : " << endl;
	cerr << ligne << endl;
  }
  string cleVille = colonnes[colCle]; // stoi()
  string nomVille = colonnes[colNom];

  // ajout de la requete d'insertion du ville, dans le fichier SQL
  sqlInsererVille(fichierSql, cleVille, nomVille);
}

/*
 * Ouverture du fichier configVilles.csv, et pour chacune de ses lignes,
 * traitement du ville correspondant.
 */
void traiterVilles(string nomVillesCsv, string nomVillesSql,
					  int colCle, int colNom) {

    ifstream villesCsv;
    string ligne;

    // ouverture fichier csv en lecture
    villesCsv.open(nomVillesCsv.c_str(), ios::in);
    if (villesCsv.fail()) {
        cerr << "ouverture du fichier" << nomVillesCsv
			 << " impossible." << endl;
        exit(EXIT_FAILURE);
    }

	// ouverture fichier sql en ecriture
	fstream villesSql;
	villesSql.open(nomVillesSql.c_str(), ios::out);
	if (villesSql.fail()) {
	  cerr << "ouverture du fichier" << nomVillesSql
		   << " impossible." << endl;
	  exit(EXIT_FAILURE);
	}

	// suppression des anciens villes
	sqlSupprimerVilles(villesSql);

    // lecture des lignes du fichier des villes
	bool premiereLigne = true;
    while (getline(villesCsv, ligne)) {
	    if (premiereLigne) { // on ne traite pas la ligne des titres
		    premiereLigne = false;
		    continue;
	    }
		traiterVille(ligne, nomVillesCsv, villesSql, colCle, colNom);
    }
    villesCsv.close();
	villesSql.close();
}

/*
 * Analyse de la ligne de commande.
 */
void analyserLigneDeCommande(int argc, char *argv[],
							 string &cheminCsv, string &cheminSql,
							 int &colCle, int &colNom){

    if( argc != 5 ) {
	  cout << "Erreur : nombre d'arguments incorrect." << endl;
	  cout << "Usage : " << argv[0]
		   << " configVilles.csv villes.sql colCle colNom" << endl;
	  exit(-1);
	}
	cheminCsv = argv[1];
	cheminSql = argv[2];
	colCle = atoi(argv[3])-1;
	colNom = atoi(argv[4])-1;
}

/*
 * Procédure principale.
 */
int main( int argc, char* argv[] )
{
  string cheminCsv, cheminSql;
  int colCle, colNom;
  analyserLigneDeCommande(argc, argv, cheminCsv, cheminSql, colCle, colNom);
  traiterVilles(cheminCsv, cheminSql, colCle, colNom);
  return EXIT_SUCCESS;
}
