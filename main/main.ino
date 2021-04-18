//**********************************************
//* INCLUDES                                   *
//**********************************************
// Pixel Library
#include <Adafruit_NeoPixel.h>

// Dataset
// * run `php ./datagen.php` to 
//   generate a new dataset
#include "dataset.h"


//**********************************************
//* CONSTANTS / SETTINGS                       *
//**********************************************

// SPI Pin
#define PIN 6

// Change to 1 to toggle debug mode
#define DEBUG 0

// Brightness 
#define MAX_BRIGHTNESS 255 // No higher than 255
#define MIN_BRIGHTNESS -1  // No lower than 0

// Fade In
#define FADE_IN_STEP  3
#define FADE_IN_SPEED 50

// Fade Out
#define FADE_OUT_STEP  3
#define FADE_OUT_SPEED 40

// Intro fades
#define INTRO_FADE_IN_STEP   3
#define INTRO_FADE_IN_SPEED  50
#define INTRO_FADE_OUT_STEP  3
#define INTRO_FADE_OUT_SPEED 40

// Outro fades
#define OUTRO_FADE_IN_STEP   3
#define OUTRO_FADE_IN_SPEED  50
#define OUTRO_FADE_OUT_STEP  3
#define OUTRO_FADE_OUT_SPEED 40

// Stalls
#define INTERMISSION 400
#define CURTAIN_DOWN 2000

#define INTRO_INTERMISSION 400
#define INTRO_CURTAIN_DOWN 2000

#define OUTRO_INTERMISSION 400
#define OUTRO_CURTAIN_DOWN 2000

#define INTRO_PULSES         10
#define OUTRO_PULSES         2
#define PULSES_PER_DATAPOINT 5

#define ENDING_DELAY 10000

// Don't change
#define COLUMN_RACE   0
#define COLUMN_ELDER  1
#define COLUMN_PHILLY 2
#define COLUMN_MOTHER 3


//**********************************************
//* SIZE                                       *
//**********************************************

// Amount of people
// * Change this to add more people to the data
// * This must be changed in the datagen.php file as well
const int ROWS = 200; 

// Amount of data categories
// * Change this to add datapoints
// * This must be changed in the datagen.php file as well
const int COLS = 4;


//**********************************************
//* NEO Pixel Init                             *
//**********************************************

// CHECK HERE if the program and light strip are
// not communicating properly. The third 
// argument here is protocol config
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

// The default color
const int COLOR_DEFAULT = COLOR_Y;

// Datapoint colors
/* const int COLOR_RACE    = COLOR_R; */
const int COLOR_RACE    = COLOR_R;
const int COLOR_ELDER   = COLOR_O;
const int COLOR_PHILLY  = COLOR_B;
const int COLOR_MOTHER  = COLOR_I;


//**********************************************
//* PROGRAM VARIBLES                           *
//**********************************************
// Do Not Change
int i;
int ii;
int color;
int brightness;


//**********************************************
//* FUNCTIONS                                  *
//**********************************************

void debug(char *message) {
  if(DEBUG == 1)
    Serial.println(message);
}

void fadeIn(
  int *dataset, 
  int fade_in_step  = FADE_IN_STEP, 
  int fade_in_speed = FADE_IN_SPEED
) {
  for(
    brightness =  MIN_BRIGHTNESS; 
    brightness <  MAX_BRIGHTNESS; 
    brightness += fade_in_step
  ) {

    if(brightness > MAX_BRIGHTNESS)
      brightness = MAX_BRIGHTNESS;

    for(int i = 0; i < ROWS; i++) 
      strip.setPixelColor(i, dataset[i]);

    strip.setBrightness(brightness);

    strip.show();

    delay(fade_in_speed);
  }
}

void fadeOut(
  int *dataset,
  int fade_out_step  = FADE_OUT_STEP,
  int fade_out_speed = FADE_OUT_SPEED
) {
  for(
    brightness =  MAX_BRIGHTNESS; 
    brightness >  MIN_BRIGHTNESS; 
    brightness -= fade_out_step
  ) {
    if(brightness < MIN_BRIGHTNESS)
      brightness = MIN_BRIGHTNESS;

    for(int i = 0; i < ROWS; i++) 
      strip.setPixelColor(i, dataset[i]);

    strip.setBrightness(brightness);

    strip.show();

    delay(fade_out_speed);
  }
}

void intro() {
  int data[ROWS];

  for(int i = 0; i < ROWS; i++) 
    data[i] = COLOR_DEFAULT;

  for(int i = 0; i < INTRO_PULSES; i++) {
    fadeIn(
      data, 
      INTRO_FADE_IN_STEP, 
      INTRO_FADE_IN_SPEED
    );

    delay(INTRO_INTERMISSION);

    fadeOut(
      data, 
      INTRO_FADE_OUT_STEP, 
      INTRO_FADE_OUT_SPEED
    );

    delay(INTRO_CURTAIN_DOWN);
  }
}

void outro() {
  int data[ROWS];

  for(int i = 0; i < ROWS; i++) 
    data[i] = COLOR_DEFAULT;

  for(int i = 0; i < OUTRO_PULSES; i++) {
    fadeIn(
      data, 
      OUTRO_FADE_IN_STEP, 
      OUTRO_FADE_IN_SPEED
    );

    delay(OUTRO_INTERMISSION);

    fadeOut(
      data, 
      OUTRO_FADE_OUT_STEP, 
      OUTRO_FADE_OUT_SPEED
    );

    delay(OUTRO_CURTAIN_DOWN);
  }
}

void pulse(int *dataset) {
  for(int i = 0; i < PULSES_PER_DATAPOINT; i++) {
    fadeIn(dataset);

    delay(INTERMISSION);

    fadeOut(dataset);

    delay(CURTAIN_DOWN);
  }
}

void pulseColumn(int col_num = -1, int color = 0) {
  int column[ROWS];

  for(int i = 0; i < ROWS; i++) {
    if(col_num == -1 || dataset[i][col_num] == false)
      column[i] = COLOR_DEFAULT;
    else 
      column[i] = color;
  }

  pulse(column);
}

void pulseDefault() {
  pulseColumn( );
}

void pulseRace() {
  pulseColumn( 
    COLUMN_RACE,   
    COLOR_RACE 
  );
}

void pulseElder() {
  pulseColumn( 
    COLUMN_ELDER,  
    COLOR_ELDER  
  );
}

void pulsePhilly() {
  pulseColumn( 
    COLUMN_PHILLY, 
    COLOR_PHILLY 
  );
}

void pulseMother() {
  pulseColumn( 
    COLUMN_MOTHER, 
    COLOR_MOTHER
  );
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
  intro();

  pulseRace();

  pulseDefault();

  pulseElder();

  pulseDefault();

  pulsePhilly();

  pulseDefault();

  pulseMother();

  outro();

  delay(ENDING_DELAY);
}
