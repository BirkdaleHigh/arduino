/*
  Multiple tone player

 Plays multiple tones on multiple pins in sequence

 circuit:
 * 3 8-ohm speaker on digital pins 6, 7, and 8

 created 8 March 2010
 by Tom Igoe
 based on a snippet from Greg Borenstein

This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Tone4

 */
#include "pitches.h";
#define aref_voltage 3.3;         // we tie 3.3V to ARef and measure it with a multimeter!

int speaker = 5;
int sensorPin = 0;

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(speaker, OUTPUT);

  analogReference(EXTERNAL);

  Serial.begin(9600);
}

float lastTemp;
void loop(){
  int reading = analogRead(sensorPin);  
  
  // converting that reading to voltage, for 3.3v arduino use 3.3
  float voltage = reading * aref_voltage;
  voltage /= 1024.0; 
  
  float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
  Serial.print(temperatureC); Serial.print(" degrees C");

  if(temperatureC < 5.0 && temperatureC > 6.0){
    if(lastTemp != temperatureC){
      warn(temperatureC); // only beep once on a tenth of a degree change.
    }
  }
  if(temperatureC <= 5.0){
    alert();
  }
  if(temperatureC > 24.0 && temperatureC < 25.0){
    if(lastTemp != temperatureC){
      warn(temperatureC); // only beep once on a tenth of a degree change.
    }
  }
  if(temperatureC >= 25.0){
    alert();
  }

  lastTemp = temperatureC;
  Serial.println("");
  delay(3000);
}

void warn(float level) {
  int range;
  range = (int)(level * 100); //move up 2 decimal places and truncate remainding
  
  int pitch = map(range, 2400, 2500, NOTE_C4, NOTE_C5);
  Serial.print(" warning pitch: ");Serial.print(pitch);
  // turn off tone function
  noTone(speaker);
  
  tone(speaker, pitch, 250);
}

void alert() {
  Serial.print(" alert! ");
  // turn off tone function for pin 6:
  noTone(speaker);
  // play a note on pin 7 for 500 ms:
  tone(speaker, NOTE_C6, 1000);
  delay(1000);
}
