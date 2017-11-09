/*
* Fonctions utiles pour le traitement des fichiers CSV.
*/
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "csv.h"
#include "chaines.h"

using namespace std;

/* Coupe une chaine en deux morceaux séparés par un caractère donné.
* Renvoie vrai ssi le caractère a été trouvé.
*/
bool coupeEnDeux(string chaine, char sep, string &gauche, string &droite) {
  size_t trouve = chaine.find(sep);
  if (trouve != string::npos) {
    gauche = chaine.substr(0, trouve);
    droite = chaine.substr(trouve+1);
  }
  return (trouve!=string::npos);
}

/* Coupe une chaine en plusieurs morceaux séparés par un caractère donné.
* Le nombre de morceaux maximal est LONGUEUR_MAX_LIGNE_CSV.
*/
void coupeEnPlusieurs(string chaine, char sep,
  int &nbMorceaux, TabLigne &morceaux) {
    string gauche, droite;
    nbMorceaux = 0;
    while (coupeEnDeux(chaine, sep, gauche, droite) && nbMorceaux<MAX_LIGNE)
    {
      morceaux[nbMorceaux] = gauche;
      chaine = droite;
      nbMorceaux++;
    }
    if (nbMorceaux<MAX_LIGNE) {
      morceaux[nbMorceaux] = chaine;
      nbMorceaux++;
    }
  }

  /* Renvoie le plus grand indice de colonne parmi ceux de la catégorie. */
  int indiceColonneMax(infoCategorie categorie) {
    int maxIndice = max(categorie.colX, categorie.colY);
    maxIndice = max(maxIndice, categorie.colTxt);
    maxIndice = max(maxIndice, categorie.colCle);
    maxIndice = max(maxIndice, categorie.colVille);
    return maxIndice;
  }

  /* Lit une ligne du fichier config.csv et renseigne les infos de la catégorie
  * lue.
  * Renvoie vrai ssi la lecture s'est bien déroulée.
  */
  bool lireLigneConfigCsv(string ligne, string configCsv,
    infoCategorie &categorie) {
      int nbCol;
      TabLigne colonnes;
      coupeEnPlusieurs(ligne, CSV_SEP, nbCol, colonnes);
      if (nbCol!=NB_COL_CONFIG_CSV) {
        cerr << "Une ligne du fichier 1" << configCsv;
        cerr << " ne contient pas le bon nombre de colonnes : " << endl;
        cerr << ligne << endl;
        cerr << "Fichier ignoré." << endl;
        return false;
      }
      categorie.id = colonnes[0];
      categorie.nom = colonnes[2];
      categorie.date = colonnes[3];
      categorie.colX = atoi(colonnes[4].c_str())-1;
      categorie.colY = atoi(colonnes[5].c_str())-1;
      categorie.colTxt = atoi(colonnes[6].c_str())-1;
      categorie.colCle = atoi(colonnes[7].c_str())-1;
      categorie.colVille = -1; // -1 si car pas de ville
      categorie.cheminIcone = colonnes[8];
      categorie.identifiantVille = colonnes[1];
      return true;
    }

    bool lireLigneConfigBudgetCsv(std::string ligne, std::string configCsv,
      infoBudget &budget){

        int nbCol;
        TabLigne colonnes;
        coupeEnPlusieurs(ligne, CSV_SEP, nbCol, colonnes);
        if (nbCol!=10) {
          cerr << "Une ligne du fichier" << configCsv;
          cerr << " ne contient pas le bon nombre de colonnes : " << endl;
          cerr << ligne << endl;
          cerr << "Fichier ignoré." << endl;
          return false;
        }

        budget.id = colonnes[9];
        budget.annee = colonnes[1];
        budget.mode = atoi(colonnes[2].c_str());
        switch (budget.mode) {
          case 1:
          if(colonnes[4].find("r") != string::npos || colonnes[4].find("R") != string::npos ){
            budget.montantRecettes += atoi(colonnes[3].c_str());
          }else{
            budget.montantDepenses += atoi(colonnes[3].c_str());
          }
          break;
          case 2:
          budget.montantRecettes += atoi(colonnes[7].c_str());
          budget.montantDepenses += atoi(colonnes[8].c_str());
          break;
        }
        budget.identifiantVille = colonnes[0];
        return true;
      }

      /* Lit une ligne du fichier villes.csv et renseigne les infos du ville lu.
      * Renvoie vrai ssi la lecture s'est bien déroulée.
      */
      bool lireLigneVillesCsv(string ligne, string villesCsv,
        infoVille &ville) {
          int nbCol;
          TabLigne colonnes;
          coupeEnPlusieurs(ligne, CSV_SEP, nbCol, colonnes);
          if (nbCol!=NB_COL_VILLES_CSV) {
            cerr << "Une ligne du fichier" << villesCsv;
            cerr << " ne contient pas le bon nombre de colonnes : " << endl;
            cerr << ligne << endl;
            cerr << "Fichier ignoré." << endl;
            return false;
          }
          ville.id = atoi(colonnes[0].c_str());
          ville.nom = colonnes[1];
          ville.nom = supprimeEspacesDroite(ville.nom);
          return true;
        }

        /*
        * Lire villes.csv, et renvoyer l'ensemble des villes qu'il contient.
        */
        void chargerVilles(string nomVillesCsv, vector<infoVille> &villes) {
          ifstream villesCsv;
          string ligne;

          // on vide l'ensemble des villes
          villes.clear();

          // ouverture fichier csv en lecture
          villesCsv.open(nomVillesCsv.c_str(), ios::in);
          if (villesCsv.fail()) {
            cerr << "ouverture du fichier" << nomVillesCsv
            << " impossible." << endl;
            exit(EXIT_FAILURE);
          }

          // lecture des lignes du fichier de configuration
          while (getline(villesCsv, ligne)) {
            infoVille ville;
            bool ok = lireLigneVillesCsv(ligne, nomVillesCsv, ville);
            if (!ok) {
              return;
            }
            villes.push_back(ville);
          }
          // fermeture de villes.csv
          villesCsv.close();
        }


        void chargerBudgets(std::string budgetCsv,
          std::vector<infoBudget> &budgets){
            ifstream budgetsCsv;
            string ligne;

            // on vide l'ensemble des villes
            budgets.clear();

            // ouverture fichier csv en lecture
            budgetsCsv.open(budgetCsv.c_str(), ios::in);
            if (budgetsCsv.fail()) {
              cerr << "ouverture du fichier" << budgetCsv
              << " impossible." << endl;
              exit(EXIT_FAILURE);
            }
            bool premiereLigne = true;

            // lecture des lignes du fichier de configuration
            while (getline(budgetsCsv, ligne)) {
              if (premiereLigne) { // on ne traite pas la ligne des titres
                premiereLigne = false;
                continue;
              }
              infoBudget budget;
              bool ok = lireLigneConfigBudgetCsv(ligne, budgetCsv, budget);
              if (!ok) {
                return;
              }
              budgets.push_back(budget);
            }
            // fermeture de villes.csv
            budgetsCsv.close();
          }


          /*
          * Nom du fichier CSV contenant les points (extraits de la base) d'une
          * catégorie, pour un ville donné.
          */
          string nomFichierCsvVille(string cheminSqlExtraction,
            const infoVille &ville,
            const infoCategorie &categorie) {
              return cheminSqlExtraction + "villes/categories/csv/"
              + int2string(ville.id) + "-" + categorie.id + ".sql.csv";
            }
