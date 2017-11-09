@echo off

rem compilation des tous les programmes C++ de l'application

rem une ligne de compilation a la structure suivante :
rem g++ OPTIONS_DE_COMPILATION -o NOM_EXECUTABLE LISTE DES FICHIERS_SOURCE

set PROJET="\\iut.bx1\Etudiants\Home\sdupuy002\Downloads\TESTS-PT2-SYLVAIN-AEXECUTER"
set MINGW=C:\MinGW\bin
set PATH=%PATH%;%MINGW%
set GPP="%MINGW%\g++"
set SRC=%PROJET%\programmes\src
set BIN=%PROJET%\programmes\bin
set OPTIONS=-std=c++11 -pedantic -Wextra

echo compilation des programmes :

echo - tests unitaires
 %GPP% %OPTIONS% -o %BIN%/tests %SRC%/tests.cc %SRC%/utils/csv.h %SRC%/utils/csv.cc %SRC%/utils/sql.h %SRC%/utils/sql.cc %SRC%/utils/chaines.h %SRC%/utils/chaines.cc

echo - insertion des villes
%GPP% %OPTIONS% -o %BIN%/insererVilles %SRC%/insererVilles.cc %SRC%/utils/csv.h %SRC%/utils/csv.cc %SRC%/utils/sql.h %SRC%/utils/sql.cc %SRC%/utils/chaines.h %SRC%/utils/chaines.cc

echo - insertion des budgets
%GPP% %OPTIONS% -o %BIN%/insererBudget %SRC%/insererBudget.cc %SRC%/utils/csv.h %SRC%/utils/csv.cc %SRC%/utils/sql.h %SRC%/utils/sql.cc %SRC%/utils/chaines.h %SRC%/utils/chaines.cc

echo - insertion des categories et points
%GPP% %OPTIONS% -o %BIN%/insererCategoriesEtPoints %SRC%/insererCategoriesEtPoints.cc %SRC%/utils/csv.h %SRC%/utils/csv.cc %SRC%/utils/sql.h %SRC%/utils/sql.cc %SRC%/utils/chaines.h %SRC%/utils/chaines.cc

echo - extraction des points de la base
%GPP% %OPTIONS% -o %BIN%/extrairePoints %SRC%/extrairePoints.cc %SRC%/utils/csv.h %SRC%/utils/csv.cc %SRC%/utils/sql.h %SRC%/utils/sql.cc %SRC%/utils/chaines.h %SRC%/utils/chaines.cc

echo - export json
%GPP% %OPTIONS% -o %BIN%/exportJson %SRC%/exportJson.cc %SRC%/utils/csv.h %SRC%/utils/csv.cc %SRC%/utils/json.h %SRC%/utils/json.cc %SRC%/utils/chaines.h %SRC%/utils/chaines.cc %SRC%/utils/sql.h %SRC%/utils/sql.cc

echo - generation du site web
%GPP% %OPTIONS% -o %BIN%/genererSite %SRC%/genererSite.cc %SRC%/utils/csv.h %SRC%/utils/csv.cc %SRC%/utils/html.h %SRC%/utils/html.cc %SRC%/utils/chaines.h %SRC%/utils/chaines.cc
