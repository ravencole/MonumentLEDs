#include <Adafruit_NeoPixel.h>


//**********************************************
//* CONSTANTS / SETTINGS                       *
//**********************************************

// SPI Pin
#define PIN 6

// Change to 1 to toggle debug mode
#define DEBUG 1

// Brightness 
#define MAX_BRIGHTNESS 255 // No higher than 255
#define MIN_BRIGHTNESS -1   // No lower than 0

// Fade In
#define FADE_IN_STEP  3
#define FADE_IN_SPEED 50

// Fade Out
#define FADE_OUT_STEP  3
#define FADE_OUT_SPEED 40

// Stalls
#define INTERMISSION 400
#define CURTAIN_DOWN 2000


//**********************************************
//* SIZE                                       *
//**********************************************

// Amount of people
// * Change this to add more people to the data
const int ROWS = 200; 

// Amount of data categories
// * Change this to add datapoints
const int COLS = 4;


//**********************************************
//* NEO Pixel Init                             *
//**********************************************

Adafruit_NeoPixel strip = Adafruit_NeoPixel(ROWS, PIN, NEO_GRB + NEO_KHZ800);


//**********************************************
//* COLORS                                     *
//**********************************************
// R    G    B
const int COLOR_W = strip.Color( 255, 255, 255 ); // White
const int COLOR_K = strip.Color(   0,   0,   0 ); // Black (off)

const int COLOR_R = strip.Color( 255,   0,   0 ); // Red
const int COLOR_O = strip.Color( 255, 166,   0 ); // Orange
const int COLOR_Y = strip.Color( 255, 255, 100 ); // Yellow
const int COLOR_G = strip.Color(   0, 255,   0 ); // Green
const int COLOR_B = strip.Color(   0,   0, 255 ); // Blue
const int COLOR_I = strip.Color( 155,   0, 255 ); // Indigo
const int COLOR_V = strip.Color( 255,   0, 255 ); // Violet


//**********************************************
//* COLORS -> COLUMNS                          *
//**********************************************

// Assign a color to a datapoint
const int na      = COLOR_Y;
const int race    = COLOR_R;
const int over_50 = COLOR_O;
const int phil    = COLOR_B;
const int mother  = COLOR_I;

int col_names[COLS] = {
  race,
  over_50,
  phil,
  mother
};


//**********************************************
//* DATASET                                    *
//**********************************************

bool dataset[ROWS][COLS] = {
  {false,true,false,true},
  {true,true,false,true},
  {false,false,false,true},
  {false,false,false,true},
  {true,false,true,true},
  {false,true,false,true},
  {false,false,true,true},
  {false,true,false,true},
  {true,true,false,true},
  {true,false,false,true},
  {false,true,false,true},
  {true,false,false,true},
  {false,true,false,true},
  {false,false,false,false},
  {false,false,false,false},
  {true,false,false,false},
  {false,false,true,true},
  {true,true,false,false},
  {false,false,false,true},
  {false,true,false,true},
  {false,false,false,false},
  {true,false,false,false},
  {false,true,true,false},
  {false,false,true,true},
  {true,true,false,true},
  {false,false,true,false},
  {true,false,true,false},
  {false,false,true,false},
  {true,false,true,true},
  {false,false,false,true},
  {true,true,false,true},
  {true,true,true,true},
  {true,true,false,true},
  {false,false,false,true},
  {true,false,false,true},
  {true,true,false,true},
  {false,false,false,true},
  {true,false,true,false},
  {true,false,false,true},
  {false,false,false,true},
  {false,false,true,true},
  {false,false,false,true},
  {false,false,false,false},
  {true,false,true,true},
  {false,true,false,true},
  {true,true,true,true},
  {false,true,false,false},
  {false,true,false,true},
  {true,false,true,true},
  {true,false,false,true},
  {false,true,true,true},
  {true,true,true,false},
  {true,true,false,true},
  {true,false,false,true},
  {true,true,false,false},
  {true,false,false,false},
  {false,false,true,true},
  {true,false,true,true},
  {true,false,false,false},
  {true,true,false,true},
  {false,true,true,false},
  {false,false,true,true},
  {false,false,false,true},
  {false,false,false,false},
  {true,false,false,true},
  {false,false,false,true},
  {false,false,false,true},
  {false,true,false,true},
  {true,true,true,true},
  {true,false,true,true},
  {true,false,false,false},
  {true,false,true,true},
  {true,false,true,true},
  {true,false,false,true},
  {true,false,true,true},
  {false,false,false,true},
  {true,true,true,false},
  {false,false,true,true},
  {false,false,false,true},
  {false,false,true,true},
  {false,false,false,true},
  {true,false,false,true},
  {false,false,false,true},
  {true,true,false,false},
  {true,true,false,true},
  {true,false,false,true},
  {false,false,false,true},
  {true,false,false,true},
  {false,false,false,true},
  {false,false,false,true},
  {true,false,false,true},
  {false,false,false,true},
  {false,false,false,true},
  {false,false,false,true},
  {false,false,false,true},
  {true,true,false,true},
  {false,false,false,true},
  {true,false,true,true},
  {true,false,true,true},
  {false,false,false,true},
  {false,true,false,false},
  {false,false,true,true},
  {false,false,false,true},
  {true,false,false,true},
  {false,true,false,true},
  {true,true,false,true},
  {true,true,false,true},
  {false,false,false,true},
  {true,false,false,true},
  {true,false,false,true},
  {false,true,true,true},
  {false,false,true,true},
  {true,false,false,true},
  {true,true,false,true},
  {true,false,false,true},
  {false,false,false,true},
  {false,false,false,false},
  {true,false,true,true},
  {false,false,true,true},
  {false,true,false,false},
  {false,true,false,true},
  {false,true,false,true},
  {false,false,false,true},
  {false,true,false,true},
  {false,false,true,true},
  {false,true,false,true},
  {true,false,false,true},
  {true,false,false,false},
  {false,false,false,true},
  {false,false,false,false},
  {true,false,true,true},
  {true,false,false,true},
  {true,false,false,true},
  {false,true,true,false},
  {true,false,false,true},
  {false,false,false,true},
  {true,false,false,false},
  {true,true,false,true},
  {false,false,false,false},
  {true,false,true,false},
  {true,false,false,false},
  {true,false,false,true},
  {true,true,false,true},
  {true,false,true,true},
  {false,false,false,true},
  {false,false,false,true},
  {true,false,false,true},
  {true,true,false,true},
  {true,false,false,true},
  {false,false,false,true},
  {true,true,false,false},
  {false,false,false,false},
  {true,false,false,true},
  {false,false,false,true},
  {false,true,false,true},
  {false,false,false,true},
  {true,true,false,true},
  {true,false,true,true},
  {false,false,false,true},
  {true,true,false,false},
  {true,true,false,true},
  {false,false,false,true},
  {true,true,false,true},
  {true,false,false,true},
  {true,false,false,true},
  {false,false,false,true},
  {false,true,false,true},
  {true,true,true,false},
  {true,false,false,true},
  {false,false,true,true},
  {false,false,true,true},
  {false,false,false,true},
  {true,false,true,true},
  {true,true,false,true},
  {true,false,true,true},
  {false,true,true,true},
  {true,false,true,true},
  {true,false,false,true},
  {false,false,false,false},
  {false,true,false,true},
  {true,true,true,false},
  {true,false,true,true},
  {false,true,false,true},
  {true,true,false,true},
  {true,false,true,true},
  {true,false,false,true},
  {true,false,false,true},
  {true,true,false,false},
  {false,false,false,true},
  {false,false,false,true},
  {true,true,false,true},
  {false,false,true,true},
  {false,false,false,true},
  {false,false,false,true},
  {false,false,false,true},
  {true,false,true,true},
  {false,false,false,false},
  {true,false,false,true},
  {false,false,false,true},
  {true,false,false,true}
};


//**********************************************
//* PROGRAM VARIBLES                           *
//**********************************************
// Do Not Change
int color;
int i;
int ii;
int brightness;


//**********************************************
//* FUNCTIONS                                  *
//**********************************************

void debug(char *message) {
  if(DEBUG == 1)
    Serial.println(message);
}

void fadeIn() {
  for(
    brightness =  MIN_BRIGHTNESS; 
    brightness <  MAX_BRIGHTNESS; 
    brightness += FADE_IN_STEP
   ) {
    for(
      ii = 0; 
      ii < ROWS; 
      ii++
    ) {
      if(dataset[ii][i] == 1) 
        color = col_names[i];
      else 
        color = na;

      strip.setPixelColor(ii, color);
    }

    strip.setBrightness(brightness);

    if(DEBUG == 1) { 
      char message[20];

      sprintf(message, "b - %d", brightness);

      debug(message);
    }

    strip.show();

    delay(FADE_IN_SPEED);
  }
}

void fadeOut() {
  for(
    brightness =  MAX_BRIGHTNESS; 
    brightness >  MIN_BRIGHTNESS; 
    brightness -= FADE_OUT_STEP
  ) {
    for(
      ii = 0; 
      ii < ROWS; 
      ii++
    ) {
      if(dataset[ii][i] == 1) 
        color = col_names[i];
      else 
        color = na;

      strip.setPixelColor(ii, color);
    }

    strip.setBrightness(brightness);

    if(DEBUG == 1) {
      char message[20];

      sprintf(message, "b - %d", brightness);

      debug(message);
    }

    strip.show();

    delay(FADE_OUT_SPEED);
  }
}


//**********************************************
//* SETUP                                      *
//**********************************************

void setup() {
  strip.begin();
  strip.show(); 

  if(DEBUG == 1) {
    Serial.begin(9600);

    while(! Serial) { ; }
  }
}


//**********************************************
//* LOOP                                       *
//**********************************************

void loop() {
  for(i = 0; i < COLS; i++) {
    fadeIn();

    debug("INTERMISSION");

    delay(INTERMISSION);

    fadeOut();

    debug("CURTAIN DOWN");
    
    delay(CURTAIN_DOWN);
  }
}
