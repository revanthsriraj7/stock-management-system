//wifi code
//9:10 am
//3/11/23
//code 5

#define WIFI_SSID "akshay"         //defined wifi username and passowrod to be connected
#define WIFI_PASSWORD "aks142004"

void setup() {
  Serial.println("Connecting to Wi-Fi...");
   while (WiFi.status() != WL_CONNECTED)
   {
       Serial.println("Not connected to the internet");
       WiFi.begin(WIFI_SSID, WIFI_PASSWORD);              //conecting to wifi
   }
   if (WiFi.status() == WL_CONNECTED)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.println("Connected to the internet");
    }

}

void loop() {
  // put your main code here, to run repeatedly:

}
