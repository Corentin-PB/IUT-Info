@echo off

rem ------------------------------------------------------
rem Script de mise à jour global : 
rem - mise à jour de toutes les données de la base, 
rem - ainsi que du site web.
rem 
rem Prérequis :
rem - les programmes ont été compilés (voir compiler.bat)
rem - la base a été créée (voir le script de création).
rem ------------------------------------------------------

set PROJET=\\iut.bx1\Etudiants\Home\sdupuy002\Downloads\TESTS-PT2-SYLVAIN-AEXECUTER
set BIN=%PROJET%\programmes\bin
set CONFIG_CSV=%PROJET%\configCategories.csv
set CONFIGVILLES_CSV=%PROJET%\configVilles.csv
set CONFIGBUDGET_CSV=%PROJET%\configBudgets.csv
set DONNEES_CSV=%PROJET%\donnees\
set REQUETES_CREATION=%PROJET%\requetes\creation_base
set REQUETES_INSERTION=%PROJET%\requetes\insertion
set REQUETES_EXTRACTION=%PROJET%\requetes\extraction
set VILLES_CSV=%REQUETES_EXTRACTION%\villes\villes.csv
set SITE=%PROJET%\site_web
set JSON_RELATIF=json
set JSON=%SITE%\%JSON_RELATIF%
set LOGS=%PROJET%\logs
set BD_SERVEUR=info-dormeur
set BD_NOM=PT2_B6_2

rem ------------------------------------
rem Insertion des villes dans la base
rem ------------------------------------

set COLONNE_CLE_VILLE=1
set COLONNE_NOM_VILLE=2

echo insertion des villes : generation des requetes sql a partir de configVilles.csv
%BIN%\insererVilles %CONFIGVILLES_CSV% %REQUETES_CREATION%\villes.sql %COLONNE_CLE_VILLE% %COLONNE_NOM_VILLE%

echo insertion des villes : execution de la requete sql
sqlcmd -S %BD_SERVEUR% -U ETD -P ETD -d %BD_NOM% -i %REQUETES_CREATION%\villes.sql -o %LOGS%\villes.log


rem ------------------------------------
rem Insertion des bugdets dans la base
rem ------------------------------------

echo insertion des budgets : generation sql a partir des fichiers csv
%BIN%\insererBudget %CONFIGBUDGET_CSV% %DONNEES_CSV%Bordeaux\budgets-primitifs\ %REQUETES_INSERTION%\Budgets\
%BIN%\insererBudget %CONFIGBUDGET_CSV% %DONNEES_CSV%Nantes\budgets-primitifs\ %REQUETES_INSERTION%\Budgets\
%BIN%\insererBudget %CONFIGBUDGET_CSV% %DONNEES_CSV%Toulouse\budgets-primitifs\ %REQUETES_INSERTION%\Budgets\

pushd %REQUETES_INSERTION%\Budgets
for %%f in (*) do sqlcmd -S %BD_SERVEUR% -U ETD -P ETD -d %BD_NOM% -i %%f -o %LOGS%\insertion-%%f.log
popd

rem ---------------------------------------------------
rem Insertion des catégories et des points dans la base
rem ---------------------------------------------------

echo insertion des categories et points : generation sql a partir des fichiers csv
%BIN%\insererCategoriesEtPoints %CONFIG_CSV% %DONNEES_CSV%Bordeaux\geographiques\ %REQUETES_INSERTION%\
%BIN%\insererCategoriesEtPoints %CONFIG_CSV% %DONNEES_CSV%Nantes\geographiques\ %REQUETES_INSERTION%\
%BIN%\insererCategoriesEtPoints %CONFIG_CSV% %DONNEES_CSV%Toulouse\geographiques\ %REQUETES_INSERTION%\

echo insertion des categories et points : execution des requetes sql
rem on se deplace dans %REQUETES_INSERTION% puis on y exécute toutes les requêtes de tous les fichiers
pushd %REQUETES_INSERTION%
for %%f in (*) do sqlcmd -S %BD_SERVEUR% -U ETD -P ETD -d %BD_NOM% -i %%f -o %LOGS%\insertion-%%f.log
popd

rem ----------------------
rem Génération du site web
rem ----------------------


echo extraction des donnees depuis la base : sql vers csv


rem extraction des villes
sqlcmd -S %BD_SERVEUR% -U ETD -P ETD -d %BD_NOM% -i %REQUETES_EXTRACTION%\villes\villes.sql -o %VILLES_CSV%  -s ";" -h-1 -W

rem generation des requetes d'extraction
%BIN%\extrairePoints %CONFIG_CSV% %VILLES_CSV% %REQUETES_EXTRACTION%\

rem extraction des points, par categorie
pushd %REQUETES_EXTRACTION%
for %%f in (*) do sqlcmd -S %BD_SERVEUR% -U ETD -P ETD -d %BD_NOM% -i %%f -o %REQUETES_EXTRACTION%\csv\%%f.csv  -s ";" -h-1 -W
popd


echo extraction des donnees depuis la base : csv vers json


%BIN%\exportJson %CONFIG_CSV% %VILLES_CSV% %REQUETES_EXTRACTION%\csv\ %JSON%\ %REQUETES_EXTRACTION%\ images/icones/


echo generation du site web


%BIN%\genererSite %CONFIG_CSV% %VILLES_CSV% %CONFIGBUDGET_CSV% %SITE%\ %JSON_RELATIF%/ %SITE%\templates\ %REQUETES_EXTRACTION%\csv\
