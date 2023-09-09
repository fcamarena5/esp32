#include <Arduino.h>
#line 1 "c:\\Users\\Francisco\\Documents\\VSC_Projects\\amg8833\\amg8833.ino"
#include <Wire.h>
#include <Adafruit_AMG88xx.h>


Adafruit_AMG88xx amg;

void setup()
{
	Serial.begin(9600);
    while (!Serial) delay(10);

    if (!amg.begin()) {
        Serial.println("AMG8833 not found.")
        delay(10);
    }
}

void loop()
{
	float pixels[AMG88xx_PIXEL_ARRAZ_SIZE];
    amg.readPixels(pixels);
    Serial.println("Thermal map:");
    for (int i=0; i < AMG88xx_PIXEL_ARRAZ_SIZE, i++) {
        if (i % 8 == 0) {
            Serial.println("");
        }
        Serial.print(pixels[i]);
        Serial.print(", ");
    }
    delay(1000);
}


