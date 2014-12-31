/*
                ---------------------------------------------------------------------
  RobotControl - code for a simple IR remote controlled robot.
                ---------------------------------------------------------------------
                This is the code for the BreadBot project. It is a two wheeled, basic 
                instruction following device. It works for a Samsung remote. I built 
                it using an Arduino on a breadboard based on an Atmega 8.
                ---------------------------------------------------------------------                
                Compiled size : 2,560 bytes
                ---------------------------------------------------------------------
                Written by - Shikhar Bhardwaj             shikharbhardwaj68@gmail.com
                With IR code reading contributions from the Arduino forums.
                ---------------------------------------------------------------------
                You are free to use this code or its modification in your projects.
                But, never forget to mention! :-[
                ---------------------------------------------------------------------
                
                
*/
#define tsop_pin 12  //These are some constants defined to be used as pin numbers
#define led_pin 8    //Not using ints as it consumes precious space!
#define rfwd 2
#define rbwd 3
#define lfwd 4
#define lbwd  5
#define le 10
#define re 9        //Saved 64 bytes!
//Setting the current LED state for the toggle.
int ledState = LOW;
//Setting the current time for the background blink program.
//And yes we need a very large positive number!
unsigned long pastTime=0;
void setup(){
  pinMode(13,OUTPUT);
  pinMode(led_pin,OUTPUT);
  pinMode(tsop_pin,INPUT);
  pinMode(lfwd,OUTPUT);
  pinMode(lbwd,OUTPUT);
  pinMode(rfwd,OUTPUT);
  pinMode(rbwd,OUTPUT);
  pinMode(le,OUTPUT);
  pinMode(re,OUTPUT);
}
void loop(){
  int rec = iread();
  if(rec==96){
    forward();
  }
  else if(rec==97){
    backward();
  }
  else if(rec==104){
    hardStop();
  }
  else if(rec==101){
    left();
  }
  else if(rec==98){
    right();
  }
  else if(rec==5){
    softfwd();
  }
  else if(rec==8){
    hardLeft();
  }
  else if(rec==9){
    hardStop();
  }
  else if(rec==10){
    hardRight();
  }
  else if(rec==13){
    softbwd();
  }
  else if(rec==6){
    rotateRight();
  }
  else if(rec==4){
    rotateLeft();
  }
  else if(rec==12){
    rightbwd();
  }
  else if(rec==14){
    leftbwd();
  }
}
//Motion control v0.2b
//Basic functions for controlling bot motion.
void forward(){
  digitalWrite(lfwd,HIGH);
  digitalWrite(lbwd,LOW);
  digitalWrite(rfwd,HIGH);
  digitalWrite(rbwd,LOW);
  digitalWrite(le,HIGH);
  digitalWrite(re,HIGH);
  delay(10);
}
void backward(){
  digitalWrite(lfwd,LOW);
  digitalWrite(lbwd,HIGH);
  digitalWrite(rfwd,LOW);
  digitalWrite(rbwd,HIGH);
  digitalWrite(le,HIGH);
  digitalWrite(re,HIGH);
  delay(10); 
}
void hardStop(){
  digitalWrite(le,LOW);
  digitalWrite(re,LOW);
}
void left(){
  digitalWrite(lfwd,HIGH);
  digitalWrite(lbwd,LOW);
  digitalWrite(rfwd,HIGH);
  digitalWrite(rbwd,LOW);
  analogWrite(le,64);
  analogWrite(re,255);
  delay(10);
}
void right(){
  digitalWrite(lfwd,HIGH);
  digitalWrite(lbwd,LOW);
  digitalWrite(rfwd,HIGH);
  digitalWrite(rbwd,LOW);
  digitalWrite(le,255);
  digitalWrite(re,64);
  delay(10);
}
void softfwd(){
  digitalWrite(lfwd,HIGH);
  digitalWrite(lbwd,LOW);
  digitalWrite(rfwd,HIGH);
  digitalWrite(rbwd,LOW);
  analogWrite(le,128);
  analogWrite(re,128);
  delay(10);  
}
void rotateRight(){
  digitalWrite(lfwd,HIGH);
  digitalWrite(lbwd,LOW);
  digitalWrite(rfwd,LOW);
  digitalWrite(rbwd,HIGH);
  digitalWrite(le, HIGH);
  digitalWrite(re, HIGH);
  delay(10);   
}
void softbwd(){
  digitalWrite(lfwd,LOW);
  digitalWrite(lbwd,HIGH);
  digitalWrite(rfwd,LOW);
  digitalWrite(rbwd,HIGH);
  analogWrite(le,128);
  analogWrite(re,128);
  delay(10);
}
void hardLeft(){
  digitalWrite(lfwd,LOW);
  digitalWrite(lbwd,LOW);
  digitalWrite(rfwd,HIGH);
  digitalWrite(rbwd,LOW);
  digitalWrite(le,LOW);
  digitalWrite(re,HIGH);
  delay(10); 
}
void hardRight(){
  digitalWrite(lfwd,HIGH);
  digitalWrite(lbwd,LOW);
  digitalWrite(rfwd,LOW);
  digitalWrite(rbwd,LOW);
  digitalWrite(le,HIGH);
  digitalWrite(re,LOW);
  delay(10); 
}
void rotateLeft(){
  digitalWrite(lfwd,LOW);
  digitalWrite(lbwd,HIGH);
  digitalWrite(rfwd,HIGH);
  digitalWrite(rbwd,LOW);
  digitalWrite(le, HIGH);
  digitalWrite(re, HIGH);
  delay(10);
}
void leftbwd(){
  digitalWrite(lfwd, LOW);
  digitalWrite(lbwd, HIGH);
  digitalWrite(rfwd, LOW);
  digitalWrite(rbwd, LOW);
  digitalWrite(le, HIGH);
  digitalWrite(re, LOW);
}
void rightbwd(){
  digitalWrite(lfwd, LOW);
  digitalWrite(lbwd, LOW);
  digitalWrite(rfwd, LOW);
  digitalWrite(rbwd, HIGH);
  digitalWrite(le, LOW);
  digitalWrite(re, HIGH);
}
//IR reading funtion v0.1b
//Credits : Arduino forums!
//Hats off to the person who wrote this!
//Works flawless!
int iread(){
  boolean bin[32];                    //boolean consumes less space
  int data=0;
  while(pulseIn(tsop_pin,LOW)<4000){
    //This is the !bottleneck! part of the code
    //But I still get enough to blink an LED!
    //This blink type does not use delays so
    // that the sensor is always available 
    // for reading. Based on Arduino example : BlinkWithoutDelay
    if(millis()-pastTime>700){
      pastTime=millis();
      if(ledState==LOW)
        ledState=HIGH;
      else
        ledState=LOW;
      digitalWrite(13,ledState);
    }
  }
  digitalWrite(13,HIGH);
  digitalWrite(led_pin,HIGH);                 
  for(int i=0; i<32; i++)
  {
    if(pulseIn(tsop_pin,HIGH)>1000)   //store binary values
      bin[i]=1;
    else
      bin[i]=0;
  }
  for(int i=0;i<8;i++)            //extract data bits
  {
    if(bin[i+16] == 1)
      data+=1<<i;
  }
  digitalWrite(led_pin,LOW);      //turn off the led
  digitalWrite(13,LOW);
  return data;
}
