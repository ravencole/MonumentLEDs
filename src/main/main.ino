#include <Adafruit_NeoPixel.h>

//**********************************************
//* SPI                                        * 
//**********************************************
#define PIN 6


//**********************************************
//* SIZE                                       *
//**********************************************

// Amount of people
// * Change this to add more people to the data
const int ROWS = 60; 

// Amount of data categories
// * Change this to add datapoints
const int COLS = 6;


//**********************************************
//* NEO Pixel Init                             *
//**********************************************

Adafruit_NeoPixel strip = Adafruit_NeoPixel(ROWS, PIN, NEO_GRB + NEO_KHZ800);


//**********************************************
//* COLORS                                     *
//**********************************************
                              // R    G    B
const int COLOR_W = strip.Color( 255, 255, 255 );
const int COLOR_K = strip.Color(   0,   0,   0 );

const int COLOR_R = strip.Color( 255,   0,   0 );
const int COLOR_O = strip.Color( 255, 166,   0 );
const int COLOR_Y = strip.Color( 255, 255, 100 );
const int COLOR_G = strip.Color(   0, 255,   0 );
const int COLOR_B = strip.Color(   0,   0, 255 );
const int COLOR_I = strip.Color( 155,   0, 255 );
const int COLOR_V = strip.Color( 255,   0, 255 );


//**********************************************
//* COLORS -> COLUMNS                          *
//**********************************************

// Assign a color to a datapoint
const int na      = COLOR_Y;
const int race    = COLOR_R;
const int over_50 = COLOR_O;
const int teens   = COLOR_G;
const int phil    = COLOR_B;
const int mother  = COLOR_I;
const int passed  = COLOR_V;

int col_names[COLS] = {
  race,
  over_50,
  teens,
  phil,
  mother,
  passed
};


//**********************************************
//* VARIBLES                                   *
//**********************************************

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

// Iterators - Do not change
int color;
int i;
int ii;
int brightness;


//**********************************************
//* DATASET                                    *
//**********************************************

bool dataset[ROWS][COLS] = {
  // main set
  {  true, false,  true,  true, false,  true },
  { false,  true, false, false, false,  true },
  {  true, false, false,  true,  true,  true },
  {  true, false, false, false, false, false },
  {  true,  true, false, false, false, false },
  { false, false,  true, false,  true, false },
  { false, false,  true,  true,  true, false },
  {  true,  true,  true, false,  true, false },
  {  true, false, false, false, false, false },
  {  true, false,  true, false,  true,  true }, // 10

  {  true, false,  true,  true, false,  true },
  { false,  true, false, false, false,  true },
  {  true, false, false,  true,  true,  true },
  {  true, false, false, false, false, false },
  {  true,  true, false, false, false, false },
  { false, false,  true, false,  true, false },
  { false, false,  true,  true,  true, false },
  {  true,  true,  true, false,  true, false },
  {  true, false, false, false, false, false },
  {  true, false,  true, false,  true,  true }, // 20

  {  true, false,  true,  true, false,  true },
  { false,  true, false, false, false,  true },
  {  true, false, false,  true,  true,  true },
  {  true, false, false, false, false, false },
  {  true,  true, false, false, false, false },
  { false, false,  true, false,  true, false },
  { false, false,  true,  true,  true, false },
  {  true,  true,  true, false,  true, false },
  {  true, false, false, false, false, false },
  {  true, false,  true, false,  true,  true }, // 30

  {  true, false,  true,  true, false,  true },
  { false,  true, false, false, false,  true },
  {  true, false, false,  true,  true,  true },
  {  true, false, false, false, false, false },
  {  true,  true, false, false, false, false },
  { false, false,  true, false,  true, false },
  { false, false,  true,  true,  true, false },
  {  true,  true,  true, false,  true, false },
  {  true, false, false, false, false, false },
  {  true, false,  true, false,  true,  true }, // 40

  {  true, false,  true,  true, false,  true },
  { false,  true, false, false, false,  true },
  {  true, false, false,  true,  true,  true },
  {  true, false, false, false, false, false },
  {  true,  true, false, false, false, false },
  { false, false,  true, false,  true, false },
  { false, false,  true,  true,  true, false },
  {  true,  true,  true, false,  true, false },
  {  true, false, false, false, false, false },
  {  true, false,  true, false,  true,  true }, // 50

  {  true, false,  true,  true, false,  true },
  { false,  true, false, false, false,  true },
  {  true, false, false,  true,  true,  true },
  {  true, false, false, false, false, false },
  {  true,  true, false, false, false, false },
  { false, false,  true, false,  true, false },
  { false, false,  true,  true,  true, false },
  {  true,  true,  true, false,  true, false },
  {  true, false, false, false, false, false },
  {  true, false,  true, false,  true,  true }, // 60
};


//**********************************************
//* FUNCTIONS                                  *
//**********************************************

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

    char message[20];

    sprintf(message, "b - %d", brightness);

    Serial.println(message);

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

    char message[20];

    sprintf(message, "b - %d", brightness);

    Serial.println(message);

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

  Serial.begin(9600);

  while(! Serial) { ; }
}


//**********************************************
//* LOOP                                       *
//**********************************************

void loop() {
  for(i = 0; i < COLS; i++) {
    fadeIn();

    Serial.println("INTERMISSION");

    delay(INTERMISSION);

    fadeOut();

    Serial.println("CURTAIN DOWN");
    
    delay(CURTAIN_DOWN);
  }
}
