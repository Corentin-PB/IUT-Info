/*
 * Tests unitaires
 */

#include <array>
#include <string>
#include <cassert>
#include <cstdlib>
#include "utils/sql.h"
#include "utils/csv.h"
#include "utils/json.h"
#include "utils/chaines.h"

using namespace std;

// tests SQL

void testVirgulePoint() {
  assert(virgulePoint("12,3")=="12.3");
  assert(virgulePoint("1,")=="1.");
}

void testEchapperQuote() {
  assert(echapperQuote("1'2")=="1''2");
  assert(echapperQuote("'")=="''");
  assert(echapperQuote("12")=="12");
  assert(echapperQuote("''")=="''''");
}

// tests CSV

void testCoupeEnDeux() {
  string gauche, droite;
  bool coupe;

  coupe = coupeEnDeux("abc", ',', gauche, droite);
  assert(!coupe);

  coupe = coupeEnDeux("ab,c", ',', gauche, droite);
  assert(coupe && gauche=="ab" && droite=="c");

  coupe = coupeEnDeux("ab,c,", ',', gauche, droite);
  assert(coupe && gauche=="ab" && droite=="c,");

  coupe = coupeEnDeux(",,", ',', gauche, droite);
  assert(coupe && gauche=="" && droite==",");

  coupe = coupeEnDeux(",", ',', gauche, droite);
  assert(coupe && gauche=="" && droite=="");
}

void testCoupeEnPlusieurs() {
  int nbMorceaux;
  TabLigne morceaux;

  coupeEnPlusieurs("1;22;333", ';', nbMorceaux, morceaux);
  assert(nbMorceaux==3);
  assert(morceaux[0]=="1" && morceaux[1]=="22" && morceaux[2]=="333");

  coupeEnPlusieurs(";;", ';', nbMorceaux, morceaux);
  assert(nbMorceaux==3);
  assert(morceaux[0]=="" && morceaux[1]=="" && morceaux[2]=="");

  coupeEnPlusieurs("", ';', nbMorceaux, morceaux);
  assert(nbMorceaux==1);
  assert(morceaux[0]=="");

  coupeEnPlusieurs("1", ';', nbMorceaux, morceaux);
  assert(nbMorceaux==1);
  assert(morceaux[0]=="1");
}

void testIndiceColonneMax() {
  infoCategorie categorie;
  categorie.colX = 3;
  categorie.colY = 11;
  categorie.colTxt = 4;
  categorie.colVille = 2;
  categorie.colCle = 1;
  assert(indiceColonneMax(categorie)==11);
}

void testLireLigneConfigCsv() {
  string id = "identifiant categorie";
  string nom = "nom categorie";
  string date = "01/01/2016";
  int colX = 12;
  int colY = 1;
  int colTxt = 3;
  int colCle = 2;
  int colVille = 7;
  string cheminIcone = "chemin/icone/";

  // avec ville
  string ligne = id + CSV_SEP + nom + CSV_SEP + date
	+ CSV_SEP + int2string(colX)
	+ CSV_SEP + int2string(colY) + CSV_SEP + int2string(colTxt)
	+ CSV_SEP + int2string(colCle) + CSV_SEP + int2string(colVille)
	+ CSV_SEP + cheminIcone;
  infoCategorie categorie;
  bool ok = lireLigneConfigCsv(ligne, "config.csv", categorie);
  assert(ok);
  assert(categorie.id == id);
  assert(categorie.nom == nom);
  assert(categorie.date == date);
  assert(categorie.colX == colX-1);
  assert(categorie.colY == colY-1);
  assert(categorie.colTxt == colTxt-1);
  assert(categorie.colCle == colCle-1);
  assert(categorie.colVille == colVille-1);
  assert(categorie.cheminIcone == cheminIcone);

  // sans ville
  ligne = id + CSV_SEP + nom + CSV_SEP + date + CSV_SEP + int2string(colX)
	+ CSV_SEP + int2string(colY) + CSV_SEP + int2string(colTxt)
	+ CSV_SEP + int2string(colCle) + CSV_SEP // + int2string(colVille)
	+ CSV_SEP + cheminIcone;
  ok = lireLigneConfigCsv(ligne, "config.csv", categorie);
  assert(ok);
  assert(categorie.colVille == -1);

  // avec une colonne manquante
  ligne = id + CSV_SEP + nom + CSV_SEP + date + CSV_SEP + int2string(colX)
	+ CSV_SEP + int2string(colY) + CSV_SEP + int2string(colTxt)
	+ CSV_SEP + int2string(colCle) + CSV_SEP + int2string(colVille);
	// + CSV_SEP + cheminIcone;
  ok = lireLigneConfigCsv(ligne, "config.csv", categorie);
  assert(!ok);
}

void testLireLigneVillesCsv() {
  int idVille = 17;
  string nomVille = "mon ville";
  infoVille ville;

  // ligne correcte
  string ligne = int2string(idVille) + CSV_SEP + nomVille;
  bool ok = lireLigneVillesCsv(ligne, "villes.csv", ville);
  assert(ok);
  assert(ville.id == idVille);
  assert(ville.nom == nomVille);

  // ligne incorrecte (champ en trop)
  ligne = int2string(idVille) + CSV_SEP + nomVille
	+ CSV_SEP + nomVille;
  ok = lireLigneVillesCsv(ligne, "villes.csv", ville);
  assert(!ok);
}

// tests JSON

void testSupprimeEspacesDroite() {
  assert(supprimeEspacesDroite("")=="");
  assert(supprimeEspacesDroite(" ")=="");
  assert(supprimeEspacesDroite(" t")==" t");
  assert(supprimeEspacesDroite("t ")=="t");
  assert(supprimeEspacesDroite("t t")=="t t");
  assert(supprimeEspacesDroite("t t ")=="t t");
  assert(supprimeEspacesDroite("  ttt t t  ")=="  ttt t t");
}

/*
 * Procédure principale.
 */
int main( int argc, char* argv[] )
{
  //tests SQL;
  testVirgulePoint();
  testEchapperQuote();
  //tests CSV;
  testCoupeEnDeux();
  testCoupeEnPlusieurs();
  testIndiceColonneMax();
  testLireLigneConfigCsv();
  testLireLigneVillesCsv();
  //tests JSON
  testSupprimeEspacesDroite();
}
