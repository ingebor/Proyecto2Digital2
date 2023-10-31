//Universidad del Valle de Guatemala
//Electrónica Digital 2
//Ingebor Ayleen Rubio Vasquez-19003
//Proyecto 2

//Librerías
#include <Arduino.h>
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11

//Variables globales
int valorSensor = 0;

DHT dht(DHTPIN, DHTTYPE);

//COnfiguración
void setup()
{
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  Serial2.begin(115200);

  dht.begin();
}

//Loop principal
void loop()
{
  // Obtener los valores de temperatura y humedad
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  //Si no se pudo obtener los valores, mostrar un mensaje de advertencia
  if (isnan(h) || isnan(t))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  //Cuando haya comunicaicón serial
  if (Serial2.available() > 0)
  {
    //leer el mensaje proveniente de la Tiva C
    char bufferTiva = Serial2.read();
    //Si este corresponde a la letra m, enviar los datos de temperatura y humedad
    //concatenados en un string separado por una coma
    if (bufferTiva == 'm')
    {
      Serial.println("\nEnviando temperatura y humedad");
      Serial.print(F("Temperatura: "));
      Serial.print(t);
      Serial.println(F("°C "));
      Serial.print(F("Humedad: "));
      Serial.print(h);
      Serial.print(F("%"));
      String temp = String(t);
      String hum = String(h);
      String myString = temp + ',' + hum;
      Serial2.println(myString);
      delay(300);
    }
  }

}