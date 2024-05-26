#include "pmsx003.hpp"
pmsx003 sensor;


void setup() {
  // Connect to the port according your MCU
  Serial2.begin(9600);
  sensor.begin(&Serial2);
}

void loop() {
  pmsx003data data = sensor.read();
  if (!data.success) {
    Serial.println("PMSX003 read failed!");
    return;
  }
  Serial.printf("PM0.3 : %i\n PM0.5: %i\nPM1.0: %i\n PM2.5: %i\n, PM10.0: %i\n",data.particles_03um, data.particles_05um, data.pm10_standard, data.pm25_standard, data.pm100_standard);
}
