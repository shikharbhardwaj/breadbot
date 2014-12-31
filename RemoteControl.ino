#define tsop_pin 12
#define led_pin 13
void setup()
{
  Serial.begin(57600);
  pinMode(tsop_pin,INPUT);
  pinMode(led_pin,OUTPUT);
  pinMode(9,OUTPUT);
  for(int i = 2;i<=8;i++){
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
  }
}
void loop()
  {
  boolean bin[32];                    //boolean consumes less space
  int addr=0, data=0;
  while(pulseIn(tsop_pin,LOW)<4000){
        byte brightness;
        if (Serial.available()) {
          brightness = Serial.read();
          for(int i = 0;i<=brightness;i++){
            analogWrite(9, i);
            delay(50);
          }
          Serial.println(brightness);
          Serial.println();
    }
  }  //wait for start bit
  refreshPin();
  digitalWrite(led_pin,HIGH);                 //turn on an led
  for(int i=0; i<32; i++)
  {
    if(pulseIn(tsop_pin,HIGH)>1000)   //store binary values
      bin[i]=1;
    else
      bin[i]=0;
  }
  Serial.print("Data = ");
  for(int i=0;i<8;i++)            //extract data bits
  {
    if(bin[i+16]==1)
      data+=1<<i;
  }
  Serial.println(data);
  Serial.println();
  digitalWrite(led_pin,LOW);      //turn off the led
  if(data==96){
    refreshPin();
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(6,LOW);
    digitalWrite(4,LOW);
    digitalWrite(8,LOW);
  }
  else if(data==97){
    refreshPin();
    digitalWrite(3,LOW);
    digitalWrite(6,LOW);
    digitalWrite(4,LOW);
    digitalWrite(8,LOW);
    digitalWrite(7,LOW);
  }
  else if(data==101){
    refreshPin();
    digitalWrite(5,LOW);
    digitalWrite(3,LOW);
    digitalWrite(6,LOW);
  }
  else if(data==98){
    digitalWrite(5,LOW);
    digitalWrite(4,LOW);
    digitalWrite(8,LOW);
  }
  else if(data==13){
    for(int i = 2;i<=8;i++){
     digitalWrite(i,LOW);
    }
  }
  else if(data==4){
    refreshPin();
    digitalWrite(4,LOW);
    digitalWrite(8,LOW);
  }
  else if(data==5){
    refreshPin();
    digitalWrite(2,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
  }
  else if(data==6){
    refreshPin();
    digitalWrite(2,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(8,LOW);
    digitalWrite(7,LOW);
  }
  else if(data==8){
    refreshPin();
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(8,LOW);
    digitalWrite(3,LOW);
  }
  else if(data==9){
    refreshPin();
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(5,LOW);
    digitalWrite(8,LOW);
    digitalWrite(7,LOW);    
  }
  else if(data==10){
    refreshPin();
    for(int i = 2;i<=8;i++){
      digitalWrite(i,LOW);
    }
    digitalWrite(4,HIGH);
  }
  else if(data==12){
    refreshPin();
    digitalWrite(2,LOW);
    digitalWrite(4,LOW);
    digitalWrite(8,LOW);    
  }
  else if(data==14){
     for(int i = 2;i<=8;i++){
      digitalWrite(i,LOW);
    }
    digitalWrite(6,HIGH);
  }
  else if(data==17){
     for(int i = 2;i<=8;i++){
      digitalWrite(i,LOW);
     }    
     digitalWrite(5,HIGH);
  }
}
void refreshPin(){
  for(int i = 2;i<=8;i++){
    digitalWrite(i,HIGH);
  }
}