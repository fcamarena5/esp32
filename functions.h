void connect_wifi();
void disconnect_wifi();
void activate_access_point();
bool check_if_client_connected();

void check_amg8833();
float* read_pixels();

void init_servos();
void move_servo(int servo_id, int angle);
int read_servo1();
int read_servo2();

String get_memory_ssid();
String get_memory_password();
String get_memory_url();
String get_memory_port();
String get_memory_username();
void store_ssid(String ssid);
void store_password(String password);
void store_url(String url);
void store_port(String port);
void store_username(String username);
void store_included();
bool check_credentials_exist();
void deleteMemory();
bool is_included_in_server();

void handleSave(AsyncWebServerRequest *request);
void handleReset(AsyncWebServerRequest *request);
void handleServo(AsyncWebServerRequest *request);
void handleSendData(AsyncWebServerRequest *request);
void send_request_add_device();
void send_data();
void send_thermal_data();

void init_sensors();
float get_temperature();
int get_light();
