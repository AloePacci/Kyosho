
void INT_Throttle() { //executed interruption rc read
  if (digitalRead(RC_PIN) == HIGH) Throttle_HIGH_us = micros(); //store rising edge
  if (digitalRead(RC_PIN) == LOW)  { //substract falling edge to get up time
    if((micros() - Throttle_HIGH_us)<1000){ //if uptime is lower than minimun discard read
      return;
    }
    RC_Throttle_raw  = (micros() - Throttle_HIGH_us)*0.1+0.9*last; // Apply an EMA filter alpha=0.9
    last=RC_Throttle_raw;
  }
}
