#include "HX711.h"
#include <Arduino.h>
#include <ESP8266Webhook.h>
#include <ESP8266WiFi.h>
#include <ESP_Mail_Client.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <FastLED.h>

#define LED_PIN     D3
#define NUM_LEDS    8


CRGB leds[NUM_LEDS];

#define WIFI_SSID "akshay"
#define WIFI_PASSWORD "aks142004"
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465
#define AUTHOR_EMAIL "akshaybhawarkiti@gmail.com"
#define AUTHOR_PASSWORD "uabulpopoejyiyxk"
#define RECIPIENT_EMAIL "akshaybhawarkiti@gmail.com"
#define RECIPIENT_EMAIL_2 "akshaybhawarlego1@gamil.com"
#define RECIPIENT_EMAIL_3 "revanthsriraj007@gmail.com"

SMTPSession smtp;
Session_Config config;
SMTP_Message message; // Declare message as a global variable
  
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int LOADCELL_DOUT_PIN = D7;
const int LOADCELL_SCK_PIN = D6;
HX711 scale;

int weight;

void sendEmail();

void setup()
{
    Serial.begin(9600);
    pinMode(D5, INPUT);
    pinMode(A0, INPUT);
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

    // CONNECT TO WIFI
    Serial.println("Connecting to Wi-Fi...");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Not connected to the internet");
        ledBuffering();
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // Attempt to connect to Wi-Fi
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(50);
            ledBuffering();
        }
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.println("Connected to the internet");
        ledConnection();
    }

    // Mail handling
    MailClient.networkReconnect(true);
    smtp.debug(1);

    config.server.host_name = SMTP_HOST;
    config.server.port = SMTP_PORT;
    config.login.email = AUTHOR_EMAIL;
    config.login.password = AUTHOR_PASSWORD;

    config.time.ntp_server = F("pool.ntp.org,time.nist.gov");
    config.time.gmt_offset = 3;
    config.time.day_light_offset = 0;

    message.sender.name = F("Stock Management System");
    message.sender.email = AUTHOR_EMAIL;
    message.subject = F("LOW ON STOCK!!");
    message.addRecipient(F("akshaybhawarkiti@gmail.com"), RECIPIENT_EMAIL); 
    message.addRecipient(F("akshaybhawarlego1@gamil.com"), RECIPIENT_EMAIL_2);
    message.addRecipient(F("revanthsriraj007@gmail.com"), RECIPIENT_EMAIL_3);

    String textMsg = "YOUR STOCK IS GETTING LOW BELOW <100g please refill the stock as soon as possible.";
    message.text.content = textMsg.c_str();
    message.text.charSet = "us-ascii";
    message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

    // LCD SETUP
    lcd.begin();
    lcd.backlight();

    // SCALE SETUP
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    scale.set_scale(1131.22); // Calibration
    scale.tare();

    // Delay to put load
    for (int z = 0; z <= 3; z++)
    {
        sleeptime();
        Serial.print("READY");
    }
}

void loop()
{
int counter = analogRead(A0);


    if (counter >= 50 && counter <= 299)
    {
        ledoff();
        weightindi();
        weight = scale.get_units(3);
        Serial.print("Grams: ");
        Serial.print(weight);
        lcd.setCursor(0, 0);
        lcd.print("Weight: ");
        lcd.print(weight);
        lcd.print(" g");
        delay(800);
        lcd.clear();
    }
    else if (counter >= 300 && counter <= 599)
    {
        ledoff();
        weightindi();
        weightEindi();
        weight = scale.get_units(3);
        Serial.print("Grams: ");
        Serial.print(weight);
        lcd.setCursor(0, 0);
        lcd.print("Weight: ");
        lcd.print(weight);
        lcd.print(" g");
        delay(800);
        lcd.clear();

        if (weight <= -1)
        {
          for (int z = 0; z <= 5; ++z)
            {
                alert();
            }
            Serial.println("LOW ON STOCK");
            lcd.setCursor(0, 0);
            lcd.print("LOW STOCK!!");
            lcd.setCursor(0, 1);
            lcd.print("RESTOCK");
            sendEmail();
            delay(5000);
            lcd.clear();
        }
    }
    else if (counter >= 600 && counter <= 899)
    {
        ledoff();
        weightindi();
        weightEindi();
        quantityindi();
        weight = scale.get_units(3);
        int qun = weight / 15;

        Serial.print("Units: ");
        Serial.print(qun);
        Serial.print(" Pecs");
        lcd.setCursor(0, 0);
        lcd.print("Quantity :- ");
        lcd.print(qun);
        delay(800);
        lcd.clear();

        if (qun <= -1)
        {
            for (int z = 0; z <= 5; ++z)
            {
                alert();
            }
            Serial.println("LOW ON STOCK");
            lcd.setCursor(0, 0);
            lcd.print("LOW STOCK!!");
            lcd.setCursor(0, 1);
            lcd.print("RESTOCK");
            sendEmail();
            delay(5000);
            lcd.clear();
        }
    }
    else if (counter >= 900 && counter <= 1204)
    {
        ledoff();
        liquidindi();
        weightindi();
        weightEindi();
        quantityindi();
        // Implement liquid measurement logic here
        // ...
    }
}

void sendEmail()
{
if (!smtp.connect(&config))
 {
return;
 }

if (!MailClient.sendMail(&smtp, &message))
  {
 return;
 }
}

void smtpCallback(SMTP_Status status)
{
if (status.success())
{
for (size_t i = 0; i < smtp.sendingResult.size(); i++)
{
SMTP_Result result = smtp.sendingResult.getItem(i);
}
smtp.sendingResult.clear();
    }
}

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

void sleeptime()
{
    leds[4] = CRGB(225, 225, 225);
    FastLED.show();
    delay(100);

    leds[3] = CRGB(225, 225, 225);
    leds[5] = CRGB(225, 225, 225);
    FastLED.show();
    delay(100);

    leds[2] = CRGB(225, 225, 225);
    leds[6] = CRGB(225, 225, 225);
    FastLED.show();
    delay(100);

    leds[1] = CRGB(225, 225, 225);
    leds[7] = CRGB(225, 225, 225);
    FastLED.show();
    delay(100);

    leds[0] = CRGB(225, 225, 225);
    leds[8] = CRGB(225, 225, 225);
    FastLED.show();
    delay(100);

    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = CRGB(0, 0, 0);
    }
    FastLED.show();
    delay(200);
}

void weightindi()
{
    leds[1] = CRGB(15, 225, 225);
    leds[2] = CRGB(15, 225, 225);
    FastLED.show();
}

void weightEindi()
{
    leds[3] = CRGB(225, 153, 51);
    leds[4] = CRGB(225, 153, 51);
    FastLED.show();
}

void quantityindi()
{
    leds[5] = CRGB(225, 15, 225);
    leds[6] = CRGB(225, 15, 225);
    FastLED.show();
}

void liquidindi()
{
    leds[7] = CRGB(225, 225, 15);
    leds[8] = CRGB(225, 225, 15);
    leds[0] = CRGB(225, 225, 15);
    FastLED.show();
}

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

void ledoff()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = CRGB(0, 0, 0);
    }
    FastLED.show();
}