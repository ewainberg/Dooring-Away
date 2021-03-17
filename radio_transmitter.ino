// Import installed libraries
#define echoPin 3 // attach pin D3 Arduino to pin Echo of HC-SR04
#define trigPin 5 //attach pin D5 Arduino to pin Trig of HC-
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

#define infraRed 4 //define the term "infraRed" as 4 for all instances of it to be replaced with 4 at compilation

// Import installed libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
// The 'pipe' or 'frequency'
// Same for sender and receiver

const uint64_t pipe = 0xE8E8F0F0E1LL; 
// Declare object & Create Radio
RF24 radio(7, 8); //CE and CSN pins 
//Declare Variable array 'sensors'
//as a 2 element array
int sensors[2];
int readInfrared;

void setup()
{
Serial.begin(9600);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
pinMode(infraRed, INPUT);
radio.begin(); //begins radio
radio.openWritingPipe(pipe); //opens writing aka starts sending information
}
void loop()
{
  digitalWrite(trigPin, LOW);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");readInfrared = digitalRead(infraRed); //declare variable "readInfrared" to be the reading that the infrared sensor is giving
// give the sensors array values
sensors[0] = distance;
sensors[1] = readInfrared;
// send 'sensors' array
radio.write(sensors, sizeof(sensors)); //sends the array 'sensors' as well as its amount of elements
Serial.println(distance);
Serial.println("\t");
Serial.println(readInfrared);
delay(10);
}

void ultrasonic()
{
    // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}
