//#define LOG_TO_FILE //Comment this line if you dont wanna log
#define LOG
#include <Servo.h>
#include <EnableInterrupt.h>
#include "Adafruit_VL53L0X.h"

#ifdef LOG_TO_FILE
#include <SPI.h>
#include <SD.h>
#endif

#define MOTOR_PIN 3
#define RC_PIN 2
#define MAX_SERVO_OUTPUT 1620
#define MIN_SERVO_OUTPUT 1380
#define MIN_REFERENCE 0
#define MAX_REFERENCE 600
#define Kp 0.25
#define Kv 1
