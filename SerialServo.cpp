
#include "SerialServo.h"


int pos = 0;
int servo = 0;
boolean reading = false;
boolean gotServo = false;

Servo servos[6];

void setup(){

  Serial.begin(115200);

  servos[0].write(90);
  servos[1].write(65);
  servos[2].write(65);
  servos[3].write(170);
  servos[4].write(90);
  servos[5].write(120);

  for(int i = 0; i<6; i++){
    servos[i].attach(i + 4);
    delay(2000);
  }

  delay(500);

}

void loop(){

  if(Serial.available()){
    char c = Serial.read();

    if(c == '<'){
      pos = 0;
      servo = 0;
      reading = true;
      gotServo = false;
    }

    else if(c == '>' && reading == true){
      reading = false;
      if(pos >= 0 && pos <= 180 && servo < 6){
#ifdef DEBUG_SERVO
        Serial.print("Running servo ");
        Serial.print(servo);
        Serial.print(" to position :");
        Serial.println(pos);
#endif
        servos[servo].write(pos);
      }
    }

    else if(c == ',' && !gotServo){
      servo = pos;
      pos = 0;
      gotServo = true;
    }

    else if(c >= '0' && c <= '9' && reading == true){
      pos *= 10;
      pos += (c - '0');
    }
  }
}

