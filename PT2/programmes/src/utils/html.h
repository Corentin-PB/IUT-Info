#ifndef HTML_H
#define HTML_H

#include <string>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include "csv.h"

std::string chargerJsonCategories(std::string nomMap, std::string cheminJson,
								  infoCategorie categorie);

std::string listePagesCategories(infoCategorie categorie);

std::string listePagesVilles(infoVille ville);

std::string listePagesCategoriesVilles(const std::vector<infoCategorie> &categories,std::string nomVille);

std::string pointCategorie(std::string x, std::string y, std::string texte);

std::string intToString(int i);

std::string sectionVille(const infoVille &ville);

std::string declarerMapVille(const infoVille &ville);

std::string chargerDataDepenses(infoBudget budget);

std::string chargerDataRecettes(infoBudget budget);

std::string chargerJsonVilleCategories(const infoVille &ville,
										  const std::vector<infoCategorie> &categories);

std::string setStyleMapVille(const infoVille &ville);
#endif // HTML_H
