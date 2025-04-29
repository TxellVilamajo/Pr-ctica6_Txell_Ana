#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#define CS_PIN    5   
#define SCK_PIN   12
#define MISO_PIN  13
#define MOSI_PIN  11

SPIClass spi = SPIClass(FSPI); // Usa SPI1 (FSPI)
File myFile;

void setup() {
  Serial.begin(115200);
  delay(2000);

  // Configura SPI con los pines
  spi.begin(SCK_PIN, MISO_PIN, MOSI_PIN, CS_PIN);

  Serial.print("Iniciant SD... ");
  
  // Intenta inicializar con velocidad reducida (1 MHz)
  if (!SD.begin(CS_PIN, spi, 1000000)) { // <- ¡Velocidad reducida!
    Serial.println("Error. Verifica:");
    Serial.println("- Pins i connexions");
    Serial.println("- Format FAT32");
    Serial.println("- Resistència pull-up");
    while (1);
  }
  Serial.println("Correcte");

  // Leer archivo...
  myFile = SD.open("/prova1.txt");
  if (myFile) {
    Serial.println("Contingut:");
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.close();
  } else {
    Serial.println("Error obrint l'arxiu");
  }
}

void loop() {}
