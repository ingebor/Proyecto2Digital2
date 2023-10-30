/*
  Multple serial test
 
  Receives from the main serial port, sends to the others. 
  Receives from serial port 1, sends to the main serial (Serial 0).
 
  The circuit: 
  * Any serial device attached to Serial port 1
  * Serial monitor open on Serial port 0:
 
  created 30 Dec. 2008
  by Tom Igoe
 
  This example code is in the public domain.
 
*/
const int buttonPin = 17;
int buttonState = 0; // variable for reading the LP button state
int presionado1 = 0;
int presionado2 = 0;
String inByte = "";
String temp = "";
String hum = "";


void setup() {
  // initialize both serial ports:
  Serial.begin(115200);
  Serial2.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // read from port 1, send to port 0:
  buttonState = digitalRead(buttonPin);
  if (buttonState == 0) {
    //Serial.println("presionado"); // turn LED on: 
    presionado1 = 1;
  }
  if(buttonState == 1 && presionado1 == 1){
    Serial.println("recibiendo");
    Serial2.println("m");
    delay(300);
    presionado1 = 0;
  }

   while (Serial2.available()){
   delay(10);
   if (Serial2.available()>0){
     char c = Serial2.read();
     inByte +=c;
    }
  }
  if(inByte.length()>0){
    Serial.println(inByte);
    temp = inByte.substring(0,5);
    hum = inByte.substring(6,11);
   inByte = "";
   Serial.println(temp);
   Serial.println(hum);
   delay(300);
  }
  //Serial.println(temp);
  //Serial.println(temp);
  /*
  if(Serial2.available()>0){
      //Serial.println("disponible");
      String inByte = Serial2.readStringUntil('\n');
      Serial.println(inByte);
      delay(1000);
    }

    */
    

  /*
  if (Serial2.available()) {
    float inByte = Serial2.read();
    Serial.write(inByte); 
  }
  */
}
