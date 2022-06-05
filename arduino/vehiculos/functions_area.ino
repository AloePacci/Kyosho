
void INT_Throttle() { //executed interruption rc read
  if (digitalRead(RC_PIN) == HIGH) Throttle_HIGH_us = micros(); //store rising edge
  if (digitalRead(RC_PIN) == LOW)  { //substract falling edge to get up time
    if((micros() - Throttle_HIGH_us)<1000 || (micros() - Throttle_HIGH_us)>2000){ //if uptime is lower than minimun discard read
      return;
    }
    RC_Throttle  = (micros() - Throttle_HIGH_us)*0.1+0.9*last; // Apply an EMA filter alpha=0.9
    last=RC_Throttle;
  }
}

int controller(int error){
  static float last_time=0;
  return 1500-Kp*error;
  last_time=millis();
  }

void set_speed(int raw_speed){
  int motor_speed;
  if(raw_speed>1510){ //avoid dead zone
    motor_speed=map(raw_speed,1500,1650,1550,1650);
  }else if(raw_speed<1490){
    motor_speed=map(raw_speed,1500,1350,1450,1350);
  }else
    motor_speed=1500; //keep vehicle still
  servo.writeMicroseconds(motor_speed); 
}


void update_rc(){
    //RC read for reference changes
  if(RC_Throttle > 1800 && (millis()-last_rc_read)>1000){ // decrease reference
    reference-=100; 
    last_rc_read=millis();
    if (reference<MIN_REFERENCE)
      reference=MIN_REFERENCE;/*
    Serial.print(F("inc ref:"));
    Serial.println(reference);*/
  }else if(RC_Throttle < 1200 && (millis()-last_rc_read)>1000){ // increase reference
    reference+=100; 
    last_rc_read=millis();
    if (reference>MAX_REFERENCE)
      reference=MAX_REFERENCE;/*
    Serial.print(F("dec ref:"));
    Serial.println(reference);*/
  }
}
