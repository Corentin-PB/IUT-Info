#ifndef CSV_H
#define CSV_H

#include <array>
#include <string>
#include <vector>

const int MAX_LIGNE = 50; // nombre max de cellules d'une ligne csv
const char CSV_SEP = ';'; // separateur du fichier csv
const int NB_COL_CONFIG_CSV = 9; // nombre de colonnes dans config.csv
const int NB_COL_CATEGORIE_CSV = 4; // nombre de colonnes dans un categorie.csv
const int NB_COL_VILLES_CSV = 2; // nombre de colonnes dans villes.csv
const int NB_COL_CONFIG_BUDGETS_CSV = 10; // nombre de colonnes dans configBudgets.csv

// tableau stockant les cellules d'une ligne d'un fichier CSV
using TabLigne = std::array<std::string,MAX_LIGNE>;

// structure stockant les informations d'une categorie (= ligne de config.csv)
struct infoCategorie {
  std::string id;
  std::string nom;
  std::string date;
  int colX;
  int colY;
  int colTxt;
  int colCle;
  int colVille;
  std::string cheminIcone;
  std::string identifiantVille;
};

// structure stockant les informations d'un budget (= ligne de config.csv)
struct infoBudget {
  std::string annee;
  std::string id;
  int mode;
  int montantRecettes;
  int montantDepenses;
  std::string identifiantVille;
};

// structure stockant les informations d'un ville (= ligne de villes.csv)
struct infoVille {
  int id;
  std::string nom;
};

bool coupeEnDeux(std::string chaine, char sep, std::string &gauche, std::string &droite);

void coupeEnPlusieurs(std::string chaine, char sep,
                      int &nbMorceaux, TabLigne &morceaux);

std::string changerExtension(std::string csv, std::string extension);

int indiceColonneMax(infoCategorie categorie);

bool lireLigneConfigCsv(std::string ligne, std::string configCsv,
						infoCategorie &categorie);

bool lireLigneConfigBudgetCsv(std::string ligne, std::string configCsv,
            infoBudget &budget);

bool lireLigneVillesCsv(std::string ligne, std::string villesCsv,
						   infoVille &ville);

void chargerVilles(std::string nomVillesCsv,
					  std::vector<infoVille> &villes);

void chargerBudgets(std::string budgetCsv,
           std::vector<infoBudget> &budgets);

std::string nomFichierCsvVille(std::string cheminSqlExtraction,
								  const infoVille &ville,
								  const infoCategorie &categorie);
#endif // CSV_H
