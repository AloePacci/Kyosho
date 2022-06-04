#ifndef DEFINES
#define DEFINES
//#define USE_CAMERA
#define CAMERA_MODEL_AI_THINKER // Has PSRAM
#include "Arduino.h"
#include "driver/mcpwm.h"
#include <ESP32Servo.h> // ESP32Servo library installed by Library Manager
#include "libraries/RC_ESC/src/ESC.h" // RC_ESP library installed by Library Manager
#include "Adafruit_VL53L0X.h"
#include <MPU9250_asukiaaa.h>
#include "NewPing.h"      // include NewPing library
#define MIN_SPEED 1040 // speed just slow enough to turn motor off
#define MAX_SPEED 1240 // speed where my motor drew 3.6 amps at 12v.

#define PWM_READ_PIN 13
#define PWM_WRITE_PIN 12
#define LED_BUILTIN 4
#define CONTROL_PIN1 15
#define CONTROL_PIN2 17

#ifdef USE_CAMERA
#include "esp_camera.h"
#include <WiFi.h>
#include "other_code/CameraWebServer/camera_pins.h"
const char* ssid = "AloePacci";
const char* password = "alopako99";
WiFiServer server(80);
#endif


void reader(void *pvParameters);
void start_camera();
void configure_pwm();
void set_speed(float speed);
#endif

