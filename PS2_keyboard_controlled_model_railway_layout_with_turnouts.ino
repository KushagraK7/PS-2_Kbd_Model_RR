/*
 * Arduino program for controlling DC model railway layout with a PS/2 keyboard with the 
 * help of an Adafruit V2 motor driver shield.
 * Made by Kushagra, from Tech Build:https://www.youtube.com/channel/UCNy7DyfhSD9jsQEgNwETp9g?sub_confirmation=1
 */
#include <PS2Keyboard.h>//Make sure this library is installed.
#include <Wire.h>
#include <Adafruit_MotorShield.h>//Make sure this library is installed.

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *loco = AFMS.getMotor(1);
Adafruit_DCMotor *turnoutA = AFMS.getMotor(3);
Adafruit_DCMotor *turnoutB = AFMS.getMotor(4);


const int DataPin = 3;
const int IRQpin =  2;

PS2Keyboard keyboard;

int s=0,i;

void motor_go(){
 if(s>=1&&s<=255){
  loco->setSpeed(s);
  loco->run(FORWARD);
 }
 if(s<=-1&&s>=-255){
  loco->setSpeed(-s);
  loco->run(BACKWARD);
 }
 if(s==0){
  loco->setSpeed(s);
  loco->run(RELEASE);
 }
}

void motor_halt(int i){
  if(s>20){
    for(s=s;s>20;s--){
    motor_go();
    delay(i);
    }
 }
  if(s<=20&&s>0&&i<=60){
    for(s=s;s!=0;s--){
    motor_go();
    delay(60);
    }
  }
  if(s<-20){
    for(s=s;s!=-20;s++){
    motor_go();
    delay(i);
    }
  }
  if(s>=-20&&s<0){
    for(s=s;s!=0;s++){
    motor_go();
    delay(60);
    }
  }
}

void turnoutA_side(){
turnoutA->setSpeed(255);
turnoutA->run(FORWARD);
delay(100);
turnoutA->setSpeed(0);
turnoutA->run(RELEASE);
}

void turnoutA_straight(){
turnoutA->setSpeed(255);
turnoutA->run(BACKWARD);
delay(100);
turnoutA->setSpeed(0);
turnoutA->run(RELEASE);
}

void turnoutB_side(){
turnoutB->setSpeed(255);
turnoutB->run(FORWARD);
delay(100);
turnoutB->setSpeed(0);
turnoutB->run(RELEASE);
}

void turnoutB_straight(){
turnoutB->setSpeed(255);
turnoutB->run(BACKWARD);
delay(100);
turnoutB->setSpeed(0);
turnoutB->run(RELEASE);
}
void setup() {
// put your setup code here, to run once:
AFMS.begin();
keyboard.begin(DataPin, IRQpin);
pinMode(10,OUTPUT);
pinMode(9,OUTPUT);
pinMode(8,OUTPUT);
pinMode(13,OUTPUT);

digitalWrite(13,HIGH);
delay(500);
digitalWrite(13,LOW);
}

void loop() {
// put your main code here, to run repeatedly:
if (keyboard.available()) {
  
  // read the next key
  char c = keyboard.read();
  
  // check for some of the special keys
  switch(c){
    case PS2_UPARROW:
    if(s<255){
      s++;
    }
    break;
  

    case PS2_DOWNARROW:
    if(s>-255){
      s--;
    }
      break;
    case PS2_TAB:
      if(s<20&&s>=0){
        for(s=s;s<20;s++){
          motor_go();
          delay(60);
        }
        break;
      }
      if(s==20){
        for(s=s;s!=0;s--){
          motor_go();
          delay(60);
        }
      }
      break; 
    

    case ' ':
    motor_halt(125);
    break;

    case PS2_ENTER:
    motor_halt(60);
    break;

    case '1':
    turnoutA_side();
    break;
 
    case '2':
    turnoutA_straight();
    break;

    case '3':
    turnoutB_side();
    break;
    
    case '4':
    turnoutB_straight();
    break;

    case '5':
    digitalWrite(13,HIGH);
    break;

    case '6':
    digitalWrite(13,LOW);
    break;
    

   Serial.println(i);
  }
  
}
  motor_go();
}
