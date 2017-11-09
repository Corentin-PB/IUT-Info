/*
 ----------------------------------------------------------------------------
             Génération d'une base de données pour
                        SQL Server 2005
                       (16/1/2017 15:34:14)
 ----------------------------------------------------------------------------
     Nom de la base : PT2_XXXXX
     Projet : 
     Auteur : CRIIUT
     Date de dernière modification : 16/1/2017 15:33:06
 ----------------------------------------------------------------------------
*/

drop database PT2_XXXXX
go

/* -----------------------------------------------------------------------------
      OUVERTURE DE LA BASE PT2_XXXXX
----------------------------------------------------------------------------- */

create database PT2_XXXXX
go

use PT2_XXXXX
go



/* -----------------------------------------------------------------------------
      TABLE : POINTS
----------------------------------------------------------------------------- */

create table POINTS
  (
     NUM_POINT int identity (1, 1)   ,
     NUM_QUARTIER int  null  ,
     NUM_CATEGORIE int  not null  ,
     X_LONGITUDE float  not null  ,
     Y_LATITUDE float  not null  ,
     TEXTE_POINT char(100)  not null  ,
     CLE_OPENDATA int  not null  
     ,
     constraint PK_POINTS primary key (NUM_POINT)
  ) 
go



/*      INDEX DE POINTS      */



/* -----------------------------------------------------------------------------
      TABLE : QUARTIERS
----------------------------------------------------------------------------- */

create table QUARTIERS
  (
     NUM_QUARTIER int  not null  ,
     NOM_QUARTIER char(50)  not null  
     ,
     constraint PK_QUARTIERS primary key (NUM_QUARTIER)
  ) 
go



/* -----------------------------------------------------------------------------
      TABLE : CATEGORIES
----------------------------------------------------------------------------- */

create table CATEGORIES
  (
     NUM_CATEGORIE int identity (1, 1)   ,
     NOM_CATEGORIE char(60)  not null  ,
     CHEMIN_ICONE char(255)  not null  ,
     DATE_PUBLICATION datetime  not null  
     ,
     constraint PK_CATEGORIES primary key (NUM_CATEGORIE)
  ) 
go



/* -----------------------------------------------------------------------------
      REFERENCES SUR LES TABLES
----------------------------------------------------------------------------- */



alter table POINTS 
     add constraint FK_POINTS_QUARTIERS foreign key (NUM_QUARTIER) 
               references QUARTIERS (NUM_QUARTIER)
go




alter table POINTS 
     add constraint FK_POINTS_CATEGORIES foreign key (NUM_CATEGORIE) 
               references CATEGORIES (NUM_CATEGORIE)
go




/*
 -----------------------------------------------------------------------------
               FIN DE GENERATION
 -----------------------------------------------------------------------------
*/