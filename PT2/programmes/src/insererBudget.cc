/*
* Programme générant les requêtes SQL d'insertion des catégories et
* de leurs points dans la base.
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "utils/csv.h"
#include "utils/sql.h"
using namespace std;

/* Insertion d'une catégorie dans la base, avec les points de cette catégorie,
* initialement stockés dans un fichier csv.
*/
void insererbudget(string csv, string sql, infoBudget budget, string Ville){
  ifstream fichierCsv;
  fstream fichierSql;
  string ligne;
  bool avecVille = false; // On a supprimer les ville, on initialise donc à faux

  // ouverture fichier csv en lecture
  fichierCsv.open(csv.c_str(), ios::in);
  if (fichierCsv.fail()) {
    cerr << "ouverture du fichier " << csv << " impossible." << endl;
    exit(EXIT_FAILURE);
  }

  // ouverture fichier sql en ecriture
  fichierSql.open(sql.c_str(), ios::out);
  if (fichierSql.fail()) {
    cerr << "ouverture du fichier " << sql << " impossible." << endl;
    exit(EXIT_FAILURE);
  }
  // insérer le nouveau budget dans la base
  sqlInsererbudget(fichierSql, budget.montantRecettes, budget.montantDepenses, budget.annee, Ville);
  budget.montantRecettes=0;
  budget.montantDepenses=0;
}
  /*
  * Analyse de la ligne de commande.
  */
  void analyserLigneDeCommande(int argc, char *argv[], string &configCsv,
    string &cheminCsv, string &cheminSql) {

      if( argc != 4 ) {
        cout << "Erreur : nombre d'arguments incorrect." << endl;
        cout << "Usage : " << argv[0]
        << " configBudget.csv cheminCsv cheminSql" << endl;
        exit(-1);
      }
      configCsv = argv[1];
      cheminCsv = argv[2];
      cheminSql = argv[3];
    }

    /*
    * Ouverture du fichier config.csv, et pour chacune de ses lignes,
    * traitement de la budget correspondante.
    */
    void traiterFichierConfig(string configCsv,
      string cheminCsv, string cheminSql) {

        ifstream configCsvFic;
        string ligne;

        int i=0;

        // ouverture fichier csv en lecture
        configCsvFic.open(configCsv.c_str(), ios::in);
        if (configCsvFic.fail()) {
          cerr << "ouverture du fichier " << configCsv
          << " impossible." << endl;
          exit(EXIT_FAILURE);
        }
        infoBudget budget;

        // lecture des lignes du fichier de configuration
        bool premiereLigne = true;
        while (getline(configCsvFic, ligne)) {
          if (premiereLigne) { // on ne traite pas la ligne des titres
            premiereLigne = false;
            continue;
          }

          bool ok = lireLigneConfigBudgetCsv(ligne, configCsv, budget);
          if (!ok) {
            return;
          }
          if(cheminCsv.find("Bordeaux") != string::npos){
            i++;
            if(i<5){
              string fichierCsv = cheminCsv + budget.id + ".csv";
              string fichierSql = cheminSql + budget.id + ".sql";
              insererbudget(fichierCsv, fichierSql, budget,"Bordeaux");
            }

          }
          else if(cheminCsv.find("Nantes") != string::npos){
            i++;
            if(i>4 && i<12){
              string fichierCsv = cheminCsv + budget.id + ".csv";
              string fichierSql = cheminSql + budget.id + ".sql";
              insererbudget(fichierCsv, fichierSql, budget,"Nantes");
            }

          }
          else if(cheminCsv.find("Toulouse") != string::npos){
            i++;
            if(i>11){
              string fichierCsv = cheminCsv + budget.id + ".csv";
              string fichierSql = cheminSql + budget.id + ".sql";
              insererbudget(fichierCsv, fichierSql, budget,"Toulouse");
            }
          }
        }
        configCsvFic.close();
      }

      /*
      * Procédure principale.
      */
      int main( int argc, char* argv[] )
      {
        string configCsv, cheminCsv, cheminSql;
        analyserLigneDeCommande(argc, argv, configCsv, cheminCsv, cheminSql);
        traiterFichierConfig(configCsv, cheminCsv, cheminSql);
        return EXIT_SUCCESS;
      }
