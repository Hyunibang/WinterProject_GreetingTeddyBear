// FILE GreetingTeddy.ino
// DATE 2017-02-12
// AUTHOR Lee Young Hyun

#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>


SoftwareSerial mySerial(10,11);

const int speedPin = 3; // H-bridge enable pin for speed control 
const int motor1APin = 8; // H-bridge leg 1 
const int motor2APin = 7; // H-bridge leg 2  
const int TriggerPin = 5; //Trig pin
const int EchoPin = 4; //Echo pin
long Duration = 0;

int speed_value_motor1; // value for motor speed 

void setup() {
 
Serial.begin(9600);
mySerial.begin(9600);
mp3_set_serial(mySerial);
delay(100);
mp3_set_volume(30);

pinMode(TriggerPin, OUTPUT); // Trigger is an output pin
pinMode(EchoPin, INPUT); // Echo is an input pin
Serial.begin(9600); // Serial Output

pinMode(speedPin, OUTPUT); 
pinMode(motor1APin, OUTPUT); 
pinMode(motor2APin, OUTPUT); 
}

void loop(){
  
  digitalWrite(TriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPin, HIGH); // Trigger pin to HIGH
  delayMicroseconds(10); // 10us high
  digitalWrite(TriggerPin, LOW); // Trigger pin to HIGH

  Duration = pulseIn(EchoPin, HIGH); // Waits for the echo pin to get high
  // returns the Duration in microseconds

  long Distance_mm = Distance(Duration); // Use function to calculate the distance

  Serial.print("Distance = "); // Output to serial
  Serial.print(Distance_mm);
  Serial.println(" mm");

  if(Distance_mm < 150){
   digitalWrite(motor1APin, HIGH); // set leg 1 of the H-bridge low 
   digitalWrite(motor2APin, LOW); // set leg 2 of the H-bridge high
   Serial.println("Motor 1");
   mp3_play(1);
   delay(5000);
  }
 else{
  digitalWrite(motor1APin, LOW); // set leg 1 of the H-bridge low 
   digitalWrite(motor2APin, LOW); // set leg 2 of the H-bridge high
   Serial.println("Motor 0");
 }

 speed_value_motor1 = 255; // half speed 
 analogWrite(speedPin, speed_value_motor1); // output speed as 
 delay(100);
   
}
long Distance(long time)
{
  // Calculates the Distance in mm
  // ((time)*(Speed of sound))/ toward and backward of object) * 10

  long DistanceCalc; // Calculation variable
  DistanceCalc = ((time / 2.9) / 2); // Actual calculation in mm
  //DistanceCalc = time / 74 / 2; // Actual calculation in inches
  return DistanceCalc; // return calculated value
}



