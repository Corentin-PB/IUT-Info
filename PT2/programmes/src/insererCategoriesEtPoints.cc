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
void insererCategorie(string csv, string sql, infoCategorie categorie, string Ville){
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

  // supprimer les (anciens) points de cette catégorie
  sqlSupprimerPointsCategorie(fichierSql, categorie.nom);
  // supprimer l'(éventuelle) ancienne catégorie dans la base
  sqlSupprimerCategorie(fichierSql, categorie.nom);
  // insérer la nouvelle catégorie dans la base
  sqlInsererCategorie(fichierSql, categorie.nom,
    categorie.cheminIcone, categorie.date, Ville);

    // lecture des lignes du fichier csv, pour insertion des points
    bool premiereLigne = true;
    while (getline(fichierCsv, ligne)) {
      if (premiereLigne) { // on ne traite pas la ligne des titres
        premiereLigne = false;
        continue;
      }
      int nbCol;
      TabLigne colonnes;
      coupeEnPlusieurs(ligne, CSV_SEP, nbCol, colonnes);
      if (nbCol<=indiceColonneMax(categorie)) {
        cerr << "Une ligne du fichier " << csv;
        cerr << " ne contient pas assez de colonnes : " << endl;
        cerr << ligne << endl;
      }
      /*  if (avecVille && colonnes[categorie.colVille]!="") {
      ville = colonnes[categorie.colVille];
    }*/
    // insertion d'un point
    sqlInsererPoint(fichierSql, categorie.nom,
      colonnes[categorie.colX], colonnes[categorie.colY],
      colonnes[categorie.colTxt], colonnes[categorie.colCle],
      avecVille,"");
    }
    fichierSql.close();
    fichierCsv.close();
  }

  /*
  * Analyse de la ligne de commande.
  */
  void analyserLigneDeCommande(int argc, char *argv[], string &configCsv,
    string &cheminCsv, string &cheminSql) {

      if( argc != 4 ) {
        cout << "Erreur : nombre d'arguments incorrect." << endl;
        cout << "Usage : " << argv[0]
        << " config.csv cheminCsv cheminSql" << endl;
        exit(-1);
      }
      configCsv = argv[1];
      cheminCsv = argv[2];
      cheminSql = argv[3];
    }

    /*
    * Ouverture du fichier config.csv, et pour chacune de ses lignes,
    * traitement de la categorie correspondante.
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
          if(cheminCsv.find("Bordeaux") != string::npos){
            i++;
            if(i<13){
              string fichierCsv = cheminCsv + categorie.id + ".csv";
              string fichierSql = cheminSql + categorie.id + ".sql";
              insererCategorie(fichierCsv, fichierSql, categorie,"Bordeaux");
            }
          }
          else if(cheminCsv.find("Nantes") != string::npos){
            i++;
            if(i>12 && i<20){
              string fichierCsv = cheminCsv + categorie.id + ".csv";
              string fichierSql = cheminSql + categorie.id + ".sql";
              insererCategorie(fichierCsv, fichierSql, categorie,"Nantes");
            }

          }
          else if(cheminCsv.find("Toulouse") != string::npos){
            i++;
            if(i>19){
              string fichierCsv = cheminCsv + categorie.id + ".csv";
              string fichierSql = cheminSql + categorie.id + ".sql";
              insererCategorie(fichierCsv, fichierSql, categorie,"Toulouse");
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
