<!DOCTYPE html>
<html>
<head>

	<link rel="stylesheet" type="text/css" href="style.css">	

	<script src="https://maps.googleapis.com/maps/api/js"></script>
	
	<script>
	  // declaration des cartes
    var map;

	  // la fenetre qui s'ouvre quand on passe la souris sur un point
	  var infowindow = new google.maps.InfoWindow();

	  // fonction d'initialisation
    function initialize() {
      var mapOptions = {
        zoom: 6,
        center: {lat:  46.55, lng: 2.4},
        mapTypeId: google.maps.MapTypeId.TERRAIN
      };
      map = new google.maps.Map(document.getElementById('map-categories'),
        mapOptions);
	    // initialisation des cartes et chargement des donnees
      map.data.loadGeoJson('json/airejeux.json');
      map.data.loadGeoJson('json/parcjardin.json');
      map.data.loadGeoJson('json/poiculture.json');
      map.data.loadGeoJson('json/poieducation.json');
      map.data.loadGeoJson('json/poienfance.json');
      map.data.loadGeoJson('json/poiservices.json');
      map.data.loadGeoJson('json/poisocial.json');
      map.data.loadGeoJson('json/poisport.json');
      map.data.loadGeoJson('json/sigaccesinternet.json');
      map.data.loadGeoJson('json/sigparkpub.json');
      map.data.loadGeoJson('json/sigsanitaire.json');
      map.data.loadGeoJson('json/sigstavelo.json');
      map.data.loadGeoJson('json/abris-velos-de-nantes-metropole.json');
      map.data.loadGeoJson('json/defibrillateurs-de-la-ville-de-nantes.json');
      map.data.loadGeoJson('json/jardins-familiaux-de-la-ville-de-nantes.json');
      map.data.loadGeoJson('json/localisation-des-equipements-publics-relevant-du-theme-mobilite-de-nantes-metropole-1.json');
      map.data.loadGeoJson('json/localisation-des-equipements-publics-relevant-du-theme-sports-loisirs-de-nantes-metropole.json');
      map.data.loadGeoJson('json/localisation-et-caracteristiques-des-parcs-et-jardins-de-nantes.json');
      map.data.loadGeoJson('json/toilettes-publiques-de-nantes-metropole.json');
      map.data.loadGeoJson('json/aires-de-jeux.json');
      map.data.loadGeoJson('json/bornes-wi-fi.json');
      map.data.loadGeoJson('json/boulodromes.json');
      map.data.loadGeoJson('json/defibrillateurs.json');
      map.data.loadGeoJson('json/equipements-socioculturels-de-proximite.json');
      map.data.loadGeoJson('json/sanisettes.json');
      map.data.loadGeoJson('json/site-communal-dimplantation-de-fitness.json');
      map.data.loadGeoJson('json/velo-toulouse.json');


	    // fonction de style
	    var setColorStyleFn = function(feature) {
       return {icon: feature.getProperty('icon')};
     };

	    // style des cartes, et listener pour la fenetre qui s'ouvre quand on passe la souris sur un point
	    map.data.setStyle(setColorStyleFn);
	    map.data.addListener('mouseover', function(event) {
        infowindow.setContent(event.feature.getProperty('description'));
        infowindow.setPosition(event.latLng);
        infowindow.setOptions({pixelOffset: new google.maps.Size(0,-34)});
        infowindow.open(map);
      });
      google.maps.event.addListener(map, 'click', function() {
          infowindow.close(); // un clic sur la carte ferme les infowindows
        });

	  } // end initialize

      // appel de la fonction d'initialisation une fois la page chargee
      google.maps.event.addDomListener(window, 'load', initialize);
    </script>

    <script type="text/javascript" src="http://canvasjs.com/assets/script/jquery-1.11.1.min.js"></script>
    <!--<script type="text/javascript">
     window.onload = function () {

      var chart = new CanvasJS.Chart("chartContainer",
      {
        title:{
          text: "Budgets primitifs"  
        },
        axisX:{
         valueFormatString:  "####",
         interval: 1
       },
       axisY:{
        valueFormatString:  "#,##0.##",
        suffix: " euros"
      },
      data: [
      {        
        type: "spline",
        legendText: "depenses",
        showInLegend: true,
        dataPoints: [
        { x: 2012, y: 1877302928 },
        { x: 2013, y: 1877302939 },
        { x: 2014, y: 1877302950 },
        { x: 2015, y: 1877302962 },
        { x: 2010, y: 1877302973 },
        { x: 2011, y: 1877302984 },
        { x: 2012, y: 1877302995 },
        { x: 2013, y: 1877303006 },
        { x: 2014, y: 1877303017 },
        { x: 2015, y: 1877303028 },
        { x: 2016, y: 1877303039 },
        { x: 2012, y: 1877303055 },
        { x: 2014, y: 1877303067 },
        { x: 2015, y: 1877303081 },
        { x: 2016, y: 1877303095 },

        ]
      },
      {
        type: "spline",
        legendText: "recettes",
        showInLegend: true,
        dataPoints: [
        { x: 2012, y: 91 },
        { x: 2013, y: 91 },
        { x: 2014, y: 91 },
        { x: 2015, y: 91 },
        { x: 2010, y: 91 },
        { x: 2011, y: 91 },
        { x: 2012, y: 91 },
        { x: 2013, y: 91 },
        { x: 2014, y: 91 },
        { x: 2015, y: 91 },
        { x: 2016, y: 91 },
        { x: 2012, y: 108 },
        { x: 2014, y: 108 },
        { x: 2015, y: 108 },
        { x: 2016, y: 108 },

        ]
      },
      ]
    });

      chart.render();
    }
  </script>
  <script type="text/javascript" src="./canvasjs.min.js"></script>!-->

  <meta charset="UTF-8"> 
</head>

<body>
  <?php
 // RECONNAITRE LE NAVIGATEUR UTILISE

/*$NAV_UNKNOWN = UNKNOWN;
$NAV_NETSCAPE = Netscape;
$NAV_FIREFOX = Firefox;
$NAV_SAFARI = Safari;
$NAV_KONQUEROR = Konqueror;
$NAV_OPERA = Opera;
$NAV_CHROME = Chrome;
$NAV_MSIE = Msie;
$NAV_EDGE = "Microsoft Edge";
$BOT_GOOGLE = Google;
 
$HUA = getenv("HTTP_USER_AGENT");
 
$nav = $NAV_UNKNOWN;
if ( ereg("(Nav|Gold|X11|Netscape)", $HUA) && !ereg("(MSIE|Konqueror)", $HUA) ) $nav = $NAV_NETSCAPE;
elseif (ereg("Opera", $HUA)) $nav = $NAV_OPERA;
elseif (ereg("MSIE", $HUA)) $nav = $NAV_MSIE;
elseif (ereg("Mozilla", $HUA) && ereg("Chrome", $HUA) && !ereg("Edge", $HUA)) $nav = $NAV_CHROME;
elseif (ereg("Mozilla", $HUA) && ereg("Chrome", $HUA) && ereg("Edge", $HUA)) $nav = $NAV_EDGE;
elseif (ereg("Mozilla", $HUA) && !ereg("Chrome", $HUA)) $nav = $NAV_FIREFOX;
elseif (ereg("Konqueror", $HUA)) $nav = $NAV_KONQUEROR;
elseif (ereg("(Google|Slurp|Scooter)", $HUA) || eregi("(bot|Spider|Infoseek)", $HUA)) $nav = $BOT_GOOGLE;

if($nav=="Firefox" OR $nav=="Microsoft Edge" OR $nav=="Chrome"){*/
  ?>

  <h1>Index</h1>

  <h2>Carte générale</h2>
  <div id="map-categories" class="map-canvas"></div>

    <!--<h2>Graphes des budgets des villes</h2>
    <div id="chartContainer" style="height: 300px; width: 100%;">
    </div>!-->

    <h2>Villes<h2>
      <ul>
       <li><a href="Bordeaux.html">Bordeaux</a></li>
       <li><a href="Nantes.html">Nantes</a></li>
       <li><a href="Toulouse.html">Toulouse</a></li>

     </ul>
   </div>

 </body>

 </html>
