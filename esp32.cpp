#include <Adafruit_AMG88xx.h>


#define AMG88xx_ADDRESS 0x69
Adafruit_AMG88xx amg;

void check_amg8833() {
    if (!amg.begin(AMG88xx_ADDRESS)) {
        Serial.println("No se puede conectar con el sensor AMG8833");
        while (1);
    }
}

float bilinear_interpolation(float q11, float q12, float q21, float q22, float x, float y) {
    float r1 = (1.0 - x) * q11 + x * q21;
    float r2 = (1.0 - x) * q12 + x * q22;
    return (1.0 - y) * r1 + y * r2;
}

float* read_pixels() {
    float* pixels = new float[64];
    float interpolation[256];
    amg.readPixels(pixels);
    //for (int i = 0; i < 16; i++) {
    //    for (int j = 0; j < 16; j++) {
    //        int idx = i*4 + j/4 + 16*(j%4);
    //        interpolation[i*16+j] = bilinear_interpolation(pixels[idx], pixels[idx+1], pixels[idx+16], pixels[idx+17], (float)(j%4)/4.0, (float)(j/4)/4.0);
    //    }
    //}
    return pixels;
}
