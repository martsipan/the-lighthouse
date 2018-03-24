/*
               .
             \ _ /     .-='-. _db_      .--==-,
           -= (_) =-  (_  (  _IIII_   _(    )  `.
             /   \      (    |" " |-.(  ` ,_  `  )
               '         '-._HHHHHH  `)---' `'--'    =.=
                             |.   |--`                    =.=
                             |    |      =.=
                   _H___,=====;___|           =.=
                n_/____/____/``\__\
               /__|:: :|. .|:::|::|                  =.=
            _%&|__&%_"_|_"_|_ H|__|__
           jgs`";;;;`";;;;'";;'"';;;;``;;-.
           .  ' `";;'  `;;;  `;'   `;  .`' `\
           . '  .  `' .  `';.    '   .   .  |^-`^~_^^~``-^^_~^^-`^~

 * "The lighthouse" - Evening LED Patch
 * 24/03/18 @ Nida, Lithuania
 * 
 */
 
#include <FastLED.h>

#define NUM_LEDS 290
#define DATA_PIN 6

#define CYCLE_DURATION 1000

#define COLOR_START 140
#define COLOR_END 210

#define BRIGHTNESS_MIN 180
#define BRIGHTNESS_MAX 210

CRGBArray<NUM_LEDS> leds;

int currentCycle;
int currentDirection;
int currentColor;

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

  // Set initial values
  currentDirection = 0;
  currentCycle = 0;
  currentColor = COLOR_START;

  // Reset
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

void loop() {
  // Adjust direction and color
  if (currentDirection == 0) {
    currentColor += 1;

    if (currentColor >= COLOR_END) {
      currentDirection = 1;
    }
  } else {
    currentColor -= 1;

    if (currentColor <= COLOR_START) {
       currentDirection = 0;
    }
  }

  // Change color slightly
  fill_solid(
    leds,
    NUM_LEDS,
    CHSV(
      currentColor,
      255,
      BRIGHTNESS_MIN + scale8(
        sin8(currentCycle % 255),
        (BRIGHTNESS_MAX - BRIGHTNESS_MIN)
      )
    )
  );

  currentCycle += 1;

  // Update
  FastLED.delay(CYCLE_DURATION);
  FastLED.show();
}
           
