//RGB LED code
//7:45
//2/11/23
//code 2

#include <FastLED.h>
#define LED_PIN D3
#define NUM_LEDS 8
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS); //LED configration

}

void loop() {
  //testing

}

//buffering of led
void ledBuffering()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = CRGB(0, 0, 255);
        FastLED.show();
        delay(200);
    }

    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = CRGB(0, 0, 0);
    }
    FastLED.show();
    delay(200);
}

//led light during connection
void ledConnection()
{
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            leds[i] = CRGB(0, 225, 0);
        }
        FastLED.show();
        delay(150);

        for (int i = 0; i < NUM_LEDS; i++)
        {
            leds[i] = CRGB(0, 0, 0);
        }
        FastLED.show();
        delay(200);
    }
}

// led light alert
void alert()
{
    leds[2] = CRGB(225, 0, 0);
    leds[6] = CRGB(225, 0, 0);
    FastLED.show();
    delay(80);

    leds[1] = CRGB(225, 0, 0);
    leds[3] = CRGB(225, 0, 0);
    leds[7] = CRGB(225, 0, 0);
    leds[5] = CRGB(225, 0, 0);
    FastLED.show();
    delay(80);

    leds[0] = CRGB(225, 0, 0);
    leds[4] = CRGB(225, 0, 0);
    leds[8] = CRGB(225, 0, 0);
    FastLED.show();
    delay(80);

    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = CRGB(0, 0, 0);
    }
    FastLED.show();
    delay(300);
}
//led off
void ledoff()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = CRGB(0, 0, 0);
    }
    FastLED.show();
}
