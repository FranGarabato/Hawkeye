#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
 
//Declaremos los pines CE y el CSN
#define CE_PIN 4
#define CSN_PIN 5
 
//Variable con la dirección del canal que se va a leer
byte direccion[5] ={'c','a','n','a','l'}; 

//creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);

//vector para los datos recibidos
float datos[3];

void setup()
{
 //inicializamos el NRF24L01 
  radio.begin();
  //inicializamos el puerto serie
  Serial.begin(9600); 
  
  //Abrimos el canal de Lectura
  radio.openReadingPipe(1, direccion);
  
    //empezamos a escuchar por el canal
  radio.startListening();
 
}
 
void loop() {
 uint8_t numero_canal;
 //if ( radio.available(&numero_canal) )
 if ( radio.available())
 {    
     //Leemos los datos y los guardamos en la variable datos[]
     radio.read(datos,sizeof(datos));
     if (datos[2] == 0)
     {
     //reportamos por el puerto serial los datos recibidos
     Serial.print("Latitud= " );
     Serial.print(datos[0], 6);
     Serial.print(" , ");
     Serial.print("Longitud= " );
     Serial.print(datos[1], 6);
     Serial.print(" , FUEGO!! ");
     Serial.print(datos[2]);
    }
    else
    {
     //reportamos por el puerto serial los datos recibidos
     Serial.print("Latitud= " );
     Serial.print(datos[0], 6);
     Serial.print(" , ");
     Serial.print("Longitud= " );
     Serial.print(datos[1], 6);
     Serial.print(" , ");
     Serial.print(datos[2]);
   }
 }
 else
 {
     Serial.println("No hay datos de radio disponibles");
 }
 delay(1000);
}
