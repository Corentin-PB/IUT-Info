#ifndef SQL_H
#define SQL_H

#include <fstream>
#include "csv.h"

std::string virgulePoint(std::string s);

std::string echapperQuote(std::string s);

void sqlInsererVille(std::fstream &fichierSql,std::string cleVille, std::string nomVille);

void sqlSupprimerVilles(std::fstream &fichierSql);

void sqlInsererPoint(std::fstream &fichierSql, std::string nomCategorie,std::string x, std::string y, std::string txt,std::string cle, bool avecVille,std::string cleVille);

void sqlSupprimerPointsCategorie(std::fstream &fichierSql,std::string nomCategorie);

void sqlSupprimerCategorie(std::fstream &fichierSql, std::string nomCategorie);

void sqlSupprimerbudget(std::fstream &fichierSql, infoBudget budget);

void sqlInsererCategorie(std::fstream &fichierSql, std::string nomCategorie,std::string cheminIcone, std::string date, std::string Ville);

void sqlInsererbudget(std::fstream &fichierSql, int montantRecettes, int montantDepenses, std::string date,std::string Ville);

void sqlExtrairePointsCategorie(infoCategorie categorie, std::fstream &fichierSql);

void sqlExtrairePointsCategorieVille(infoCategorie categorie,infoVille ville, std::fstream &fichierSql);

std::string nomFichierSqlVille(std::string cheminSql,	const infoVille &ville,const infoCategorie &categorie);


#endif // SQL_H
