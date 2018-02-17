#include "TimerOne.h"


constexpr double Period = 0.1; //loop time in seconds
constexpr int Pseconds = Period * 1000000;
volatile int loopFlag = 0;   //Flag to run main loop when high
const int SensorPin = A0;   //Pin to plug in heart rate
const int MainLoopLED = 13; //Pin for LED to blink every loop
const int HeartBeatLED = 2;  //Pin to visualize the heart rate, updated after reading data
int raw_heartValues[256] = {0}; //Array of all incoming data from heart rate sensor
const int Threshold = 550; //threshold that decided whether the data point is part of a pulse or not
int PulseCount = 0;
int bPm = 0;
int Seconds;
int data_index = 0;
int Average_HR;
void initArray(); //initialize the first 100 samples of the array
int readSensor();   //Gather a single data point from heart rate
int countPulses(int nextData);  //Inputs new data outputs number of pulses
int calc_rate(int pulseCount);
void calc_avg();


double t = 0;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("begin timer");
  Timer1.initialize(Pseconds);        // initialize timer1
  Timer1.attachInterrupt(callback);   // attaches callback() as a timer overflow interrupt
  pinMode(SensorPin, INPUT);          //input data from sensor
  pinMode(MainLoopLED, OUTPUT);       //LED on Arduino is output
  pinMode(HeartBeatLED, OUTPUT);      //external LED for heart rate visualizer is outpu
  //initArray();                        //initialize the first 104 points of the array
}

void callback()
{
  digitalWrite(MainLoopLED, digitalRead(13) ^ 1);
  loopFlag = 1;
  t = t + Period;
  
}

void loop() 

{ 
  while(loopFlag == 1)
  {
    loopFlag = 0;
    raw_heartValues[data_index] = readSensor(); //Gather a single data point and return it
    PulseCount = countPulses(raw_heartValues[data_index]);
    bPm = calc_rate(PulseCount);
    Serial.print("BPM: "); Serial.println(bPm);
    Average_HR = calc_avg(Seconds, bPm);
  }

}

void initArray()
{
  while (loopFlag == 1)
  {
    loopFlag = 0;
    for (int i = 0; i <= 104; i++)
    {
      raw_heartValues[i] = readSensor();
    }
    
  }
}

int readSensor()
{
  int data = 0;
  data = analogRead(SensorPin);
  data_index ++;
  if (data > Threshold && raw_heartValues[(data_index-1)] < Threshold)
  { 
    digitalWrite(HeartBeatLED, HIGH);
  }
  else if (raw_heartValues[data_index] < Threshold && raw_heartValues[data_index-1] > Threshold)
  {
    digitalWrite(HeartBeatLED, LOW);
  } 
  return data;

}

int countPulses(int nextData)
{
  int numPulses = 0;
  for(int i = data_index-100; i < (data_index-1); i++)
  {
    if (raw_heartValues[i] > Threshold && raw_heartValues[i-1] < Threshold && raw_heartValues[i-2] < Threshold && raw_heartValues[i-3] < Threshold )   
    {
      numPulses++;
    } 
  }
  return numPulses++;
}

int calc_rate(int PulseCount)
{
  int Rate = (PulseCount/(Period*100.))*60.;
  return Rate;
}

int calc_avg(int Sec, int bPm)
{
  int avg = 0;
  int numSamples = 0;
  int bPmSum = 0;
  int Bad_Reading_count;
  t = 0;
  while (t <= Sec)
  {
    if (30 < bPm || bPm > 200)
    {
      bPmSum = bPmSum + bPm;
    }
    else 
    {
      Serial.println("Heart Rate Not Detected");
      Bad_Reading_count++;
    }
    numSamples = (Sec / Period) - Bad_Reading_count;
    avg = bPmSum / numSamples;
    return avg;
    }
}

