#include <Adafruit_AMG88xx.h>


#define AMG88xx_ADDRESS 0x69
Adafruit_AMG88xx amg;

void check_amg8833() {
    if (!amg.begin(AMG88xx_ADDRESS)) {
        Serial.println("Can't connect with the AMG8833 sensor");
        while (1);
    }
}

float* read_pixels() {
    float* pixels = new float[64];
    float interpolation[256];
    amg.readPixels(pixels);
    return pixels;
}
