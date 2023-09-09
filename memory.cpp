#include <Preferences.h>


Preferences preferences;

String get_memory_ssid() {
  preferences.begin("esp32", false);
  String ssid = preferences.getString("ssid", "");
  return ssid;
}

String get_memory_password() {
  preferences.begin("esp32", false);
  String password = preferences.getString("password", "");
  return password;
}

String get_memory_url() {
  preferences.begin("esp32", false);
  String url = preferences.getString("url", "");
  return url;
}

String get_memory_port() {
  preferences.begin("esp32", false);
  String port = preferences.getString("port", "");
  return port;
}

String get_memory_username() {
  preferences.begin("esp32", false);
  String username = preferences.getString("username", "");
  return username;
}

bool check_credentials_exist() {
  preferences.begin("esp32", false);
  String ssid = preferences.getString("ssid", "");
  if (ssid == "" || ssid == NULL) {
    return false;
  } else {
    return true;
  }
}

void store_ssid(String ssid) {
  preferences.begin("esp32", false);
  preferences.putString("ssid", ssid);
}

void store_password(String password) {
  preferences.begin("esp32", false);
  preferences.putString("password", password);
}

void store_url(String url) {
  preferences.begin("esp32", false);
  preferences.putString("url", url);
}

void store_port(String port) {
  preferences.begin("esp32", false);
  preferences.putString("port", port);
}

void store_username(String username) {
  preferences.begin("esp32", false);
  preferences.putString("username", username);
}

void store_included() {
  preferences.begin("esp32", false);
  preferences.putBool("included", true);
}

void deleteMemory() {
  preferences.clear();
  Serial.println("Memory has been deleted.");
}

bool is_included_in_server() {
  bool included = preferences.getBool("included", false);
  return included;
}
