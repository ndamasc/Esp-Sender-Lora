#include <Arduino.h>

const int pino_ph = 35;

float calibracao_ph7 = 2.5;   // Tensão obtida em solução de calibração pH 7
float calibracao_ph4 = 2.2;   // Tensão obtida em solução de calibração pH 4
float calibracao_ph9 = 3.3;  // Tensão obtida em solução de calibração pH 10
 
#define UTILIZAR_PH_10 false  // Habilita calibração entre pH 7 e 10, \
                                 caso contrário utiliza pH 7 e 4.
float m;
float b;
int buf[10];



void init_ph4502c() {
  Serial.begin(115200);
 
  if (calibracao_ph7 == 0 && calibracao_ph4 == 0 && calibracao_ph9 == 0) {
    delay(500);
    Serial.println();
    Serial.println("Erro - Necessário colocar os valores de calibração no código!");
    while (1)
      ;
  }
 
  if (!UTILIZAR_PH_10 && calibracao_ph4 == 0 && calibracao_ph9 != 0 && calibracao_ph7 != 0) {
    delay(500);
    Serial.println();
    Serial.println("Erro - Você não marcou a opção UTILIZAR_PH_10 como true para utilizar pH 7 e 10.");
    while (1)
      ;
  }
 
 
  if (UTILIZAR_PH_10) {
    m = (7.0 - 9.0) / (calibracao_ph7 - calibracao_ph9);
    b = 9.0 - m * calibracao_ph9;
  } else {
    m = (4.0 - 7.0) / (calibracao_ph4 - calibracao_ph7);
    b = 7.0 - m * calibracao_ph7;
  }
}


void get_values_ph4502c() {
  for (int i = 0; i < 10; i++) {  // 11 amostras
    buf[i] = analogRead(pino_ph);      // Ler o sensor PH
    delay(10);
  }
 
  for (int i = 0; i < 9; i++) {  // Ordena em ordem crescente
    for (int j = i + 1; j < 10; j++) {
      if (buf[i] > buf[j]) {
        int temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }
 
  int valorMedio = 0;
  for (int i = 2; i < 8; i++) {  // Realiza o valor médio utilizando 6 amostras
    valorMedio += buf[i];
  }
 
  float tensao = (valorMedio * 3.3) / 4095 / 6;  // Realiza a média e \
                                                    transforma o valor \
                                                    analógico em volt
  float ph = m * tensao + b; // Converte para pH

 

  Serial.print("Valor pH: ");  // Escreve no display
  Serial.println(ph-3);
  delay(1000);              // Aguarda para próxima leitura
}