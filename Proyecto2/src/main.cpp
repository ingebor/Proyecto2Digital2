#include <Arduino.h>
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11

int valorSensor = 0;

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  Serial2.begin(115200);

  dht.begin();
}

void loop()
{
  // delay(2000); // Es un sensor lento, por lo que hay que darle tiempo.
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  if (Serial2.available() > 0)
  {
    //Serial.println("Disponible");
    char bufferTiva = Serial2.read();
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

  /*
  else
  {
    Serial.println("Puerto no disponible");
  }
  */
  /*
bufferTiva = Serial2.readStringUntil('\n');
  }
  if(bufferTiva == "m"){

  Serial.print(F("Humedad: "));
  Serial.print(h);
  Serial.print(F("% Temperatura: "));
  Serial.print(t);
  Serial.println(F("°C "));
  */
}