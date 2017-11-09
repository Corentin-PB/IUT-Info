/*
* Fonctions utiles pour la génération de requêtes SQL.
*/
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "sql.h"
#include "csv.h"
#include "chaines.h"

using namespace std;

/* Remplace le séparateur virgule par un point. */
string virgulePoint(string s) {
  string gauche, droite;
  bool ok = coupeEnDeux(s, ',', gauche, droite);
  if (!ok) {
    cerr << "Mauvais format numérique pour " << s << endl;
  }
  return gauche + "." + droite;
}

/* echappe (double) les guillemets simples dans une chaine de caracteres */
string echapperQuote(string s) {
  string chaine = s;
  size_t trouve = chaine.find("'");
  while (trouve != string::npos) {
    chaine.replace(trouve,1,"''");
    trouve = chaine.find("'", trouve+2);
  }
  return chaine;
}

/* Ajoute la requete SQL d'insertion d'un ville dans le fichier SQL */
void sqlInsererVille(fstream &fichierSql,
  string cleVille, string nomVille) {
    fichierSql << "INSERT INTO "
    << "VILLES(Nom_Ville) "
    << "VALUES("
    << "N'" << echapperQuote(nomVille) << "')"
    << endl << endl;
  }

  /* Ajoute la requête SQL de suppression de tous les villes dans
  * le fichier SQL.
  */
  void sqlSupprimerVilles(fstream &fichierSql) {
    fichierSql << "DELETE FROM POINTS" << endl << endl;
    fichierSql << "DELETE FROM BUDGETS" << endl << endl;
    fichierSql << "DELETE FROM CATEGORIES" << endl << endl;
    fichierSql << "DELETE FROM VILLES" << endl << endl;
  }

  void sqlSupprimerbudget(fstream &fichierSql, infoBudget budget){
    fichierSql << "DELETE FROM BUDGETS "
    << "where Montant_Recettes ='" << budget.montantRecettes <<"'"
    << "AND where Montant_Depenses ='" << budget.montantDepenses <<"'"
    << endl << endl;
  }

  /* Ajoute la requete SQL d'insertion d'une categorie dans le fichier SQL */
  void sqlInsererCategorie(fstream &fichierSql, string nomCategorie,
    string cheminIcone, string date, string Ville) {
      fichierSql << "INSERT INTO "
      << "CATEGORIES(NUM_VILLE,Nom_Categorie, Chemin_icone, Date_Publication) "
      << "VALUES("
      << "(select NUM_VILLE from VILLES where NOM_VILLE='" << Ville << "'), "
      << "N'" << echapperQuote(nomCategorie) << "', "
      << "N'" << echapperQuote(cheminIcone) << "', "
      << "'" << date << "')" << endl << endl;
    }

    void sqlInsererbudget(fstream &fichierSql,int Montant_Recettes,int Montant_Depenses,std::string date,std::string Ville) {
        fichierSql << "INSERT INTO "
        << "BUDGETS(NUM_VILLE,Annee, Montant_Recettes, Montant_Depenses ) "
        << "VALUES("
        << "(select NUM_VILLE from VILLES where NOM_VILLE='" << Ville << "'), "
        << "N'" << echapperQuote(date) << "', "
        << "N'" << Montant_Recettes << "', "
        << "N'" << Montant_Depenses << "')" << endl << endl;
      }

      /* Ajoute la requete SQL de suppression des points d'une categorie
      dans le fichier SQL */
      void sqlSupprimerPointsCategorie(fstream &fichierSql, string nomCategorie) {
        fichierSql << "DELETE FROM POINTS WHERE Num_Categorie IN "
        << "(SELECT Num_Categorie FROM CATEGORIES "
        << "WHERE Nom_Categorie = '" << echapperQuote(nomCategorie) << "')"
        << endl << endl;
      }

      /* Ajoute la requete SQL de suppression d'une categorie dans le fichier SQL */
      void sqlSupprimerCategorie(fstream &fichierSql, string nomCategorie) {
        fichierSql << "DELETE FROM CATEGORIES "
        << "WHERE Nom_Categorie='" << echapperQuote(nomCategorie) << "'"
        << endl << endl;
      }

      /* Ajoute la requete SQL d'insertion d'un point dans le fichier SQL */
      void sqlInsererPoint(fstream &fichierSql, string nomCategorie, string x,
        string y, string txt, string cle, bool avecVille,
        string cleVille) {
          string reqVille;
          if (avecVille) {
            reqVille  = cleVille + ",";
          } else {
            reqVille  = "Null,";
          }

          fichierSql << "INSERT INTO "
          << "POINTS(Num_Categorie,X_Longitude,Y_Latitude,Texte_Point,"
          << "Cle_Opendata)"
          << "VALUES("
          << "(SELECT Num_Categorie FROM Categories WHERE Nom_Categorie = "
          << "N'" << echapperQuote(nomCategorie) << "'),"
          << virgulePoint(x) << ", "
          << virgulePoint(y) << ", "
          << "N'" << echapperQuote(txt) << "', "
          << cle
          << ")" << endl << endl ;
        }

        /* Ajoute la requete SQL d'extraction des points d'une categorie
        * dans le fichier SQL.
        */
        void sqlExtrairePointsCategorie(infoCategorie categorie, fstream &fichierSql) {
          fichierSql << "SET NOCOUNT ON" << endl
          << "SELECT X_Longitude, Y_Latitude, Texte_Point, Chemin_icone"
          << endl
          << "FROM POINTS " << endl
          << "  INNER JOIN CATEGORIES " << endl
          << "    ON POINTS.Num_Categorie = CATEGORIES.Num_Categorie " <<endl
          << "WHERE Nom_Categorie='"<< echapperQuote(categorie.nom) << "'"
          << endl << endl;
        }

        /* Ajoute la requete SQL d'extraction des points d'une categorie,
        * dans un ville, vers le fichier SQL.
        */
        void sqlExtrairePointsCategorieVille(infoCategorie categorie,
          infoVille ville,
          fstream &fichierSql) {
            fichierSql << "SET NOCOUNT ON" << endl
            << "SELECT X_Longitude, Y_Latitude, Texte_Point, Chemin_icone"
            << endl
            << "FROM POINTS " << endl
            << "  INNER JOIN CATEGORIES " << endl
            << "    ON POINTS.Num_Categorie = CATEGORIES.Num_Categorie " <<endl
            << "WHERE Nom_Categorie='"<< echapperQuote(categorie.nom) << "'"
            << endl
            << "  AND POINTS.Num_Ville="<< ville.id << endl
            << endl << endl;
          }

          /*
          * Nom du fichier contenant la requête SQL d'extraction des points d'une
          * catégorie, pour un ville donné.
          */
          string nomFichierSqlVille(string cheminSqlExtraction,
            const infoVille &ville,
            const infoCategorie &categorie) {
              return cheminSqlExtraction + "villes/categories/" + int2string(ville.id)
              + "-" + categorie.id + ".sql";
            }
