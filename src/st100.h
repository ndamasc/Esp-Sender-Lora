#include <Arduino.h>

const int SensorTurbidez = 32;

int sensorValue;
int turbidity;


float voltagem;
float NTU;
int i;

float ArredondarPara( float ValorEntrada, int CasaDecimal ) {
    float multiplicador = powf( 10.0f, CasaDecimal );
    ValorEntrada = roundf( ValorEntrada * multiplicador ) / multiplicador;
    return ValorEntrada;
}


void get_values_st100(){
  //voltagem = 0;
  //for (i = 0; i < 800; i++) {
  //  voltagem += ((float)analogRead(SensorTurbidez) / 4094) * 3.3;
  //}
//
  //  voltagem = voltagem / 800;
  //  voltagem = ArredondarPara(voltagem, 1);
//
  //if (voltagem < 2.5) {
  //  NTU = 3000;
  //}
  //
  //else if (voltagem > 4.2) {
  //  NTU = 0;
  //  voltagem = 4.2;
  //}
//
  //else {
  //  NTU = -1120.4 * sqrt(voltagem) + 5742.3 * voltagem - 4353.8;
  //}

  sensorValue = analogRead(SensorTurbidez);
    turbidity = map(sensorValue, 0, 640, 80, 0);

    Serial.print("Sensor Value: ");
    Serial.println(sensorValue);

    Serial.print("Turbidity (NTU): ");
    Serial.println(turbidity);

    delay(1000);

}