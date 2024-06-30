#include <Arduino.h>

const int pino_ph = 2;
float ph;

int buf[10];

void get_values_ph4502c() {
  for (int i = 0; i < 10; i++) {     // 11 amostras
    buf[i] = analogRead(pino_ph);  // Ler o sensor PH
    delay(10);
  }
 
 
  int valorMedio = 0;
  for (int i = 2; i < 8; i++) {  // Realiza o valor médio utilizando 6 amostras
    valorMedio += buf[i];
  }
 
 
  float tensao = (valorMedio * 3.3) / 4095 / 6;
  //Serial.println(tensao);
  ph = ((-6.82*tensao*tensao)+(42.05*tensao) -55.5);
  ph=ph-1.5;
  Serial.println(ph);
  delay(250);
}
