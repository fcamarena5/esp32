#include <WiFi.h>
#include <HTTPClient.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>
#include <AsyncWebSocket.h>
#include "functions.h"


void connect_wifi() {
  String ssid = get_memory_ssid();
  Serial.print("Current ssid: ");
  Serial.println(ssid);
  String password = get_memory_password();
  Serial.print("Current password: ");
  Serial.println(password);
  Serial.print("Trying to connect to ");
  Serial.print(ssid);
  WiFi.begin(ssid.c_str(), password.c_str());
  int counter = 0;
  while (WiFi.status() != WL_CONNECTED && counter < 10) {
    Serial.print(".");
    counter += 1;
    delay(1000);
  }
  Serial.println("");
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Could not connect to the Wi-Fi.");
  } else {
    Serial.print("Connected to ");
    Serial.println(ssid);
    IPAddress ip = WiFi.localIP();
    Serial.print("IP: ");
    Serial.println(ip);
  }
}

void handleSave(AsyncWebServerRequest *request) {
  int params = request->params();
  for(int i=0;i<params;i++){
    AsyncWebParameter* p = request->getParam(i);
    Serial.println(p->value());
  }
  String ssid = request->arg("ssid");
  String password = request->arg("password");
  String url = request->arg("url");
  String port = request->arg("port");
  String username = request->arg("username");

  store_ssid(ssid);
  store_password(password);
  store_url(url);
  store_port(port);
  store_username(username);
  request->send(200, "text/plain", "Credentials saved");
}

void handleReset(AsyncWebServerRequest *request) {
  deleteMemory();
  request->send(200, "text/plain", "Memory deleted");
  ESP.restart();
}

void handleServo(AsyncWebServerRequest *request) {
    Serial.println("Moving servos...");
    String angle_servo1 = request->arg("servo1");
    String angle_servo2 = request->arg("servo2");
    move_servo(1, angle_servo1.toInt());
    move_servo(2, angle_servo2.toInt());
    request->send(200, "text/plain", "Servos moved.");
}

void handleSendData(AsyncWebServerRequest *request) {
  int angle_servo1 = read_servo1();
  int angle_servo2 = read_servo2();
  float temperature = get_temperature();
  int light = get_light();
  String raw_mac = WiFi.macAddress();
  String mac = "";
  for (int i=0; i<raw_mac.length();i++) {
    char currentChar = raw_mac.charAt(i);
    if (currentChar != ':') {
      mac += currentChar;
    }
  }
  // Create the URL for the API call
  String url = get_memory_url();
  String port = get_memory_port();
  String full_url = url + ":" + port + "/api/add_data/";
  IPAddress raw_ip = WiFi.localIP();
  String ip = raw_ip.toString();
  String postData = "angle_servo1="+String(angle_servo1)+"&angle_servo2="+String(angle_servo2)+"&temperature="+String(temperature)+"&light="+String(light)+"&mac="+mac+"&ip="+ip;
  // Send the POST request
  HTTPClient http;
  http.begin(full_url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.POST(postData);
  // Manage the response
  if (httpResponseCode == 201) {
    Serial.println("Data successfully sent");
    store_included();
  } else {
    Serial.print("Error sending data. Response code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}

void send_data() {
  int angle_servo1 = read_servo1();
  int angle_servo2 = read_servo2();
  float temperature = get_temperature();
  int light = get_light();
  String raw_mac = WiFi.macAddress();
  String mac = "";
  for (int i=0; i<raw_mac.length();i++) {
    char currentChar = raw_mac.charAt(i);
    if (currentChar != ':') {
      mac += currentChar;
    }
  }
  // Create the URL for the API call
  String url = get_memory_url();
  String port = get_memory_port();
  String full_url = url + ":" + port + "/api/add_data/";
  IPAddress raw_ip = WiFi.localIP();
  String ip = raw_ip.toString();
  String postData = "angle_servo1="+String(angle_servo1)+"&angle_servo2="+String(angle_servo2)+"&temperature="+String(temperature)+"&light="+String(light)+"&mac="+mac+"&ip="+ip;
  // Send the POST request
  HTTPClient http;
  http.begin(full_url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.POST(postData);
  // Manage the response
  if (httpResponseCode == 201) {
    Serial.println("Data successfully sent");
    store_included();
  } else {
    Serial.print("Error sending data. Response code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}

void send_thermal_data() {
  float* pixels = read_pixels();
  String str_pixels = "";
  for (int i=0;i<64;i++) {
    str_pixels += String(pixels[i]);
    str_pixels += ",";
  }
  String raw_mac = WiFi.macAddress();
  String mac = "";
  for (int i=0; i<raw_mac.length();i++) {
    char currentChar = raw_mac.charAt(i);
    if (currentChar != ':') {
      mac += currentChar;
    }
  }
  // Create the URL for the API call
  String url = get_memory_url();
  String port = get_memory_port();
  String full_url = url + ":" + port + "/api/thermal/";
  IPAddress raw_ip = WiFi.localIP();
  String ip = raw_ip.toString();
  String postData = "mac="+mac+"&ip="+ip+"&pixels="+str_pixels;
  // Send the POST request
  HTTPClient http;
  http.begin(full_url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.POST(postData);
  // Manage the response
  if (httpResponseCode == 201) {
    Serial.println("Thermal data successfully sent");
    store_included();
  } else {
    Serial.print("Error sending thermal data. Response code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}

void send_request_add_device() {
  // Get the data of the device to create the json
  String name_device = "ESP32";
  String raw_mac = WiFi.macAddress();
  String mac = "";
  for (int i=0; i<raw_mac.length();i++) {
    char currentChar = raw_mac.charAt(i);
    if (currentChar != ':') {
      mac += currentChar;
    }
  }
  String username = get_memory_username();
  // Create the URL for the API call
  String url = get_memory_url();
  String port = get_memory_port();
  IPAddress raw_ip = WiFi.localIP();
  String ip = raw_ip.toString();
  String full_url = url + ":" + port + "/api/add_device/";
  String postData = "username="+username+"&name=esp32&mac="+mac+"&ip="+ip;
  // Send the POST request
  HTTPClient http;
  http.begin(full_url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.POST(postData);
  // Manage the response
  Serial.println("Trying to register this device in the server...");
  if (httpResponseCode == 201) {
    Serial.println("Device included in the server");
    store_included();
  } else {
    Serial.print("Error. Response code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}
