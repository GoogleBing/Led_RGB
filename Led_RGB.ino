#include "Led_RGB.h"

const int RED_PIN=10;
const int GREEN_PIN=9;
const int BLUE_PIN=8;
led_RGB rgb;

void setup()
{
  Serial.begin(9600);
  rgb.begin(RED_PIN,GREEN_PIN,BLUE_PIN,COMMON_CATHODE);
}

void loop()
{
  rgb.changeColor(RED,PURPLE,5,100,10000);
}
