/* Quelques fonctions supplémentaires sur les chaînes de caractère.
 */
#include <string>
#include <sstream>

using namespace std;

/*
 * Conversion d'un entier en chaîne de caractères.
 * Pour pallier l'absence de std::to_string() dans MinGW.
 */
string int2string(int i) {
  stringstream stream;
  stream << i;
  return stream.str();
}


/* Supprime les espaces à droite. */
string supprimeEspacesDroite(string texte) {
  string resultat = texte;
  size_t dernierEspace = texte.find_last_not_of(" ");
  if (dernierEspace != string::npos) {
	resultat = texte.substr(0, dernierEspace+1);
  } else {
	resultat = "";
  }
  return resultat;
}
