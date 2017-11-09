/*
* Quelques fonctions utiles pour la génération de code HTML.
*/
#include "chaines.h"
#include "html.h"
#include <sstream>

using namespace std;


/*
* Renvoie le nom d'une carte (map) pour un ville donné.
*/
string nomDivMap(const infoVille &ville) {
	return "map-" + int2string(ville.id);
}

/*
* Nom de la variable javascript associée à la map d'un ville.
*/
string nomVarMap(infoVille ville) {
	return "map_" + int2string(ville.id);
}


/*
* Contenu d'un mot-clé CHARGER_JSON_CATEGORIES pour une catégorie donnée.
*/
string chargerJsonCategories(string nomMap, string cheminJson,
	infoCategorie categorie) {
		return "        " + nomMap + ".data.loadGeoJson('"
		+ cheminJson + categorie.id + ".json');\n";
	}


	/*
	* Contenu d'un mot-clé CHARGER_JSON_VILLES_CATEGORIES de villes.html,
	* pour un ville donné.
	*/
	string chargerJsonVilleCategories(const infoVille &ville,
		const vector<infoCategorie> &categories) {

			string chargerJson = "        " + nomVarMap(ville)
			+ " = new google.maps.Map(document.getElementById('"
			+ nomDivMap(ville) + "'), mapOptions);\n";
			for(infoCategorie categorie : categories) {

				string tmp = ville.nom;
				string tmpId;
				for(int i=0; i < 4; i++) {
					if(tmp[i] != ' ')
					tmpId += tmp[i];
				}

				transform(tmpId.begin(),tmpId.end(),tmpId.begin(),::towlower);
				if (categorie.identifiantVille == tmpId) {
					chargerJson += "        " + nomVarMap(ville)
					+ ".data.loadGeoJson('json/"
					/*+ int2string(ville.id) + "-" */+ categorie.id + ".json');\n";
				}
			}
			return chargerJson;
		}

		/*
		* Contenu d'un mot-clé LISTE_PAGES_CATEGORIES pour une catégorie donnée,
		* sur la page index.html.
		*/
		string listePagesCategories(infoCategorie categorie) {
			return "<li><img src=\"images/icones/" + categorie.cheminIcone
			+ "\"/> <a href=\"categories-" + categorie.id + ".html\">"
			+ categorie.nom + "</a>\n";
		}

		string listePagesVilles(infoVille ville) {
			return "<li><a href=\"" + ville.nom + ".html\">"
			+ ville.nom + "</a></li>\n";
		}

		string listePagesCategoriesVilles(const vector<infoCategorie> &categories,string nomVille) {
			string tmpPage="";
			for(infoCategorie categorie : categories) {

				string tmp = nomVille;
				string tmpId;
				for(int i=0; i < 4; i++) {
					if(tmp[i] != ' ')
					tmpId += tmp[i];
				}
				transform(tmpId.begin(),tmpId.end(),tmpId.begin(),::towlower);
				if(categorie.identifiantVille==tmpId){
					tmpPage += "<li><img src=\"images/icones/" + categorie.cheminIcone
					+ "\"/> <a href=\"categories-" + categorie.id + ".html\">"
					+ categorie.nom + "</a>\n";
				}
			}
			return tmpPage;
		}

		/*
		* Contenu d'une ligne décrivant un point, sur la page d'une catégorie.
		*/
		string pointCategorie(string x, string y, string texte) {
			return "      <tr><td>" + x + "</td><td>" + y + "</td><td>" + texte
			+ "</td></tr>\n";
		}


		/*
		* Contenu d'un mot-clé SECTIONS_VILLES de villes.html,
		* pour un ville donné.
		*/
		string sectionVille(const infoVille &ville) {
			string section = "\n<h2>" + ville.nom + "</h2>\n";
			section += "<div id=\"" + nomDivMap(ville)
			+ "\" class=\"map-canvas\"></div>\n";
			return section;
		}


		/*
		* Contenu d'un mot-clé DECLARER_MAPS_VILLES_CATEGORIES de villes.html,
		* pour un ville donné.
		*/
		string declarerMapVille(const infoVille &ville) {
			return "      var " + nomVarMap(ville) + ";\n";
		}



		/*
		* Contenu d'un mot-clé SETSTYLE_MAPS_VILLES de villes.html,
		* pour un ville donné.
		*/
		string setStyleMapVille(const infoVille &ville) {
			string indent = "        ";
			string setStyleMap = indent +
			nomVarMap(ville) + ".data.setStyle(setColorStyleFn);\n";
			setStyleMap += indent + nomVarMap(ville)
			+ ".data.addListener('mouseover', function(event) {\n";
			setStyleMap += indent
			+ "  infowindow.setContent(event.feature.getProperty('description'));\n";
			setStyleMap += indent + "  infowindow.setPosition(event.latLng);\n";
			setStyleMap += indent +
			"  infowindow.setOptions({pixelOffset: new google.maps.Size(0,-34)});\n";
			setStyleMap += indent + "  infowindow.open(" + nomVarMap(ville) + ");\n";
			setStyleMap += indent + "});\n";
			setStyleMap += indent + "google.maps.event.addListener("
			+ nomVarMap(ville) + ", 'click', function() {\n";
			setStyleMap += indent
			+ "  infowindow.close(); // un clic sur la carte ferme les infowindows\n";
			setStyleMap += indent + "});\n";
			return setStyleMap;
		}

		std::string intToString(int i) {
		     std::ostringstream oss;
		     oss << i;
		     return oss.str();
		}

		string chargerDataDepenses(infoBudget budget){
			string depenses = intToString(budget.montantDepenses);
			string tmp ="{ x: " + budget.annee + ", y: " + depenses + " },\n";
			return tmp;
		}

		string chargerDataRecettes(infoBudget budget){
		string recettes = intToString(budget.montantRecettes);
    string tmp = "{ x: " + budget.annee + ", y: " + recettes + " },\n";
			return  tmp;
		}
