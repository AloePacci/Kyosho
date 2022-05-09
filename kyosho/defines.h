#ifndef DEFINES
#define DEFINES
//#define USE_CAMERA
#define CAMERA_MODEL_AI_THINKER // Has PSRAM
#include "Arduino.h"
#include "driver/mcpwm.h"

#define PWM_READ_PIN 13
#define PWM_WRITE_PIN 12


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
#endif

