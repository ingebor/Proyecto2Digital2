//Librerias
#include <SPI.h>
#include <SD.h>

// define your pitch constants
// these will be notes that can be used to make a song


#define NOTE_C4  262
#define NOTE_A6  1760
#define NOTE_C5  523
#define NOTE_C7  2093

//Variables globales
const int buttonPin2 = 17;
const int buttonPin1 = 31;
int buttonState2 = 0; // variable for reading the LP button state
int buttonState1 = 0;
int presionado1 = 0;
int presionado2 = 0;
String inByte = "";
String temp = "";
String hum = "";
File archivo;
String enviarArchivo = "";
int buzzerPin = 19;

int melody[] = {
  NOTE_C4,NOTE_C5,NOTE_A6,NOTE_C7
};
int noteDurations[] = {
  4,4,4,4
};
int melody2[] = {
  NOTE_C7,NOTE_A6,NOTE_C5,NOTE_C4
};

//Configuracion
void setup() {
  // initialize both serial ports:
  Serial.begin(115200);
  Serial2.begin(115200);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT); // set buzzerPin to OUTPUT

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  SPI.setModule(0);

  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  pinMode(12, OUTPUT);

  if (!SD.begin(12)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
}

void loop() {
  // read from port 1, send to port 0:
  buttonState2 = digitalRead(buttonPin2);
  buttonState1 = digitalRead(buttonPin1);

  //Presionar boton para recibir datos
  if (buttonState2 == 0) {
    presionado2 = 1;
  }
  if(buttonState2 == 1 && presionado2 == 1){
    Serial.println("recibiendo");
    Serial2.println("m");
    delay(300);
    presionado2 = 0;
    for (int thisNote = 0; thisNote < 4; thisNote++) {

    // to calculate the note duration, take one second divided by the
    // note type. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(buzzerPin, melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration + 50; // delay between pulse
    delay(pauseBetweenNotes);

    noTone(buzzerPin); // stop the tone playing
  }
  }

  //Leer valores de temperatura y humedad
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
    enviarArchivo = inByte;
   inByte = "";
   Serial.println(temp);
   Serial.println(hum);
   delay(300);
  }

  //Presionsar boton para almacenar en la SD
  if (buttonState1 == 0) {
    presionado1 = 1;
  }
  if(buttonState1 == 1 && presionado1 == 1){
    archivo = SD.open("proyecto.txt", FILE_WRITE);
    if(archivo){
      for (int thisNote = 0; thisNote < 4; thisNote++) {

        // to calculate the note duration, take one second divided by the
        // note type. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000/noteDurations[thisNote];
        tone(buzzerPin, melody2[thisNote], noteDuration);
    
        int pauseBetweenNotes = noteDuration + 50; // delay between pulse
        delay(pauseBetweenNotes);
    
        noTone(buzzerPin); // stop the tone playing
        
      }
      Serial.println("Subiendo a SD: ");
      Serial.println(enviarArchivo);
      archivo.println(enviarArchivo);
      archivo.close();
      Serial.println("Listo!");
    }
    else{
      Serial.println("error opening proyecto.txt");
    }
    presionado1 = 0;
  }

}
