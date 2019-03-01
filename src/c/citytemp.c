/*

Copyright (C) 2019 Max David

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

-------------------------------------------------------------------

*/

#include "pebble.h"
	
static AppSync        app;
static uint8_t        sync_buffer[256];

static const uint32_t WEATHER_ICONS[] = {
  RESOURCE_ID_CLEAR_DAY,
  RESOURCE_ID_CLEAR_NIGHT,
  RESOURCE_ID_WINDY,
  RESOURCE_ID_COLD,
  RESOURCE_ID_PARTLY_CLOUDY_DAY,
  RESOURCE_ID_PARTLY_CLOUDY_NIGHT,
  RESOURCE_ID_HAZE,
  RESOURCE_ID_CLOUD,
  RESOURCE_ID_RAIN,
  RESOURCE_ID_SNOW,
  RESOURCE_ID_HAIL,
  RESOURCE_ID_CLOUDY,
  RESOURCE_ID_STORM,
  RESOURCE_ID_FOG,
  RESOURCE_ID_NA,
};

// Setting values
static bool current_status;
static bool weather_status;
static bool secs_instead_of_ampm;
static bool bluetoothvibe_status;
static bool hourlyvibe_status;
static bool invert_format;
static bool textcol_white;
static bool startday_is_sunday; // not monday
static bool steps_status;
static enum backgroundKeys { CITY1 = 0, CITY2, CITY3, CITY4, CITY5, CITY6, CITY7, CITY8, CITY9, CITY10, CITY11, CITY12, CITY13, CITY14, CITY15, CITY16, CITY17, CITY18, CITY19, CITY20, CITY21, CITY22, CITY23, CITY24, CITY25, CITY26, CITY27, CITY28, CITY29, CITY30, CITY31, CITY32, CITY33, CITY34, CITY35, CITY36, CITY37, CITY38, CITY39, CITY40, CITY41, BGND_END = CITY41 } current_background;
static enum formatKeys { FORMAT_LARGE = 0, FORMAT_SMALL, FORMAT_NONE, FORMAT_END = FORMAT_NONE } current_format;
static enum languageKeys { LANG_EN = 0, LANG_NL, LANG_DE, LANG_FR, LANG_HR, LANG_ES, LANG_IT, LANG_NO, LANG_SW, LANG_FI, LANG_DA, LANG_TU, LANG_CA, LANG_SL, LANG_PO, LANG_HU, LANG_END = LANG_HU } current_language;

// Setting keys
enum settingKeys {
  SETTING_STATUS_KEY,
  SETTING_LANGUAGE_KEY,
  SETTING_FORMAT_KEY,
  SETTING_TEMPERATURE_KEY,
  SETTING_ICON_KEY,
  SETTING_WEATHERSTATUS_KEY,
  BLUETOOTHVIBE_KEY,
  HOURLYVIBE_KEY,
  SECS_KEY,
  BACKGROUND_KEY,
  SETTING_INVERT_KEY,
  SETTING_TEXTCOL_KEY,
  STARTDAY_KEY,
  STEPS_KEY,
};


Window *window;
Layer *window_layer;

BitmapLayer *layer_batt_img;
BitmapLayer *layer_conn_img;

GBitmap *img_battery_100;
GBitmap *img_battery_90;
GBitmap *img_battery_80;
GBitmap *img_battery_70;
GBitmap *img_battery_60;
GBitmap *img_battery_50;
GBitmap *img_battery_40;
GBitmap *img_battery_30;
GBitmap *img_battery_20;
GBitmap *img_battery_10;
GBitmap *img_battery_charge;

GBitmap *img_bt_connect;
GBitmap *img_bt_disconnect;

int charge_percent = 0;

BitmapLayer *icon_layer;
GBitmap *icon_bitmap = NULL;

TextLayer *temp_layer;
TextLayer *temp_layer2;
TextLayer *temp_layer3;
TextLayer *temp_layer4;

TextLayer *text_date_layer;
TextLayer *text_time_layer;
TextLayer *text_time_layer2;

static GFont          custom_48;
static GFont          custom_42;
static GFont          custom_37;
static GFont          custom_14;
static GFont          custom_20;

static int s_random = 40;
static int temp_random;

	  

void skyline_image() {		
		
	if (img_bt_connect) {
		gbitmap_destroy(img_bt_connect);
		img_bt_connect = NULL;
    }
	
	switch (current_background) {

		case 0:
#ifdef PBL_COLOR
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_DEFAULT);
#else
	    	img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_BLANK);
#endif
			break;
		case 1:
		
#ifdef PBL_COLOR
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_DEFAULT);
#else
	    	img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_BLANK);
#endif

		break;
		
		case 2:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_ATHENS);
			break;
		case 3:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_AUCKLAND);
			break;
		case 4:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_BANGKOK);
			break;
		
		
		case 5:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_BEIJING);
			break;
		case 6:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_BERLIN);
			break;
		case 7:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_BOGOTA);
			break;
		case 8:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_BRISBANE);
			break;
		case 9:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_CALGARY);
			break;
		case 10:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_CANBERRA);
			break;
		
		case 11:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_CHICAGO);
			break;
		case 12:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_DELHI);
			break;
		case 13:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_DUBAI);
			break;
		case 14:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_DUBLIN);
			break;
		case 15:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_HONGKONG);
			break;
		case 16:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_LONDON);
			break;
		case 17:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_LOSANGELES);
			break;
		case 18:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_MADRID);
			break;
		case 19:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_MELBOURNE);
			break;
		case 20:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_MILAN);
			break;
		
		case 21:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_MOSCOW);
			break;
		case 22:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_NEWYORK);
			break;
		case 23:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_PARIS);
			break;
		case 24:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_PORTLAND);
			break;
		
		case 25:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_RIO);
			break;
		case 26:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_ROME);
			break;
		case 27:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_SANFRANCISCO);
			break;
		case 28:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_SEATTLE);
			break;
		
		case 29:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_SEOUL);
			break;
		case 30:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_SHANGHAI);
			break;
		case 31:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_SINGAPORE);
			break;
		case 32:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_STPETERSBERG);
			break;
		case 33:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_SYDNEY);
			break;
		
		case 34:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_TOKYO);
			break;
		case 35:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_TORONTO);
			break;
		case 36:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_VANCOUVER);
			break;
		case 37:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_WASHINGTONDC);
			break;
		case 38:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_WELLINGTON);
			break;
		
		case 39:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_BISHKEK);
			break;
		case 40:
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_ROTTERDAM);
			break;		
	
		
/*
ottawa
istanbul
miami
montreal
mumbai
cairo

munich
vienna
cape town
florence
sofia
prague
oslo
venice

johannesburg
helsinki
amsterdam
glasgow
brussels
venice
barcelona
jakarta
taipei
*/
    }
		
	   if (img_bt_connect != NULL) {
		bitmap_layer_set_bitmap(layer_conn_img, img_bt_connect);
		layer_set_hidden(bitmap_layer_get_layer(layer_conn_img), false);
		layer_mark_dirty(bitmap_layer_get_layer(layer_conn_img));
      }
}

void update_time(struct tm *tick_time) {


  // Need to be static because they're used by the system later.
  static char date_text[] = "Xxxxxxxxx, 00 xxxxxxxxx";
  static char time_text[] = "00:00";
  static int yday = -1;

  char *time_format;

  // Only update the date when it has changed.
  if (yday != tick_time->tm_yday) {

	strftime(date_text, sizeof(date_text), "%A, %e %b", tick_time);
    text_layer_set_text(text_date_layer, date_text);	
	

  }

  if (clock_is_24h_style()) {
    time_format = "%R";
  } else {
    time_format = "%I:%M";
  }
  strftime(time_text, sizeof(time_text), time_format, tick_time);

  // Handle lack of non-padded hour format string for twelve hour clock.
  if (!clock_is_24h_style() && (time_text[0] == '0')) {
    text_layer_set_text(text_time_layer, time_text + 1);
    text_layer_set_text(text_time_layer2, time_text + 1);
  } else {
    text_layer_set_text(text_time_layer, time_text);
    text_layer_set_text(text_time_layer2, time_text);
  }	
	
}

void handle_minute_tick(struct tm *tick_time, TimeUnits units_changed) {
	
    update_time(tick_time);

	if (units_changed & MINUTE_UNIT) {

		if (current_background == 1) {
	
		if(s_random == 40){
			s_random = 0;
		} else {

			temp_random = rand() % 39;

			while(temp_random == s_random){
			    temp_random = rand() % 39;
		    }

		    s_random = temp_random;

	    if (img_bt_connect) {
		gbitmap_destroy(img_bt_connect);

		img_bt_connect = NULL;

    }

		    if(s_random == 0){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_ATHENS);
			} else if(s_random == 1){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_AUCKLAND);		
			} else if(s_random == 2){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_BEIJING);
			} else if(s_random == 3){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_BERLIN);
			} else if(s_random == 4){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_BRISBANE);
			} else if(s_random == 5){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_CHICAGO);
			} else if(s_random == 6){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_DELHI);
			} else if(s_random == 7){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_DUBAI);
			} else if(s_random == 8){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_DUBLIN);
			} else if(s_random == 9){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_HONGKONG);
			} else if(s_random == 10){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_LONDON);
			} else if(s_random == 11){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_LOSANGELES);
			} else if(s_random == 12){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_MADRID);
			} else if(s_random == 13){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_MELBOURNE);
			} else if(s_random == 14){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_MOSCOW);
			} else if(s_random == 15){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_NEWYORK);
			} else if(s_random == 16){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_PARIS);
			} else if(s_random == 17){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_RIO);
			} else if(s_random == 18){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_ROME);
			} else if(s_random == 19){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_SANFRANCISCO);
			} else if(s_random == 20){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_SEOUL);
			} else if(s_random == 21){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_SHANGHAI);
			} else if(s_random == 22){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_SINGAPORE);
			} else if(s_random == 23){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_SYDNEY);
			} else if(s_random == 24){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_TOKYO);
			} else if(s_random == 25){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_TORONTO);
			} else if(s_random == 26){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_VANCOUVER);
			} else if(s_random == 27){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_WASHINGTONDC);
			} else if(s_random == 28){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_WELLINGTON);
			} else if(s_random == 29){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_BANGKOK);
			} else if(s_random == 30){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_CANBERRA);
			} else if(s_random == 31){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_PORTLAND);
			} else if(s_random == 32){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_MILAN);
			} else if(s_random == 33){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_BOGOTA);
			} else if(s_random == 34){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_CALGARY);
			} else if(s_random == 35){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_SEATTLE);
			}  else if(s_random == 36){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_STPETERSBERG);
			} else if(s_random == 37){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_ROTTERDAM);
			} else if(s_random == 38){
			img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_BISHKEK);
			}
		
           if (img_bt_connect != NULL) {
		   bitmap_layer_set_bitmap(layer_conn_img, img_bt_connect);
		   layer_set_hidden(bitmap_layer_get_layer(layer_conn_img), false);
		   layer_mark_dirty(bitmap_layer_get_layer(layer_conn_img));
           }	
			
			}
		}
	}		  
	
}

/*
  Handle update in settings
*/

// validate upper limit (can not be higher, than 1)
// mind: value is unsigned, so it can not be less than 0
#define VALIDATE_BOOL(value) if (value > 1) return;

#define VALIDATE_MAXIMUM(name, value, max) \
if (value > (uint8_t)max) \
{ \
    APP_LOG( APP_LOG_LEVEL_ERROR, "%s boundary error: %u is not less or equal than %u", name, value, max ); \
    return; \
}

static void tuple_changed_callback( const uint32_t key, const Tuple* tuple_new, const Tuple* tuple_old, void* context )
{
  uint8_t value = tuple_new->value->uint8;

  // APP_LOG( APP_LOG_LEVEL_DEBUG, "tuple_changed_callback: %lu", key );

  switch ( key )
  {
    case SETTING_STATUS_KEY:
      VALIDATE_BOOL(value)

      persist_write_int( SETTING_STATUS_KEY, value );
      current_status = value;

      break;

    case SETTING_LANGUAGE_KEY:
      VALIDATE_MAXIMUM("SETTING_LANGUAGE_KEY", value, LANG_END)

      persist_write_int( SETTING_LANGUAGE_KEY, value );
      current_language = value;
      break;

    case SETTING_FORMAT_KEY:
      VALIDATE_MAXIMUM("SETTING_FORMAT_KEY", value, FORMAT_END)

      persist_write_int( SETTING_FORMAT_KEY, value );
      current_format = value;

	switch (current_format) {
  
	case 0:  //large
		 layer_set_hidden(text_layer_get_layer(temp_layer), false); 
		 layer_set_hidden(text_layer_get_layer(temp_layer2), false); 
		 layer_set_hidden(text_layer_get_layer(temp_layer3), true); 
		 layer_set_hidden(text_layer_get_layer(temp_layer4), true); 
	break;
		  
	case 1:  //small
		 layer_set_hidden(text_layer_get_layer(temp_layer), true); 
		 layer_set_hidden(text_layer_get_layer(temp_layer2), true); 
		 layer_set_hidden(text_layer_get_layer(temp_layer3), false); 
		 layer_set_hidden(text_layer_get_layer(temp_layer4), false); 
	break;

	case 2:  //none
		 layer_set_hidden(text_layer_get_layer(temp_layer), true); 
		 layer_set_hidden(text_layer_get_layer(temp_layer2), true); 
		 layer_set_hidden(text_layer_get_layer(temp_layer3), true); 
		 layer_set_hidden(text_layer_get_layer(temp_layer4), true); 
	break;
  }
	  break;

    case BACKGROUND_KEY:
      VALIDATE_MAXIMUM("BACKGROUND", value, BGND_END)

      persist_write_int( BACKGROUND_KEY, value );
      current_background = value;

	  skyline_image();

      break;

    case SETTING_ICON_KEY:
      VALIDATE_MAXIMUM("SETTING_ICON_KEY", value, ARRAY_LENGTH(WEATHER_ICONS))

      if (icon_bitmap) {
        gbitmap_destroy(icon_bitmap);
      }
      icon_bitmap = gbitmap_create_with_resource(WEATHER_ICONS[tuple_new->value->uint8]);

      bitmap_layer_set_bitmap(icon_layer, icon_bitmap);
      break;

    case SETTING_TEMPERATURE_KEY:
      text_layer_set_text(temp_layer, tuple_new->value->cstring);
      text_layer_set_text(temp_layer2, tuple_new->value->cstring);
      text_layer_set_text(temp_layer3, tuple_new->value->cstring);
      text_layer_set_text(temp_layer4, tuple_new->value->cstring);
	  break;

    case SETTING_WEATHERSTATUS_KEY:
      VALIDATE_BOOL(value)

      persist_write_int( SETTING_WEATHERSTATUS_KEY, value );
      weather_status = value;
 
      break;

    case BLUETOOTHVIBE_KEY:
      VALIDATE_BOOL(value)

      persist_write_int( BLUETOOTHVIBE_KEY, value );
      bluetoothvibe_status = value;
      break;

    case HOURLYVIBE_KEY:
      VALIDATE_BOOL(value)

      persist_write_int( HOURLYVIBE_KEY, value );
      hourlyvibe_status = value;
      break;

    case SECS_KEY:
      VALIDATE_BOOL(value)

      persist_write_int( SECS_KEY, value );
      secs_instead_of_ampm = value;
	  
	  if (secs_instead_of_ampm) {
		  
		 		layer_set_hidden(text_layer_get_layer(text_time_layer), true); 
//		 		layer_set_hidden(bitmap_layer_get_layer(icon_layer), true); 
		 		layer_set_hidden(text_layer_get_layer(text_time_layer2), false); 
#ifdef PBL_PLATFORM_CHALK
		      layer_set_frame( text_layer_get_layer( text_date_layer ), GRect(0, 65, 180, 18 ) );
#else
		      layer_set_frame( text_layer_get_layer( text_date_layer ), GRect(0, 6, 144, 18 ) );		  
#endif
	

	  } else {
		  		layer_set_hidden(text_layer_get_layer(text_time_layer2), true); 
//		 		layer_set_hidden(bitmap_layer_get_layer(icon_layer), false); 
				layer_set_hidden(text_layer_get_layer(text_time_layer), false); 
#ifdef PBL_PLATFORM_CHALK
		      layer_set_frame( text_layer_get_layer( text_date_layer ), GRect(0, 49, 180, 18 ) );
#else
		      layer_set_frame( text_layer_get_layer( text_date_layer ), GRect(0, 6, 144, 18 ) );		  
#endif		  
	  }

      break;

    case SETTING_INVERT_KEY:
      VALIDATE_BOOL(value)

      persist_write_int( SETTING_INVERT_KEY, value );
      invert_format = value;

      break;

    case SETTING_TEXTCOL_KEY:
      VALIDATE_BOOL(value)

      persist_write_int( SETTING_TEXTCOL_KEY, value );
      textcol_white = value;

      break;

    case STARTDAY_KEY:
      VALIDATE_BOOL(value)

      persist_write_int( STARTDAY_KEY, value );
      startday_is_sunday = value;

      break;

    case STEPS_KEY:
      VALIDATE_BOOL(value)

      persist_write_int( STEPS_KEY, value );
      steps_status = value;
	  
      break;

    default:
      APP_LOG(APP_LOG_LEVEL_INFO, "unknown tuple key: %lu", key);
  }

  // Refresh display
  time_t now = time( NULL );
  struct tm *tick_time = localtime( &now );

  // Force update to avoid a blank screen at startup of the watchface
  handle_minute_tick(tick_time, 0);
}

/*
  Handle errors
*/
static void app_error_callback( DictionaryResult dict_error, AppMessageResult app_message_error, void* context ) {
  APP_LOG( APP_LOG_LEVEL_ERROR, "app error: %d", app_message_error );
//  vibes_double_pulse();
}

void handle_battery(BatteryChargeState charge_state) {

    if (charge_state.is_charging) {
        bitmap_layer_set_bitmap(layer_batt_img, img_battery_charge);

    } else {
        if (charge_state.charge_percent <= 10) {
            bitmap_layer_set_bitmap(layer_batt_img, img_battery_10);
        } else if (charge_state.charge_percent <= 20) {
            bitmap_layer_set_bitmap(layer_batt_img, img_battery_20);
		} else if (charge_state.charge_percent <= 30) {
            bitmap_layer_set_bitmap(layer_batt_img, img_battery_30);
		} else if (charge_state.charge_percent <= 40) {
            bitmap_layer_set_bitmap(layer_batt_img, img_battery_40);
		} else if (charge_state.charge_percent <= 50) {
            bitmap_layer_set_bitmap(layer_batt_img, img_battery_50);
        } else if (charge_state.charge_percent <= 60) {
            bitmap_layer_set_bitmap(layer_batt_img, img_battery_60);
		} else if (charge_state.charge_percent <= 70) {
            bitmap_layer_set_bitmap(layer_batt_img, img_battery_70);
		} else if (charge_state.charge_percent <= 80) {
            bitmap_layer_set_bitmap(layer_batt_img, img_battery_80);
		} else if (charge_state.charge_percent <= 90) {
            bitmap_layer_set_bitmap(layer_batt_img, img_battery_90);
		} else if (charge_state.charge_percent <= 99) {
            bitmap_layer_set_bitmap(layer_batt_img, img_battery_100);
		} else {
            bitmap_layer_set_bitmap(layer_batt_img, img_battery_100);
        }      						
    }
    charge_percent = charge_state.charge_percent;
}

void handle_bluetooth(bool connected) {
    if (!connected) {
		
		 layer_set_hidden(text_layer_get_layer(temp_layer), true); 
		 layer_set_hidden(text_layer_get_layer(temp_layer2), true); 
		 layer_set_hidden(text_layer_get_layer(temp_layer3), true); 
		 layer_set_hidden(text_layer_get_layer(temp_layer4), true); 

		layer_set_hidden(bitmap_layer_get_layer(icon_layer), true); 

        bitmap_layer_set_bitmap(layer_conn_img, img_bt_disconnect);
		vibes_long_pulse();

    } else {
		
		layer_set_hidden(bitmap_layer_get_layer(icon_layer), false); 
        bitmap_layer_set_bitmap(layer_conn_img, img_bt_connect);
    }
}

void force_update(void) {
	
	
    handle_battery(battery_state_service_peek());
    handle_bluetooth(bluetooth_connection_service_peek());
}


void handle_init(void) {
	
  // international support
  setlocale(LC_ALL, "");
	
  window = window_create();
  window_stack_push(window, true /* Animated */);
  window_set_background_color(window, GColorBlack);

  // Read persistent data

#define GET_PERSIST_VALUE_OR_DEFAULT(key, def) \
  persist_exists( key ) ? persist_read_int( key ) : def

  // Read watchface settings from persistent data or use default values
  current_status       = GET_PERSIST_VALUE_OR_DEFAULT( SETTING_STATUS_KEY,        true);
  weather_status       = GET_PERSIST_VALUE_OR_DEFAULT( SETTING_WEATHERSTATUS_KEY, true);
  current_language     = GET_PERSIST_VALUE_OR_DEFAULT( SETTING_LANGUAGE_KEY,      LANG_EN);
  current_format       = GET_PERSIST_VALUE_OR_DEFAULT( SETTING_FORMAT_KEY,        FORMAT_LARGE);
  current_background   = GET_PERSIST_VALUE_OR_DEFAULT( BACKGROUND_KEY,            CITY1);
  bluetoothvibe_status = GET_PERSIST_VALUE_OR_DEFAULT( BLUETOOTHVIBE_KEY,         true);
  hourlyvibe_status    = GET_PERSIST_VALUE_OR_DEFAULT( HOURLYVIBE_KEY ,           false);
  secs_instead_of_ampm = GET_PERSIST_VALUE_OR_DEFAULT( SECS_KEY,                  true);
  invert_format        = GET_PERSIST_VALUE_OR_DEFAULT( SETTING_INVERT_KEY,        false);
  textcol_white        = GET_PERSIST_VALUE_OR_DEFAULT( SETTING_TEXTCOL_KEY,       false);
  startday_is_sunday   = GET_PERSIST_VALUE_OR_DEFAULT( STARTDAY_KEY,              true);
  steps_status         = GET_PERSIST_VALUE_OR_DEFAULT( STEPS_KEY,                 false);

	 // Initial settings
  Tuplet initial_values[] = { TupletInteger( SETTING_STATUS_KEY, current_status )
                            , TupletInteger( SETTING_WEATHERSTATUS_KEY, weather_status )
                            , TupletInteger( SETTING_LANGUAGE_KEY, current_language )
                            , TupletInteger( SETTING_FORMAT_KEY, current_format )
                            , TupletInteger( BACKGROUND_KEY, current_background )
                            , TupletInteger( BLUETOOTHVIBE_KEY, bluetoothvibe_status )
                            , TupletInteger( HOURLYVIBE_KEY, hourlyvibe_status )
                            , TupletInteger( SECS_KEY, secs_instead_of_ampm )
                            , TupletInteger( SETTING_ICON_KEY, (uint8_t) 14)
                            , TupletCString( SETTING_TEMPERATURE_KEY, "")
                            , TupletInteger( SETTING_INVERT_KEY, invert_format)
                            , TupletInteger( SETTING_TEXTCOL_KEY, textcol_white)
                            , TupletInteger( STARTDAY_KEY, startday_is_sunday )
                            , TupletInteger( STEPS_KEY, steps_status )
                            };

  // Open AppMessage to transfers
  app_message_open( 256, 256 );

  // Initialize AppSync
  app_sync_init( &app, sync_buffer
               , sizeof( sync_buffer )
               , initial_values
               , ARRAY_LENGTH( initial_values )
               , tuple_changed_callback
               , app_error_callback
               , NULL
               );

	
	
  Layer *window_layer = window_get_root_layer(window);	
  GRect bounds = layer_get_bounds(window_layer);
	
// resources
#ifdef PBL_COLOR
	img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_DEFAULT);
#else
	img_bt_connect = gbitmap_create_with_resource(RESOURCE_ID_BLANK);
#endif
	img_bt_disconnect  = gbitmap_create_with_resource(RESOURCE_ID_DEFAULT);
	
    img_battery_100   = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_100);
    img_battery_90   = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_90);
    img_battery_80   = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_80);
    img_battery_70   = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_70);
    img_battery_60   = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_60);
    img_battery_50   = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_50);
    img_battery_40   = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_40);
    img_battery_30   = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_30);
    img_battery_20    = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_20);
    img_battery_10    = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_10);
    img_battery_charge = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT_CHARGING);

  // Load fonts
  custom_48  = fonts_load_custom_font( resource_get_handle( RESOURCE_ID_FONT_CUSTOM_48 ) );
  custom_42  = fonts_load_custom_font( resource_get_handle( RESOURCE_ID_FONT_CUSTOM_42 ) );
  custom_37  = fonts_load_custom_font( resource_get_handle( RESOURCE_ID_FONT_CUSTOM_37 ) );
  custom_14  = fonts_load_custom_font( resource_get_handle( RESOURCE_ID_FONT_CUSTOM_14 ) );
  custom_20  = fonts_load_custom_font( resource_get_handle( RESOURCE_ID_FONT_CUSTOM_20 ) );
 
  // active layers   

	
#ifdef PBL_PLATFORM_CHALK
  text_time_layer = text_layer_create(GRect(0, 11, bounds.size.w, 52));
  text_layer_set_text_color(text_time_layer, GColorWhite);
  text_layer_set_background_color(text_time_layer, GColorClear);
  text_layer_set_font(text_time_layer, custom_37);
  text_layer_set_text_alignment(text_time_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_time_layer));	
#endif	
	
	
#ifdef PBL_RECT
  text_time_layer = text_layer_create(GRect(0, 14, bounds.size.w, 52));
  text_layer_set_text_color(text_time_layer, GColorWhite);
  text_layer_set_background_color(text_time_layer, GColorClear);
  text_layer_set_font(text_time_layer, custom_37);
  text_layer_set_text_alignment(text_time_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_time_layer));
#endif	  
	  
	  
#ifdef PBL_RECT
  layer_batt_img  = bitmap_layer_create(GRect(0, 2, bounds.size.w, 4));
  bitmap_layer_set_bitmap(layer_batt_img, img_battery_100);
  layer_add_child(window_layer, bitmap_layer_get_layer(layer_batt_img));	
#endif
	
	
	
#ifdef PBL_PLATFORM_CHALK
	icon_layer = bitmap_layer_create(GRect(0, 63, bounds.size.w, 117));
#elif PBL_PLATFORM_BASALT
	icon_layer = bitmap_layer_create(GRect(0, 51, bounds.size.w, 117));
#else
	icon_layer = bitmap_layer_create(GRect(0, 51, bounds.size.w, 60));
#endif
  layer_add_child(window_layer, bitmap_layer_get_layer(icon_layer));	
	
	
#ifdef PBL_PLATFORM_CHALK
  text_time_layer2 = text_layer_create(GRect(0, 15, bounds.size.w, 52));
  text_layer_set_background_color(text_time_layer2, GColorBlack);
  text_layer_set_font(text_time_layer2, custom_48);
  text_layer_set_text_color(text_time_layer2, GColorWhite);
  text_layer_set_text_alignment(text_time_layer2, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_time_layer2));
#endif
	
#ifdef PBL_PLATFORM_CHALK
  layer_batt_img  = bitmap_layer_create(GRect(51, 6, 77, 12));
  bitmap_layer_set_bitmap(layer_batt_img, img_battery_100);
  layer_add_child(window_layer, bitmap_layer_get_layer(layer_batt_img));
#endif
	
#ifdef PBL_RECT
  text_time_layer2 = text_layer_create(GRect(0, 15, bounds.size.w, 55));
  text_layer_set_background_color(text_time_layer2, GColorBlack);
  text_layer_set_font(text_time_layer2, custom_48);
  text_layer_set_text_color(text_time_layer2, GColorWhite);
  text_layer_set_text_alignment(text_time_layer2, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_time_layer2));
#endif	

	
#ifdef PBL_RECT
  text_date_layer = text_layer_create(GRect(0, 5, bounds.size.w, 20));
  text_layer_set_text_color(text_date_layer, GColorWhite);
  text_layer_set_background_color(text_date_layer, GColorClear);
  text_layer_set_font(text_date_layer, custom_14);
  text_layer_set_text_alignment(text_date_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_date_layer));
#endif
	
#ifdef PBL_PLATFORM_CHALK
  text_date_layer = text_layer_create(GRect(0, 49, bounds.size.w, 16));
  text_layer_set_text_color(text_date_layer, GColorWhite);
  text_layer_set_background_color(text_date_layer, GColorBlack);
  text_layer_set_font(text_date_layer, custom_14);
  text_layer_set_text_alignment(text_date_layer, GTextAlignmentCenter);
//  text_layer_set_text(text_date_layer, "Wednesday, 30 Nov");
  layer_add_child(window_layer, text_layer_get_layer(text_date_layer));
#endif
	
	
	
#if PBL_PLATFORM_CHALK
  layer_conn_img  = bitmap_layer_create(GRect(0, 120, bounds.size.w, 60));
#elif PBL_PLATFORM_EMERY
  layer_conn_img  = bitmap_layer_create(GRect(0, 138, bounds.size.w, 90));
#else
  layer_conn_img  = bitmap_layer_create(GRect(0, 111, bounds.size.w, 57));
#endif
  bitmap_layer_set_bitmap(layer_conn_img, img_bt_connect);
	GCompOp compositing_mode = GCompOpSet;
    bitmap_layer_set_compositing_mode(layer_conn_img, compositing_mode);
  layer_add_child(window_layer, bitmap_layer_get_layer(layer_conn_img)); 

	
#ifdef PBL_PLATFORM_CHALK
  temp_layer2 = text_layer_create(GRect(12, 91, 180, 50));
#else
  temp_layer2 = text_layer_create(GRect(12, 78, bounds.size.w, 50));
#endif
  text_layer_set_text_color(temp_layer2, GColorWhite);
  text_layer_set_background_color(temp_layer2, GColorClear);
  text_layer_set_font(temp_layer2, custom_42);
  text_layer_set_text_alignment(temp_layer2, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(temp_layer2));
	
#ifdef PBL_PLATFORM_CHALK
	temp_layer = text_layer_create(GRect(10, 90, 180, 50));
#else
	temp_layer = text_layer_create(GRect(10, 77, bounds.size.w, 50));
#endif
	text_layer_set_text_color(temp_layer, GColorBlack);
  text_layer_set_background_color(temp_layer, GColorClear);
  text_layer_set_font(temp_layer, custom_42);
	text_layer_set_text_alignment(temp_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(temp_layer));

#ifdef PBL_PLATFORM_CHALK
	temp_layer3 = text_layer_create(GRect(121, 103, 35, 20));
#else
	temp_layer3 = text_layer_create(GRect(101, 93, 35, 20));
#endif
  text_layer_set_text_color(temp_layer3, GColorBlack);
  text_layer_set_background_color(temp_layer3, GColorClear);
  text_layer_set_font(temp_layer3, custom_20);
  text_layer_set_text_alignment(temp_layer3, GTextAlignmentRight);
  layer_add_child(window_layer, text_layer_get_layer(temp_layer3));
	
#ifdef PBL_PLATFORM_CHALK
	temp_layer4 = text_layer_create(GRect(120, 102, 36, 24));
#else
	temp_layer4 = text_layer_create(GRect(100, 92, 36, 24));
#endif
  text_layer_set_text_color(temp_layer4, GColorBlack);
  text_layer_set_background_color(temp_layer4, GColorClear);
  text_layer_set_font(temp_layer4, custom_20);
  text_layer_set_text_alignment(temp_layer4, GTextAlignmentRight);
  layer_add_child(window_layer, text_layer_get_layer(temp_layer4));	
	
	
	// Subscribe to notifications
  tick_timer_service_subscribe(MINUTE_UNIT, handle_minute_tick);

  // handlers
  battery_state_service_subscribe(&handle_battery);
  bluetooth_connection_service_subscribe(&handle_bluetooth);
	
  // draw first frame
  force_update();
  
}

void handle_deinit(void) {
	
  app_sync_deinit(&app);

  battery_state_service_unsubscribe();
  bluetooth_connection_service_unsubscribe();
  tick_timer_service_unsubscribe();

  text_layer_destroy( text_time_layer );
  text_layer_destroy( text_time_layer2 );
  text_layer_destroy( text_date_layer );
	
  text_layer_destroy( temp_layer );
  text_layer_destroy( temp_layer2 );
  text_layer_destroy( temp_layer3 );
  text_layer_destroy( temp_layer4 );
	
  layer_remove_from_parent(bitmap_layer_get_layer(icon_layer));
  bitmap_layer_destroy(icon_layer);
  gbitmap_destroy(icon_bitmap);
  icon_bitmap = NULL;
	
  layer_remove_from_parent(bitmap_layer_get_layer(layer_conn_img));
  bitmap_layer_destroy(layer_conn_img);
  gbitmap_destroy(img_bt_connect);
  gbitmap_destroy(img_bt_disconnect);
  img_bt_connect = NULL;
  img_bt_disconnect = NULL;
	
  layer_remove_from_parent(bitmap_layer_get_layer(layer_batt_img));
  bitmap_layer_destroy(layer_batt_img);
	
  gbitmap_destroy(img_battery_100);
  gbitmap_destroy(img_battery_90);
  gbitmap_destroy(img_battery_80);
  gbitmap_destroy(img_battery_70);
  gbitmap_destroy(img_battery_60);
  gbitmap_destroy(img_battery_50);
  gbitmap_destroy(img_battery_40);
  gbitmap_destroy(img_battery_30);
  gbitmap_destroy(img_battery_20);
  gbitmap_destroy(img_battery_10);
  gbitmap_destroy(img_battery_charge);	

  fonts_unload_custom_font( custom_48 );
  fonts_unload_custom_font( custom_42 );
  fonts_unload_custom_font( custom_37 );
  fonts_unload_custom_font( custom_14 );
  fonts_unload_custom_font( custom_20 );
	
  layer_remove_from_parent(window_layer);
  layer_destroy(window_layer);
	
  window_destroy(window);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
