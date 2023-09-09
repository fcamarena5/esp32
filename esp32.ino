
#include <WiFi.h>
#include <ESPAsyncWebSrv.h>
#include "functions.h"


String mac = WiFi.macAddress();
String ssid = "ESP32-" + mac.substring(12);
const char *password = "11131719";
const IPAddress apIP(10, 10, 254, 1);
const int httpPort = 80;


AsyncWebServer server(httpPort);

void setup() {
  Serial.begin(115200);
  // Create the access point
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid.c_str(), password);
  // Initialize the web server
  server.on("/save", HTTP_GET, handleSave);
  server.on("/reset", HTTP_GET, handleReset);
  server.on("/move_servo", HTTP_GET, handleServo);
  server.on("/send_data", HTTP_GET, handleSendData);
  server.begin();
  Serial.println("Server started");
  // Initialize the sensors and actuators
  init_servos();
  init_sensors();
  check_amg8833();
}

void loop() {

  int counter = 0;

  if (check_credentials_exist() && WiFi.status() != WL_CONNECTED) {
    // Connect to the Wi-Fi is the credentials are stored
    connect_wifi();
  }
  if (WiFi.status() == WL_CONNECTED && !is_included_in_server()) {
    // Register the device in the server
    send_request_add_device();
  }
  
  while (WiFi.status() == WL_CONNECTED && is_included_in_server()) {
    if (counter % 60 == 0) {
      send_data();
      counter = 0;
    }
    if (counter % 10 == 0) {
      send_thermal_data();
    }
    counter += 1;
    delay(1000);
  }
}
