#include "defines.h"
Servo servo;

int motor_speed = 1500; //pwm value to input
volatile float RC_Throttle=1500, last=0; // for rc storing and filtering
volatile long Throttle_HIGH_us, last_rc_read=0; // for rc read
Adafruit_VL53L0X lox = Adafruit_VL53L0X(); //sensor distance object
float raw_distance, distance, l_distance=0;
int reference=100; //initial reference 100 = 0.1meter
#ifdef LOG
volatile long last_log=0;
#endif
#ifdef LOG_TO_FILE
File dataFile;
#endif

void setup() {  
 Serial.begin(9600);
 // Interrupción para canal Thrtottle
 pinMode(RC_PIN, INPUT_PULLUP);
 pinMode(13,OUTPUT); //builtin led
 enableInterrupt(RC_PIN, INT_Throttle, CHANGE);
   
 //enable distance reader
 if (!lox.begin()) {
    Serial.println(F("Err lid"));
  }else
  Serial.println(F("ini lid"));
 lox.startRangeContinuous(); //read distances continuously

 // start routine for ESC
 servo.attach(MOTOR_PIN);
 servo.writeMicroseconds(1500); // send "stop" signal to ESC.
 delay(2000); // delay to allow the ESC to recognize the stopped signal
 
 //start loop
}

void loop() {
  if (lox.isRangeComplete()) //read sensor
  {
    raw_distance = lox.readRange();
    if (raw_distance<700){
      distance = raw_distance * 0.65 + 0.35 * l_distance ;
      l_distance=distance;
    }else{
    distance = 700 * 0.65 + 0.35 * l_distance ;
    l_distance=distance;
    }
  } 
  bool obstacle=false;
  if (distance<600){
     obstacle=true;
     digitalWrite(13,HIGH);
  } else
    digitalWrite(13,LOW);
  
  update_rc(); // change ref if neccesaryç
  if(reference>100){
    if(obstacle==true){
       motor_speed=controller(reference-distance); 
    }else
      motor_speed=(reference-200)*0.14+1520;
  }
  else if(reference==100){
    motor_speed=1500;
  }
  else
    motor_speed=1430;

  if((motor_speed>((reference-200)*0.14+1520)) && (reference>100)){
    motor_speed=(reference-200)*0.14+1520;
  }
  //saturate outputs
  if(motor_speed < MIN_SERVO_OUTPUT)
  {
    motor_speed=MIN_SERVO_OUTPUT;
  }
  else if(motor_speed > MAX_SERVO_OUTPUT)
  {
    motor_speed=MAX_SERVO_OUTPUT;
  }

  set_speed(motor_speed);// Send signal to ESC.
  

  #ifdef LOG
  if (millis()-last_log>100){
  Serial.print(reference);
  Serial.print(",");
  Serial.print(raw_distance);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(",");
  Serial.print(RC_Throttle);
  Serial.print(",");
  Serial.println(motor_speed);
  last_log=millis();
}
  #endif
}
