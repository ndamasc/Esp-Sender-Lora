#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const int oneWireBus = 15;


OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);
float tempAgua;

void init_ds18b20(){
    sensors.begin();
}

void get_values_ds18b20(){
    sensors.requestTemperatures(); 
    tempAgua = sensors.getTempCByIndex(0);
    Serial.println(tempAgua);
}

