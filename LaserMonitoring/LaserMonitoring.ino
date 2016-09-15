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
 
#define aref_voltage 3.3;         // we tie 3.3V to ARef and measure it with a multimeter!

int speaker = 5;
int sensorPin = 0;

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(speaker, OUTPUT);

  analogReference(EXTERNAL);

  Serial.begin(9600);
}

void loop(){
  int reading = analogRead(sensorPin);  
  
  // converting that reading to voltage, for 3.3v arduino use 3.3
  float voltage = reading * aref_voltage;
  voltage /= 1024.0; 
  
  float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
  Serial.print(temperatureC); Serial.print(" degrees C");

  if(temperatureC < 5.0 && temperatureC > 6.0){
    warn(temperatureC);
  }
  if(temperatureC <= 5.0){
    alert();
  }
  if(temperatureC > 24.0 && temperatureC < 25.0){
    warn(temperatureC);
  }
  if(temperatureC >= 25.0){
    alert();
  }

  Serial.println("");
  delay(1000);
}

float lastLevel;
void warn(float level) {
  if(lastLevel == level){
    return;
    // only beep once on a tenth of a degree change.
  }
  lastLevel = level;
  Serial.print(" warn: ");Serial.print(level);
  
  int pitch = map(level, 24, 25, 120, 1500);
  // turn off tone function
  noTone(speaker);
  
  tone(speaker, level, 200);
}

void alert() {
  Serial.print(" alert! ");
  // turn off tone function for pin 6:
  noTone(speaker);
  // play a note on pin 7 for 500 ms:
  tone(speaker, 494, 500);
  delay(500);
}
