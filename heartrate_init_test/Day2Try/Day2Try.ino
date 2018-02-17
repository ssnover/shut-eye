#include "TimerOne.h"

   
const int LED = 13;
const int beatLED = 2;
const int HeartSensor = A0;
const int beatThreshold = 550;

double Period = .01; //Seconds
int Flag = 0;
double t = 0;
int numBeats;
int Rate = 0;
int raw_out[100];
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
 
}

void loop() 
{
  while (Flag == 1)
  {
    if ( sampleCounter < 100 )
    {
      raw_out[sampleCounter] = analogRead(HeartSensor); //read sensor 100 time through
      if (raw_out[sampleCounter] > beatThreshold && raw_out[sampleCounter - 1] < beatThreshold)
      {
        digitalWrite(beatLED, HIGH);  
      }
      else if (raw_out[sampleCounter] < beatThreshold && raw_out[sampleCounter - 1] > beatThreshold)
      {
        digitalWrite(beatLED, LOW);
      }
      //Serial.print("Reading 100 Samples: "); Serial.println(sampleCounter);
      Serial.println(raw_out[sampleCounter]);
      sampleCounter++;
    }
    else
    {
      sampleCounter = 0;
    }

   if (t >= 10)
   {
    Serial.println("t = 10 sec");
    while(1);
    }

    Flag = 0;
  }


}


