#include "TimerOne.h"
   
const int LED = 13;
const int beatLED = 12;
const int HeartSensor = A0;
const int beatThreshold = 550;

double Period = .01; //Seconds
int Flag = 0;
double t = 0;
int numBeats;
int Rate = 0;
int output[255] = {0};
uint8_t sampleCounter = 0;
    

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(beatLED, OUTPUT);
  Timer1.initialize(Period * 1000000);     // initialize timer1
  Timer1.attachInterrupt(callback);           // attaches callback() as a timer overflow interrupt
  Serial.begin(9600);
  Serial.println("Timer Begin");
  pinMode(HeartSensor, INPUT);
}

void callback()
{
  digitalWrite(LED, digitalRead(13) ^ 1);
  Flag = 1;
  t = t + Period;
  sampleCounter ++;
 
}

void loop()
{
  while (Flag == 1) //Run through this loop every (Period) seconds 
  {
    //Serial.println(sampleCounter);
    output[sampleCounter] = analogRead(HeartSensor); //Read the sensorer
   // Serial.println(output[sampleCounter]);
    if (output[sampleCounter] > beatThreshold)
    { 
      digitalWrite(beatLED, HIGH);
    }
    else 
    {
      digitalWrite(beatLED, LOW);
    }
    
    if (sampleCounter > 100)
    {
      //int i = sampleCounter;
      //Serial.println(i);
      for(int i = sampleCounter-100; i < (sampleCounter-1); i++)
      {
       if (output[i] > beatThreshold && output[i-1] < beatThreshold && output[i-2] < beatThreshold && output[i-3] < beatThreshold )     {
        numBeats++;
       } 
      }
      Rate = numBeats * 6;
      if (Rate > 200 || Rate < 30)
      {
        Serial.println("Invalid Heart Rate");
      }
      else
      {
        Serial.print(Rate); Serial.println(" Bpm");
      }
       numBeats = 0;
    }
    if (t > 10)
    {
      //while(1);
    }
  }
}
