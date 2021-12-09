#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
int id_del_drone = 1;
//Declaremos los pines CE y el CSN
#define CE_PIN 4
#define CSN_PIN 5
 
//Variable con la dirección del canal que se va a leer
byte direccion[5] ={'c','a','n','a','l'}; 

//creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);

//vector para los datos recibidos
float datos[3];

TaskHandle_t Task1;
TaskHandle_t Task2;

void setup() {
  //inicializamos el NRF24L01 
  radio.begin();
  //inicializamos el puerto serie
  Serial.begin(9600); 
  
  //Abrimos el canal de Lectura
  radio.openReadingPipe(1, direccion);
  
    //empezamos a escuchar por el canal
  radio.startListening();

  xTaskCreatePinnedToCore(Recepcion,"Task1",10000,NULL,1,&Task1,0);                         
  delay(500); 

  xTaskCreatePinnedToCore(Muestreo,"Task2",10000,NULL,1,&Task2,1);          
    delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void Recepcion(){
  Serial.print("Dron N°" + id_del_drone);
  if ( radio.available())
 {    
     //Leemos los datos y los guardamos en la variable datos[]
     radio.read(datos,sizeof(datos));
  }
  
 else
 {
     Serial.println("No hay datos de radio disponibles");
 }
}

void Muestreo(){
if (datos[2] == 0)
     {
     //reportamos por el puerto serial los datos recibidos
     Serial.print("Dato0= " );
     Serial.print(datos[0]);
     Serial.print(" m, ");
     Serial.print("Dato1= " );
     Serial.print(datos[1]);
     Serial.print(" m, ");
     Serial.print(datos[2]);
     Serial.print(" V, ");
    }
    else
    {
     //reportamos por el puerto serial los datos recibidos
     Serial.print("Dato0= " );
     Serial.print(datos[0]);
     Serial.print(" m, ");
     Serial.print("Dato1= " );
     Serial.print(datos[1]);
     Serial.print(" m, ");
     Serial.print(datos[2]);
     Serial.print(" V problemas de CO2, "); 
   }
     delay(1000);
}
