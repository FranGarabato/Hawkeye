#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
//Declaremos los pines CE y el CSN
#define CE_PIN 4
#define CSN_PIN 5
int id_del_drone = 1;
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

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

TaskHandle_t Task1;
TaskHandle_t Task2;

void setup() {
   //inicializamos el NRF24L01 
  radio.begin();
  Serial.begin(9600); 
 //Abrimos un canal de escritura
 radio.openWritingPipe(direccion);
 ss.begin(GPSBaud);

   xTaskCreatePinnedToCore(Lectura,"Task1",10000,NULL,1,&Task1,0);                         
  delay(500); 

  xTaskCreatePinnedToCore(Transmision,"Task2",10000,NULL,1,&Task2,1);          
    delay(500);
}


void loop() {
  
}

  void Lectura(){
    if (gps.encode(ss.read())){
      datos[0]= gps.location.lat(), 6;
      datos[1]= gps.location.lng(), 6;
    }
  }

  void Transmision(){
      Serial.print("Dron N°" + id_del_drone);
      Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    bool ok = radio.write(datos, sizeof(datos)); 
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    delay(1000);
  }
  else
  {
    Serial.print(F("INVALID"));
  }  
  Serial.println();
  }
