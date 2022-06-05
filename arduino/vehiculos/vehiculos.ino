#include "defines.h"
Servo servo;

int val = 1500; //pwm value to input
volatile float RC_Throttle_raw=1500, last=0; // for rc storing and filtering
volatile long Throttle_HIGH_us; // for rc read
Adafruit_VL53L0X lox = Adafruit_VL53L0X();
VL53L0X_RangingMeasurementData_t measure;


void setup() {  
 Serial.begin(115200);
 // Interrupción para canal Thrtottle
 pinMode(RC_PIN, INPUT_PULLUP);
 enableInterrupt(RC_PIN, INT_Throttle, CHANGE);

 //enable distance reader
 if (!lox.begin()) {
    Serial.println(F("Error al iniciar VL53L0X"));
  }else
  Serial.println(F("init VL53L0X"));
 lox.startRangeContinuous(); //read distances continuously

 // start routine for ESC
 servo.attach(MOTOR_PIN);
 servo.writeMicroseconds(1500); // send "stop" signal to ESC.
 delay(2000); // delay to allow the ESC to recognize the stopped signal
 
 //start loop
}

void loop() {
  if (lox.isRangeComplete())
  {
    Serial.print("Distancia (mm): ");
   Serial.println(lox.readRange());
  } 
/*  Serial.print("RC read: ");
  Serial.print(RC_Throttle_raw);*/
  if (rising==false){
    val=val-1;
  }else{
    val=val+1;    
  }
  if(val < 1100 || val > 1900)
  {
    Serial.println("not valid");
  }
  else
  {
    servo.writeMicroseconds(val); // Send signal to ESC.
  }
  if (val<1400){
    rising=true;
  }
  if (val>1600){
    rising=false;
  }
}
