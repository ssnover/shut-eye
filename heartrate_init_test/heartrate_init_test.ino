#include "TimerOne.h"
   
const int LED = 13;        //OnBoard LED
const int beatLED = 2;    //3mm LED to pulse with heart
const int HeartSensor = A0; //Sensor input
const int beatThreshold = 550; //Threshold to decide puls

double Period = .1; //One loop runs every 0.1 seconds
int loopFlag = 0;
double t = 0;
int numBeats;
int Rate = 0;
int raw_out[255] = {0};
int sample_index = 0;
    

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
  loopFlag = 1;
  t = t + Period;
  sample_index ++;
 
}

void loop()
{
  while (loopFlag == 1) //Run through this loop every (Period) seconds 
  {
    raw_out[sample_index] = analogRead(HeartSensor); //Read the sensorer
    if (raw_out[sample_index] > beatThreshold && raw_out[sample_index-1] < beatThreshold)
    { 
      digitalWrite(beatLED, HIGH);
    }
    else if (raw_out[sample_index] < beatThreshold && raw_out[sample_index-1] > beatThreshold)
    {
      digitalWrite(beatLED, LOW);
    }
    
    if (sample_index > 100)
    {
      for(int i = sample_index-100; i < (sample_index-1); i++)
      {
       if (raw_out[i] > beatThreshold && raw_out[i-1] < beatThreshold && raw_out[i-2] < beatThreshold && raw_out[i-3] < beatThreshold )   
       {
        numBeats++;
       } 
      }
      Rate = numBeats * 6;
      if (Rate < 200 && Rate > 30)
      {
        Serial.print(Rate); Serial.println(" Bpm");
      }
      else
      {
        Serial.println("Invalid Heart Rate");
      }
       numBeats = 0;
    }

    loopFlag = 0;
  }
}
