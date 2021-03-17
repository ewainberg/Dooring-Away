// Import installed libraries
#include "pitches.h"
// notes in the melody:
int melody[] = {
  NOTE_D4, NOTE_G4, NOTE_D4, NOTE_G4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
 4, 4, 4, 4
};
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
// The 'pipe' or 'frequency'
// Same for sender and receiver
const uint64_t pipe = 0xE8E8F0F0E1LL; 
// Declare object & Create Radio
RF24 radio(7, 8); //CE and CSN pins
//Declare Variable array 'sensorsReceived'
//as a 2 element array
int sensorsReceived[2]; //create array to receive sensor values
int distanceUltrasonic;
int infraRed;

void setup() {
radio.begin(); //begin radio
radio.openReadingPipe(1,pipe); //start radio tunnel with adress variable 'pipe'
radio.startListening(); //start receiving data
Serial.begin(9600); //start serial monitor at 9600 baud
}
void loop() {
//read the incoming radio signal 
radio.read(sensorsReceived, sizeof(sensorsReceived));
// print the values of 'sensorsReceived'
distanceUltrasonic=sensorsReceived[0]; //set array value [0] as ultraSonic
infraRed=sensorsReceived[1]; //set array value [1] as infraRed
Serial.print(distanceUltrasonic);
Serial.print("\t");
Serial.println(infraRed);
if (ultraSonic==PLACEHOLDER && infraRed==PLACEHOLDER){
 playSpeaker();
}
}

void playSpeaker()
{
  int thisNote = 0; thisNote < 8; thisNote++;
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
}
