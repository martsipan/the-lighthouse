/*
               .                .                                 .
           *                 *                                   *
       .                 .                 .                 .
  *                  *                  *       *          *
          .                 .                 .                 .
    .                .                .                .
             +               +               +               +
       g"y----____                              .                .
       HmH--__    ~~~~----____              *                 *
      ,%%%.   ~~--__          ~~~~----____                .
      JMMML         ~~--__                ~~~~----____
      |%%%|       .       ~~--__                      ~~~~----____
     ,MMMMM. *                  *~--__                            ~~~~-
     |%%%%%|         .                ~~--__           
     AMMMMMA   .                .           ~~--__
  ___MMM^MMM            +                         ~~--__
              `\AwAwAwAwAwAwAwAwAwAwAwAwAwAwAwAwAwAwAwAw^v^v^v^v^v^v^v^

 * "The lighthouse" - Saturn LED Patch
 * 24/03/18 @ Nida, Lithuania
 * 
 */
 
#include <FastLED.h>

#define NUM_LEDS 300
#define DATA_PIN 5

#define STORM_COUNT 6
#define STORM_SPEED 24
#define STORM_FADE_AMOUNT 6

#define BRIGHTNESS_MIN 70
#define BRIGHTNESS_MAX 255

#define SATURATION_MIN 150
#define SATURATION_MAX 255

#define COLOR_RANGE 10
#define CHANGE_COLOR_ROTATIONS 4

CRGBArray<NUM_LEDS> leds;

int COLORS[] = {
  140,
  32
};

int rotationIndex;
int currentColorIndex;
int stormStartPixelIndex[STORM_COUNT];

int color;
int saturation;
int brightness;

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

  // Set initial values
  currentColorIndex = 0;
  rotationIndex = 0;
  
  for (int i = 0; i < STORM_COUNT; i += 1) {
    stormStartPixelIndex[i] = i * (NUM_LEDS / STORM_COUNT);
  }

  // Reset
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

void loop() {
  for (int i = 0; i < STORM_COUNT; i += 1) {
    int index = stormStartPixelIndex[i];
    int currentColor = COLORS[currentColorIndex];
    
    color = random8(currentColor - COLOR_RANGE, currentColor + COLOR_RANGE);
    saturation = random8(SATURATION_MIN, SATURATION_MAX);
    brightness = random(BRIGHTNESS_MIN, BRIGHTNESS_MAX);
    
    // Draw rotating fields
    leds(index, index) = CHSV(color, saturation, brightness);

    stormStartPixelIndex[i] += 1;

    if (index >= NUM_LEDS) {
      stormStartPixelIndex[i] = 0;

      // Did the first storm reach its end?
      if (i == 0) {
        rotationIndex += 1;

        // Is it time to change the color?
        if (rotationIndex >= CHANGE_COLOR_ROTATIONS) {
          currentColorIndex += 1;
          rotationIndex = 0;

          if (currentColorIndex >= (sizeof(COLORS) / sizeof(int))) {
            currentColorIndex = 0;
          }
        }
      }
    }
  }

  leds.fadeToBlackBy(STORM_FADE_AMOUNT);

  // Update LEDs
  FastLED.delay(STORM_SPEED);
  FastLED.show();
}
