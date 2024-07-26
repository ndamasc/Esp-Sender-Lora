#include <Arduino.h>

float ph, valorMedio;

const int sensorPin  = 15;


void get_values_ph4502c(){

  valorMedio = analogRead(sensorPin);
  float tensao = (valorMedio * 3.3) / 4095;
  ph = (5.866*(tensao)*(tensao)) -  (4.705*(tensao));
  Serial.println(ph);
  delay(1000); 
}

