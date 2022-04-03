#include <Arduino.h>
#include <WiFi.h>
#include <NeoPixelBus.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoOTA.h>

#include "color_picker.h"

#ifdef CONFIG_DEBUG
  #define DEBUG_PRINTLN(x)  Serial.println (x)
  #define DEBUG_PRINT(x)    Serial.print (x)
#else
  #define DEBUG_PRINTLN(x)
  #define DEBUG_PRINT(x)
#endif

// RGB class for saving the values of the color
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RGB_t;

RGB_t _rgb;

// The server object that will listen on port 80 and respond to requests from web browsers
AsyncWebServer server(CONFIG_SERVER_PORT);

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> pixels(CONFIG_PIXELS_COUNT, CONFIG_PIXELS_PIN);

void setPixelsColor(uint8_t red, uint8_t green, uint8_t blue, uint16_t pixels_count) {
  for (uint16_t i = 0; i < pixels_count; i++) {
    pixels.SetPixelColor(i, RgbColor(red, green, blue));
  }
  pixels.Show();
}

int setup_wifi() {
  // Connect to WiFi network
  DEBUG_PRINT("Connecting to: ");
  DEBUG_PRINTLN(CONFIG_WIFI_SSID);

  // Disconnect wifi before beginning (fixes some connection issues I've had)
  WiFi.disconnect();
  WiFi.begin(CONFIG_WIFI_SSID, CONFIG_WIFI_PASS);

  // Connect to wifi
  DEBUG_PRINT("Connected to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    DEBUG_PRINT(".");
  }

  DEBUG_PRINTLN("");
  DEBUG_PRINTLN("WiFi connected");
  DEBUG_PRINTLN("IP address: ");
  DEBUG_PRINTLN(WiFi.localIP());

  return 0;
}

int setupOTA() {
  ArduinoOTA.setHostname(CONFIG_OTA_HOSTNAME);
  ArduinoOTA.setPassword(CONFIG_OTA_PASSWORD);

  ArduinoOTA 
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      DEBUG_PRINTLN("Start updating " + type);
    })
    .onEnd([]() {
      DEBUG_PRINTLN("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) DEBUG_PRINTLN("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) DEBUG_PRINTLN("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) DEBUG_PRINTLN("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) DEBUG_PRINTLN("Receive Failed");
      else if (error == OTA_END_ERROR) DEBUG_PRINTLN("End Failed");
    });

  ArduinoOTA.begin();
  DEBUG_PRINTLN("OTA ready");
  return 0;
}

int setupServer(){
  // On a GET request, respond with the HTML string found in color_picker.h
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/html", HTML);
  });

  // On a POST request, grab the red, green and blue values that were sent and save them
  server.on("/", HTTP_POST, [](AsyncWebServerRequest * request) {
    AsyncWebParameter *redParam   = request->getParam("red", true);
    AsyncWebParameter *greenParam = request->getParam("green", true);
    AsyncWebParameter *blueParam  = request->getParam("blue", true);

    _rgb.r = redParam->value().toInt()    & 0xFF;
    _rgb.g = greenParam->value().toInt()  & 0xFF;
    _rgb.b = blueParam->value().toInt()   & 0xFF;

    DEBUG_PRINT("RGB: ");DEBUG_PRINT(_rgb.r);(", ");DEBUG_PRINT(_rgb.g);DEBUG_PRINT(", ");DEBUG_PRINTLN(_rgb.b);
  });

  // Start the server
  server.begin();
}

void setup() {
  _rgb.r = 255;
  _rgb.g = 0;
  _rgb.b = 0;
  Serial.begin(CONFIG_SERIAL_BAUD_RATE);
  pixels.Begin();
  setup_wifi();
  setupOTA();
  setupServer();   
}

void loop() {
  ArduinoOTA.handle();
  setPixelsColor(_rgb.r, _rgb.g, _rgb.b, CONFIG_PIXELS_COUNT);
}
