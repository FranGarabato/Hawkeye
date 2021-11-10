#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 4
#define CSN_PIN 5

byte direccion[5] ={'c','a','n','a','l'};

//creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);

float datos[3];

void setup() {
  //inicializamos el NRF24L01 
  radio.begin();
  Serial.begin(9600); 
  //Abrimos un canal de escritura
  radio.openWritingPipe(direccion);

}

void loop() {
  //cargamos <los datos en la variable datos[]
 datos[0]=10;
 datos[1]=millis();
 datos[2]=3.14;

}
