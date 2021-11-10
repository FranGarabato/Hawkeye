#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
//Declaremos los pines CE y el CSN
#define CE_PIN 4
#define CSN_PIN 5

//Variable con la dirección del canal por donde se va a transmitir
byte direccion[5] ={'c','a','n','a','l'};

//creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);

//vector con los datos a enviar
float datos[0];
float datos[1];
float datos[2];
/*This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.   
It requires the use of SoftwareSerial, and assumes that you have a 9600-baud serial 
GPS device hooked up on pins 8(rx) and 9(tx).*/
static const int RXPin = 16, TXPin = 17;
static const uint32_t GPSBaud = 9600;



void setup() {

}


void loop() {
  
}
