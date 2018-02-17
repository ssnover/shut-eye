
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include "TimerOne.h"
#include <PulseSensorPlayground.h>    // Includes the PulseSensorPlayground Library.   

const int LED = 13;
double Period = .01; //Seconds
auto Flag = 0;

const int HeartSensor = A0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int beatLED = 12;          // The on-board Arduino LED, close to PIN 13.
int beatThreshold = 200;           // Determine which Signal to "count as a beat" and which to ignore.

//PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(beatLED, OUTPUT);
  Timer1.initialize(Period * 1000000);     // initialize timer1
  Timer1.attachInterrupt(callback);           // attaches callback() as a timer overflow interrupt
  Serial.begin(9600);
  Serial.println("Timer Begin");

  /* Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(HeartSensor);   
  pulseSensor.blinkOnPulse(beatLED);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(beatThreshold);   

  if (pulseSensor.begin())
  {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }*/

  pinMode(HeartSensor, INPUT);
}

void callback()
{
  digitalWrite(LED, digitalRead(13) ^ 1);
  Flag = 1;
}

void loop()
{
  while (Flag == 1)
  {
    //digitalWrite(beatLED, digitalRead(12) ^ 1);
    int output = analogRead(HeartSensor);
    if (output >= 550)
    {
      digitalWrite(beatLED, HIGH);
    }
    else 
    {
      digitalWrite(beatLED, LOW);
    }
    Serial.println(output);
    Flag = 0;
  }
}
