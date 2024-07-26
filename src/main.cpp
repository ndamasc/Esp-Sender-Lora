#include <Arduino.h>
#include <LoRa.h>
#include <SPI.h>
#include <SPIFFS.h>

#include "ds18b20.h"
#include "ph.h"

#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

#define BAND 915E6
#define signalBandwidth 125E3
 
#define tempo 20000
int readingID = 1;

int counter = 0;
String LoRaMessage = "";


void startLoRA() {
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DIO0);

  while (!LoRa.begin(BAND) && counter < 10) {
    Serial.print(".");
    counter++;
    delay(500);
  }
  if (counter == 10) {
    Serial.println("Starting LoRa failed!");
  }
  Serial.println("LoRa Initialization OK!");
  delay(2000);
  LoRa.setSpreadingFactor(12);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);
}


void sendReadings() {
  LoRaMessage = String(readingID) + "/" + String(tempAgua)+ "&" + String(ph);
  LoRa.beginPacket();
  LoRa.print(LoRaMessage);
  LoRa.endPacket();
  
  Serial.println("LoRa packet sent!");
  Serial.print("Sending packet: ");
  Serial.println(readingID);
  readingID++; 
}

void idleLoRA() {
  LoRa.idle(); 
}

void saveReadingID() {
  File file = SPIFFS.open("/readingID.txt", FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  file.println(readingID);
  file.close();
}

void loadReadingID() {
  if (SPIFFS.exists("/readingID.txt")) {
    File file = SPIFFS.open("/readingID.txt", FILE_READ);
    if (!file) {
      Serial.println("Failed to open file for reading");
      return;
    }
    readingID = file.parseInt();
    file.close();
  } else {
    Serial.println("File readingID.txt does not exist");
  }
}

void setup() {
  Serial.begin(115200);
  startLoRA(); 
  init_ds18b20();

  if (!SPIFFS.begin(true)) {
    Serial.println("Failed to mount file system");
    return;
  }

  loadReadingID(); // Carrega o valor atual de readingID do arquivo

}

void loop() {

  if(readingID<101){
    get_values_ds18b20();
    get_values_ph4502c();    

    sendReadings();
    saveReadingID(); // Salva o valor atual de readingID no SPIFFS
    idleLoRA(); 
    delay(10000); // Delay para permitir o modo idle

    Serial.println("Entering deep sleep for 5 minutes...");
    esp_sleep_enable_timer_wakeup(300 * 1000000); // Tempo de deep sleep em microsegundos
    esp_deep_sleep_start();
  } 
  else{
    readingID=1;
  }
  
}


/// SE QUISER REINICIAR O READINGID COMENTAR AS LINHAS DE SAVE E LOAD