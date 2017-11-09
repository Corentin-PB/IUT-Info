/* Générer le site web, à partir :
* - des catégories présentes dans config.csv,
* - des données extraites de la base (villes, points),
* - des templates de pages web.
*/
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "utils/csv.h"
#include "utils/html.h"
#include "utils/chaines.h"

using namespace std;

/*
* On génère toutes les parties du site (templates) qui dépendent des
* catégories. Les données sur les catégories sont récupérées depuis config.csv.
*/
void lireCategories(map<string,string> &motsClesTemplates,
	string configCsv, string cheminJson,
	vector<infoCategorie> &categories) {

		ifstream configCsvFic;
		string ligne;

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
				break;
			}
			categories.push_back(categorie);
			// on ajoute l'import du json de la catégorie dans index.html
			motsClesTemplates["[[CHARGER_JSON_CATEGORIES]]"] +=
			chargerJsonCategories("map", cheminJson, categorie);
			// on ajoute la catégorie dans la liste sur la page index.html
			motsClesTemplates["[[LISTE_PAGES_CATEGORIES]]"] +=
			listePagesCategories(categorie);
		}
		configCsvFic.close();
	}

		/* Renvoie la liste des points d'une catégorie, au format html.
		* Pour cela on lit le fichier csv généré après extraction de la base.
		*/
		string listePointsCategorie(infoCategorie categorie, string cheminCsv) {

			string listePoints;

			// ouverture fichier csv en lecture
			string nomFichierCsv = cheminCsv + categorie.id + ".sql.csv";
			ifstream fichierCsv;
			fichierCsv.open(nomFichierCsv.c_str(), ios::in);
			if (fichierCsv.fail()) {
				cerr << "ouverture du fichier " << nomFichierCsv
				<< " impossible." << endl;
				exit(EXIT_FAILURE);
			}

			// lecture des lignes du fichier csv
			string ligne;
			while (getline(fichierCsv, ligne)) {
				int nbCol;
				TabLigne colonnes;
				coupeEnPlusieurs(ligne, CSV_SEP, nbCol, colonnes);
				if (nbCol!=NB_COL_CATEGORIE_CSV) {
					cerr << "Une ligne du fichier " << nomFichierCsv;
					cerr << " ne contient pas le bon nombre de colonnes : " << endl;
					cerr << ligne << endl << "Fichier ignoré." << endl;
					break;
				}
				string x = colonnes[0];
				string y = colonnes[1];
				string texte = colonnes[2];
				string icone = colonnes[3];
				listePoints += pointCategorie(x, y, texte);
			}
			fichierCsv.close();
			return listePoints;
		}

		/*
		* Dans une chaine, remplacer tous les mots-clés par leur valeur.
		* Limitations :
		* - on suppose une seule substitution par ligne, par mot-clé
		* - on suppose qu'un mot-clé n'est pas remplacé par un autre...
		*/
		string substituer(string &chaine, const map<string,string> &chainesARemplacer) {
			string sortie = chaine;
			for (auto chaineARemplacer : chainesARemplacer) {
				string motcle = chaineARemplacer.first;
				string valeur = chaineARemplacer.second;
				size_t position = sortie.find(motcle);
				if (position != string::npos) {
					sortie.replace(position, motcle.length(), valeur);
				}
			}
			return sortie;
		}

		/*
		* Lecture d'un fichier template : on remplace chaque mot-clé à remplacer
		* par une valeur, pour constituer un nouveau fichier.
		*/
		void remplacerChaines(string nomFichierEntree, string nomFichierSortie,
			const map<string,string> &chainesARemplacer) {

				// ouverture du fichier en entrée
				ifstream fichierEntree;
				fichierEntree.open(nomFichierEntree.c_str(), ios::in);
				if (fichierEntree.fail()) {
					cerr << "ouverture du fichier " << nomFichierEntree << " impossible."
					<< endl;
					exit(EXIT_FAILURE);
				}

				// ouverture du fichier en sortie
				fstream fichierSortie;
				fichierSortie.open(nomFichierSortie.c_str(), ios::out);
				if (fichierSortie.fail()) {
					cerr << "ouverture du fichier " << nomFichierSortie << " impossible."
					<< endl;
					exit(EXIT_FAILURE);
				}

				// remplacement des mots-clés par leur valeur sur chaque ligne
				string ligne;
				while (getline(fichierEntree, ligne)) {
					fichierSortie << substituer(ligne, chainesARemplacer) << endl;
				}

				// fermeture
				fichierEntree.close();
				fichierSortie.close();
			}

			/*
			* Initialise la map des chaines à remplacer (mots-clés des templates).
			*/
			void initialiserMotsClesTemplates(map<string,string> &motsClesTemplates) {
				motsClesTemplates["[[CHARGER_JSON_CATEGORIES]]"] = "";
				motsClesTemplates["[[NOM_CATEGORIE]]"] = "";
				motsClesTemplates["[[NOM_VILLE]]"] = "";
				motsClesTemplates["[[LISTE_POINTS_CATEGORIE]]"] = "";
				motsClesTemplates["[[LISTE_PAGES_CATEGORIES]]"] = "";
				motsClesTemplates["[[LISTE_PAGES_VILLES]]"] = "";
				motsClesTemplates["[[SECTIONS_VILLES]]"] = "";
				motsClesTemplates["[[DECLARER_MAPS_VILLES]]"] = "";
				motsClesTemplates["[[CHARGER_JSON_VILLES_CATEGORIES]]"] = "";
				motsClesTemplates["[[SETSTYLE_MAPS_VILLES]]"] = "";
				motsClesTemplates["[[SECTIONS_VILLES]]"] = "";
				motsClesTemplates["[[LISTE_PAGES_CATEGORIES_VILLES]]"] = "";
				motsClesTemplates["[[DATA_DEPENSES]]"] = "";
				motsClesTemplates["[[DATA_RECETTES]]"] = "";
			}

			/*
			* Analyse de la ligne de commande.
			*/
			void analyserLigneDeCommande(int argc, char *argv[],
				string &configCsv,
				string &villesCsv,
				string &budgetCsv,
				string &cheminSite, string &cheminJson,
				string &cheminTemplates,
				string &cheminExtractions) {
					if( argc != 8 ) {
						cout << "Erreur : nombre d'arguments incorrect." << endl;
						cout << "Usage : " << argv[0]
						<< " config.csv cheminSite cheminJson cheminTemplates "
						<< "cheminExtractions" << endl
						<< " Les chemins doivent se terminer par un séparateur "
						<< "(/ ou \\ selon le système)." << endl;
						exit(-1);
					}
					configCsv = argv[1];
					villesCsv = argv[2];
					budgetCsv = argv[3];
					cheminSite = argv[4];
					cheminJson = argv[5];
					cheminTemplates = argv[6];
					cheminExtractions = argv[7];
				}

				/*
				* Procédure principale.
				*/


				int main( int argc, char* argv[] )
				{
					string configCsv, villesCsv, budgetCsv;
					string cheminSite, cheminJson, cheminTemplates, cheminExtractions;
					vector<infoCategorie> categories;

					// chaines à remplacer (mots-clés) dans les templates html
					map<string,string> motsClesTemplates;

					// analyse de la ligne de commande et ouverture des fichiers
					analyserLigneDeCommande(argc, argv, configCsv,villesCsv,budgetCsv, cheminSite,
						cheminJson, cheminTemplates, cheminExtractions);

						// on lit le fichier config.csv, et on construit les chaînes qui
						// remplaceront les mots-clés dans les templates
						lireCategories(motsClesTemplates, configCsv, cheminJson, categories);

						vector<infoVille> villes;
						// on lit le fichier villes.csv
						chargerVilles(villesCsv, villes);

						for(infoVille ville : villes){
						motsClesTemplates["[[LISTE_PAGES_VILLES]]"] +=
					  listePagesVilles(ville);
						}

           vector<infoBudget> budgets;
					 chargerBudgets(budgetCsv, budgets);

					 for(infoBudget budget : budgets){
						motsClesTemplates["[[DATA_DEPENSES]]"] +=
						chargerDataDepenses(budget);
						motsClesTemplates["[[DATA_RECETTES]]"] +=
						chargerDataRecettes(budget);
					 }

						// on génère les pages html, en remplaçant dans les templates les mots-clés
						// par leur valeur :
						string pageTemplate, pageHtml;

						// - page index.html
						pageTemplate = cheminTemplates + "index.html";
						pageHtml = cheminSite + "index.html";
						remplacerChaines(pageTemplate, pageHtml, motsClesTemplates);

						// - pages des categories (jeux de données)
						for (infoCategorie categorie : categories) {
							motsClesTemplates["[[NOM_CATEGORIE]]"] = categorie.nom;
							motsClesTemplates["[[LISTE_POINTS_CATEGORIE]]"] =
							listePointsCategorie(categorie, cheminExtractions);
							motsClesTemplates["[[CHARGER_JSON_CATEGORIE]]"] =
							chargerJsonCategories("map", cheminJson, categorie);
							pageTemplate = cheminTemplates + "categorie.html";
							pageHtml = cheminSite + "categories-" + categorie.id + ".html";
							remplacerChaines(pageTemplate, pageHtml, motsClesTemplates);
						}

						// - page des villes
						/*  pageTemplate = cheminTemplates + "villes.html";
						pageHtml = cheminSite + "villes.html";
						lireVilles(motsClesTemplates, villesCsv, categories);
						remplacerChaines(pageTemplate, pageHtml, motsClesTemplates);*/



						for (infoVille ville : villes) {
							motsClesTemplates["[[CHARGER_JSON_VILLES_CATEGORIES]]"] ="";
							motsClesTemplates["[[SECTIONS_VILLES]]"] = "";
							motsClesTemplates["[[SETSTYLE_MAPS_VILLES]]"] = "";
							motsClesTemplates["[[LISTE_PAGES_CATEGORIES_VILLES]]"] = "";
							string tmp;
							ville.nom = supprimeEspacesDroite(ville.nom);
							tmp = ville.nom + ".html";
							pageTemplate = cheminTemplates + "villes.html";
							pageHtml = cheminSite + tmp;

							// on ajoute, pour chaque ville :

							motsClesTemplates["[[LISTE_PAGES_CATEGORIES_VILLES]]"] +=
							listePagesCategoriesVilles(categories,ville.nom);

							// - la déclaration de la variable javascript de sa map
							motsClesTemplates["[[DECLARER_MAPS_VILLES]]"] +=
							declarerMapVille(ville);
							// - l'initialisation de la variable javascript de la map
							motsClesTemplates["[[CHARGER_JSON_VILLES_CATEGORIES]]"] +=
							chargerJsonVilleCategories(ville, categories);
							// - le chargement du style de la map
							motsClesTemplates["[[SETSTYLE_MAPS_VILLES]]"] +=
							setStyleMapVille(ville);
							// - sa section
							motsClesTemplates["[[SECTIONS_VILLES]]"] += sectionVille(ville);
							motsClesTemplates["[[NOM_VILLE]]"] = ville.nom;

							remplacerChaines(pageTemplate, pageHtml, motsClesTemplates);
						}

						return EXIT_SUCCESS;
					}
