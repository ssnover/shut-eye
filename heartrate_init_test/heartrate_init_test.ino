
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include "TimerOne.h"
#include <PulseSensorPlayground.h>    // Includes the PulseSensorPlayground Library.   

const int LED = 13;
double Period = .5; //Seconds
auto Flag = 0;

const int HeartSensor = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int beatLED = 12;          // The on-board Arduino LED, close to PIN 13.
int beatThreshold = 200;           // Determine which Signal to "count as a beat" and which to ignore.

PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

void setup()
{
  pinMode(LED, OUTPUT);
  Timer1.initialize(Period * 1000000);     // initialize timer1
  Timer1.attachInterrupt(callback);           // attaches callback() as a timer overflow interrupt
  Serial.begin(9600);
  Serial.println("Timer Begin");

    // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(HeartSensor);   
  pulseSensor.blinkOnPulse(beatLED);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(beatThreshold);   

  if (pulseSensor.begin())
  {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
}

void callback()
{
  digitalWrite(LED, digitalRead(13) ^ 1);

  Flag = 1;
}

void loop()
{
   int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 

  if (pulseSensor.sawStartOfBeat()) 
  {            // Constantly test to see if "a beat happened". 
   Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
   Serial.print("BPM: ");                        // Print phrase "BPM: " 
   Serial.println(myBPM);                        // Print the value inside of myBPM. 
  }
  while (Flag == 1)
  {
    Flag = 0;
  }
}
