#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#define USE_ARDUINO_INTERRUPTS true    
#include <PulseSensorPlayground.h>        

const int PulseWire = 0;       
const int LED13 = 13;          
int Threshold = 550; 

int a;         
int memory=0;
int count=0;
int current=0;

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
PulseSensorPlayground pulseSensor;

void setup() {   

  Serial.begin(9600);          
  
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);      
  pulseSensor.setThreshold(Threshold);  
  
  if(!accel.begin())   //Check if Accelerometer is responding
  {
    Serial.println("Ooops, no ADXL345 detected ... ");
    while(1);
    
  }
  
  accel.setRange(ADXL345_RANGE_16_G);  //Set range sensitivity for our accelerometer
  
  Serial.println("");
   
   if (pulseSensor.begin()) {
      //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
}



void loop() {
   sensors_event_t event; 
  accel.getEvent(&event);
  
  
  int xp, yp, zp;
  xp=event.acceleration.x;
  yp=event.acceleration.y;
  zp=event.acceleration.z;

  
  if(xp>=-2&&xp<=2)   // Initial position
  {
    current=0;
  } 
  else if(xp>2)       //Movement in forward direction
   {
    current=1;
   }
  else if(xp<-2)      //Movement in reverse direction
  {
    current=-1;
  }
     
  if(current!=memory)
  {
    count++;
  }

 int myBPM = pulseSensor.getBeatsPerMinute();   

if (pulseSensor.sawStartOfBeat()) {            
                        

 
 Serial.print(count*0.05);
 Serial.print(",");
 Serial.print(count);
 Serial.print(",");
 Serial.print(count*0.080467);
 Serial.print(",");
 Serial.println(myBPM);
 Serial.print(",");

 memory=current;
}

  delay(500);                    

}

  
