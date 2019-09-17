// config page

var Clay = require('pebble-clay');
var clayConfig = require('./config.js');
var clay = new Clay(clayConfig, null, { autoHandleEvents: false });

// constants

var messageKeys = require('message_keys');
const APIKEY = 'XXX';

var CLEAR_DAY = 0;
var CLEAR_NIGHT = 1;
var WINDY = 2;
var COLD = 3;
var PARTLY_CLOUDY_DAY = 4;
var PARTLY_CLOUDY_NIGHT = 5;
var HAZE = 6;
var CLOUD = 7;
var RAIN = 8;
var SNOW = 9;
var HAIL = 10;
var CLOUDY = 11;
var STORM = 12;
var FOG = 13;
var NA = 14;

// Weather condition codes pulled directly from OWM's icon list page.
// https://openweathermap.org/weather-conditions
var imageId = {
  '01d' : CLEAR_DAY,            //clear sky (day)
  '01n' : CLEAR_NIGHT,          //clear sky (night)
  '02d' : PARTLY_CLOUDY_DAY,    //few clouds (day)
  '02n' : PARTLY_CLOUDY_NIGHT,  //few clouds (night)
  '03d' : PARTLY_CLOUDY_DAY,    //scattered clouds (day)
  '03n' : PARTLY_CLOUDY_NIGHT,  //scattered clouds (night)
  '04d' : PARTLY_CLOUDY_DAY,    //broken clouds (day)
  '04n' : PARTLY_CLOUDY_NIGHT,  //broken clouds (night)
  '09d' : RAIN,                 //shower rain (day)
  '09n' : RAIN,                 //shower rain (night)
  '10d' : RAIN,                 //rain (day)
  '10n' : RAIN,                 //rain (night)
  '11d' : STORM,                //thunderstorm (day)
  '11n' : STORM,                //thunderstorm (night)
  '13d' : SNOW,                 //snow (day)
  '13n' : SNOW,                 //snow (night)
  '50d' : HAZE,                 //mist (day)
  '50n' : FOG,                  //mist (night)
  ''    : NA,                   //not available
};

var options = localStorage.getItem('clay-settings');
console.log('options: ' + options);
var options = JSON.parse(options);

// if no options are available, then the JS needs this minimal config to work
// the watch will have it's defaults set in the C code
if (options === null)
    options = {
        "use_gps" : true,
        "units" : "fahrenheit",
        "hideweather" : false,
        "city_name" : "",
        "zip_code" : ""
    };

function getWeatherFromLatLong(latitude, longitude) {
  getWeatherFromLocation('lat=' + latitude + '&lon=' + longitude);
}

function getWeatherFromLocation(location) {
  console.log("location: " + location);

  var celsius = (options.units == 'celsius');
  var query = encodeURI(location + "&appid=" + APIKEY + "&units=" + (celsius ? 'metric' : 'imperial'));

  var url = "https://api.openweathermap.org/data/2.5/weather?" + query;
  console.log("url: " + url);

  var req = new XMLHttpRequest();
  req.open('GET', url, true);
  req.timeout = 20000; // 20 sec
  req.onload = function(e) {
    if (req.readyState != 4) return;

    console.log("response: " + req.responseText);

    if (req.status != 200) return;

    var response;
    try {
      response = JSON.parse(req.responseText);
      if (response === null) return;
    } catch(err) {
      return;
    }

    if (response.main.temp === null) return;

    var weather = response.weather[0];

    var cityname = response.name;
    var temperature = Math.round(response.main.temp) + '\u00B0';
    var icon = imageId[weather.icon];

    console.log("title: Conditions for " + cityname);
    console.log("temp: " + temperature);
    console.log("icon: " + icon);

    Pebble.sendAppMessage({
      "icon" : icon,
      "temperature" : temperature
    });
  };
  req.send(null);
}

//var locationOptions = { "timeout": 30000, "maximumAge": 60000 };
var locationOptions = { "timeout": 15000, "maximumAge": 60000 };

function updateWeather() {
  if (options.hideweather === true) return;

  if (options.use_gps === true) {
    navigator.geolocation.getCurrentPosition(locationSuccess,
                                             locationError,
                                             locationOptions);
  } else if (options.zip_code != '') {
    getWeatherFromLocation('zip=' + options.zip_code);
  } else if (options.city_name != '') {
    getWeatherFromLocation('q=' + options.city_name);
  }
}

function locationSuccess(pos) {
  getWeatherFromLatLong(pos.coords.latitude,
                        pos.coords.longitude);
}

function locationError(err) {
  console.warn('location error (' + err.code + '): ' + err.message);

  Pebble.sendAppMessage({
    "icon": 14,
    "temperature":""
  });
}

Pebble.addEventListener('showConfiguration', function(e) {
    Pebble.openURL(clay.generateUrl());
});

Pebble.addEventListener('webviewclosed', function(e) {
    if (e && !e.response) {
        console.log('no options received');
        return;
    }

    var dict = clay.getSettings(e.response);

    console.log("new options dump: " + JSON.stringify(dict));

    // transform values to be backward compatible
    for (var key in dict) {
      if (dict.hasOwnProperty(key)) {
        // if the value is a string, simply parse it to int
        if (typeof dict[key] == "string") {
          dict[key] = parseInt(dict[key]);
        }
      }
    }
    console.log("transformed options dump: " + JSON.stringify(dict));

    // we have to delete NaN key, because some options do not have messageKey
    // those options are used only in this JS!
    delete dict.NaN; 

    // send new values to pebble
    Pebble.sendAppMessage(dict);

    // load the flattened edition of settings
    options = JSON.parse(localStorage.getItem('clay-settings'));

    updateWeather();
});

Pebble.addEventListener("ready", function(e) {
  //console.log("connect!" + e.ready);

  updateWeather();

  setInterval(function() {
    //console.log("timer fired");
    updateWeather();
  }, 60000); // 1 minute
  // }, 300000); // 5 minutes
  // }, 600000); // 10 minutes
  // }, 900000); // 15 minutes
  // }, 1200000); // 20 minutes
  // }, 1800000); // 30 minutes

  console.log(e.type);
});
