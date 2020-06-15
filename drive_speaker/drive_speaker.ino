#include "sig.h"

const byte ledPin = 13;
const byte startPin=3;
const byte interruptPin = 2;
int count1init=2*wavlen/5; //0;
int count2init=3*wavlen/5; //wavlen/5;
volatile int count1=count1init;
volatile int count2=count2init;
volatile int en=0;

void setup() {
  //DAC Configuration
  analogWrite(DAC0,0);  // Enables DAC0
  analogWrite(DAC1,0);  // Enables DAC0

  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(startPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);
  attachInterrupt(digitalPinToInterrupt(startPin), countchange, CHANGE);

  digitalWrite(13, 0);
  Serial.begin(9600);
}

void loop() {
  
}

void countchange(){
  Serial.write("change \n");
  if(!en){
    count1=count1init;
    count2=count2init;
    en=1;
    digitalWrite(ledPin, 1);
  } else {
    en=0;
    digitalWrite(ledPin, 0);
  }
}
void countstart(){
  Serial.write("start\n");
  count1=count1init;
  count2=count2init;
  en=1;
  digitalWrite(ledPin, 1);
}
void countend(){
  Serial.write("end\n");
  en=0;
  digitalWrite(ledPin, 0);
}
void blink() {
  if(en>0){
    int data1=wav[count1]/2;
    int data2=wav[count2]/2;
    //Write the DACs
    dacc_set_channel_selection(DACC_INTERFACE, 0);       //select DAC channel 0
    dacc_write_conversion_data(DACC_INTERFACE, data1); //write on DAC
    dacc_set_channel_selection(DACC_INTERFACE, 1);       //select DAC channel 1
    dacc_write_conversion_data(DACC_INTERFACE, data2);//write on DAC
    
    count1=(count1+1)%wavlen;
    count2=(count2+1)%wavlen;
  } else {
    dacc_set_channel_selection(DACC_INTERFACE, 0);       //select DAC channel 0
    dacc_write_conversion_data(DACC_INTERFACE, 0); //write on DAC
    dacc_set_channel_selection(DACC_INTERFACE, 1);       //select DAC channel 1
    dacc_write_conversion_data(DACC_INTERFACE, 0);//write on DAC
  }
}
