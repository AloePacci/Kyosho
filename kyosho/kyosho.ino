#include "defines.h"

unsigned int pwm;
//ESC myESC(PWM_WRITE_PIN, 1000, 2000, 1000); // ESC_Name (PIN, Minimum Value, Maximum Value, Arm Value)
Adafruit_VL53L0X lox = Adafruit_VL53L0X();
MPU9250_asukiaaa mySensor;
NewPing sonar(15, 14);


//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(115200); // to read serial
	Serial.setDebugOutput(true);
    Serial.println();
    Serial.println("version 2");
    /*Wire.begin(2, 4); //sda, scl
    if (!lox.begin(VL53L0X_I2C_ADDR, false, &Wire))
    {
    Serial.println(F("Failed to boot VL53L0X"));
    }else
	Serial.println(F("boot laser distance"));
    mySensor.setWire(&Wire);
    mySensor.beginAccel();
    mySensor.beginMag();
    Serial.println("boot imu");
	*/
    ledcAttachPin(12, 0);
    ledcSetup(0, 50, 8);
    //pinMode(CONTROL_PIN1, OUTPUT);
    //pinMode(CONTROL_PIN2, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    analogWrite(LED_BUILTIN,10);
    Serial.println("led on");
    //digitalWrite(LED_BUILTIN, HIGH); // set led to on to indicate arming

    //myESC.arm();

    digitalWrite(PWM_WRITE_PIN, HIGH);
    delayMicroseconds(1500);
    digitalWrite(PWM_WRITE_PIN, LOW);
	Serial.println("arm");
	delay(1000); // Wait a second
    analogWrite(LED_BUILTIN,0); // led off to indicate arming completed
    delay(1000);
	Serial.println("speed min");

#ifdef USE_CAMERA
    start_camera(); // esta funcion se conecta al wifi y enciende la camara
#endif
    //configure_pwm(); //esta funcion enciende el PWM y empieza a leer y escribir
}

// The loop function is called in an endless loop
void loop()
{
	Serial.println("loop start");
	int i=MIN_SPEED;
	/*float distance = sonar.ping_median(5);
	Serial.print("spmar read: ");
	Serial.print(distance);
	Serial.println(" cm");
	VL53L0X_RangingMeasurementData_t measure;
	lox.rangingTest(&measure, false);*/
	bool state=false;
	for (int i = MIN_SPEED; i< (MAX_SPEED-MIN_SPEED)+MIN_SPEED; i++){
		for(int j = 0;j<50;j++)
		digitalWrite(PWM_WRITE_PIN, HIGH);
		delayMicroseconds(i);
		digitalWrite(PWM_WRITE_PIN, LOW);
		delay(20000-i); // Wait a second
	}
	//myESC.speed(MIN_SPEED);
	/*
	if (measure.RangeStatus != 4)
	{
	Serial.print("lidar distance saDistance (mm): "); Serial.println(measure.RangeMilliMeter);
	}
	else
	{
	Serial.println("lidar read failed out of range ");
	}
	mySensor.accelUpdate();
	Serial.println("print accel values");
	Serial.println("accelX: " + String(mySensor.accelX()));
	Serial.println("accelY: " + String(mySensor.accelY()));
	Serial.println("accelZ: " + String(mySensor.accelZ()));
	Serial.println("accelSqrt: " + String(mySensor.accelSqrt()));

	mySensor.magUpdate();
	Serial.println("print mag values");
	Serial.println("magX: " + String(mySensor.magX()));
	Serial.println("maxY: " + String(mySensor.magY()));
	Serial.println("magZ: " + String(mySensor.magZ()));
	Serial.println("horizontal direction: " + String(mySensor.magHorizDirection()));*/
	delay(100000);
}


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
//ESTA PARTE DEL CODIGO NO SE MIRA
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////









/*
 * funcion que lee PWM y se ejecuta en otro nucleo
 */

void reader(void *pvParameters) {
	/*
	 * you can read PWM like this
	 * https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/mcpwm.html
	 * */
	int32_t pos_edge, neg_edge;
	while(true){
		//TODO: tenemos que asegurar que tenemos un valor valido
		mcpwm_capture_enable(MCPWM_UNIT_0, MCPWM_SELECT_CAP0, MCPWM_NEG_EDGE, 0);
		neg_edge = mcpwm_capture_signal_get_value(MCPWM_UNIT_0, MCPWM_SELECT_CAP0);
		Serial.println(neg_edge);
		mcpwm_capture_enable(MCPWM_UNIT_0, MCPWM_SELECT_CAP0, MCPWM_POS_EDGE, 0);
		pos_edge = mcpwm_capture_signal_get_value(MCPWM_UNIT_0, MCPWM_SELECT_CAP0);
		Serial.println(pos_edge);
		pwm=1000000+(pos_edge-neg_edge);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

#ifdef USE_CAMERA

void startCameraServer(); //configuracion de la pagina web
//Funcion que inicia la camara y se conecta al wifi
void start_camera(){

	camera_config_t config;
	  config.ledc_channel = LEDC_CHANNEL_0;
	  config.ledc_timer = LEDC_TIMER_0;
	  config.pin_d0 = Y2_GPIO_NUM;
	  config.pin_d1 = Y3_GPIO_NUM;
	  config.pin_d2 = Y4_GPIO_NUM;
	  config.pin_d3 = Y5_GPIO_NUM;
	  config.pin_d4 = Y6_GPIO_NUM;
	  config.pin_d5 = Y7_GPIO_NUM;
	  config.pin_d6 = Y8_GPIO_NUM;
	  config.pin_d7 = Y9_GPIO_NUM;
	  config.pin_xclk = XCLK_GPIO_NUM;
	  config.pin_pclk = PCLK_GPIO_NUM;
	  config.pin_vsync = VSYNC_GPIO_NUM;
	  config.pin_href = HREF_GPIO_NUM;
	  config.pin_sscb_sda = SIOD_GPIO_NUM;
	  config.pin_sscb_scl = SIOC_GPIO_NUM;
	  config.pin_pwdn = PWDN_GPIO_NUM;
	  config.pin_reset = RESET_GPIO_NUM;
	  config.xclk_freq_hz = 20000000;
	  config.pixel_format = PIXFORMAT_JPEG;

	  // if PSRAM IC present, init with UXGA resolution and higher JPEG quality
	  //                      for larger pre-allocated frame buffer.
	  if(psramFound()){
	    config.frame_size = FRAMESIZE_UXGA;
	    config.jpeg_quality = 10;
	    config.fb_count = 2;
	  } else {
	    config.frame_size = FRAMESIZE_SVGA;
	    config.jpeg_quality = 12;
	    config.fb_count = 1;
	  }

	#if defined(CAMERA_MODEL_ESP_EYE)
	  pinMode(13, INPUT_PULLUP);
	  pinMode(14, INPUT_PULLUP);
	#endif

	  // camera init
	  esp_err_t err = esp_camera_init(&config);
	  if (err != ESP_OK) {
	    Serial.printf("Camera init failed with error 0x%x", err);
	    return;
	  }

	  sensor_t * s = esp_camera_sensor_get();
	  // initial sensors are flipped vertically and colors are a bit saturated
	  if (s->id.PID == OV3660_PID) {
	    s->set_vflip(s, 1); // flip it back
	    s->set_brightness(s, 1); // up the brightness just a bit
	    s->set_saturation(s, -2); // lower the saturation
	  }
	  // drop down frame size for higher initial frame rate
	  s->set_framesize(s, FRAMESIZE_QVGA);

	#if defined(CAMERA_MODEL_M5STACK_WIDE) || defined(CAMERA_MODEL_M5STACK_ESP32CAM)
	  s->set_vflip(s, 1);
	  s->set_hmirror(s, 1);
	#endif

	  WiFi.begin(ssid, password);
	  /*
	  WiFi.softAP(ssid, password);

	  IPAddress IP = WiFi.softAPIP();
	  Serial.print("AP IP address: ");
	  Serial.println(IP);

	  server.begin();*/

	  while (WiFi.status() != WL_CONNECTED) {
	    delay(500);
	    Serial.println(WiFi.status());
	  }
	  Serial.println("");
	  Serial.println("WiFi connected");

	  startCameraServer();

	  Serial.print("Camera Ready! Use 'http://");
	  Serial.print(WiFi.localIP());
	  Serial.println("' to connect");
}
#endif

void configure_pwm(){
	mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM_CAP_0, PWM_READ_PIN); //PWM read initialized in unit 0 as read
	//mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM1A, PWM_WRITE_PIN); // PWM write initialized in unit 1 as write
	xTaskCreatePinnedToCore(reader, "PWM_reader", 2048, NULL, 1, NULL, 1); // task for PWM read
	/*mcpwm_config_t pwmconfig;
	pwmconfig.counter_mode=MCPWM_UP_DOWN_COUNTER;
	pwmconfig.frequency=250;
	pwmconfig.duty_mode=MCPWM_DUTY_MODE_0;
	pwmconfig.cmpr_a=90.0;
	pwmconfig.cmpr_b=80.0;
	mcpwm_init(MCPWM_UNIT_1,MCPWM_TIMER_0, &pwmconfig);
	mcpwm_start(MCPWM_UNIT_1,MCPWM_TIMER_0);*/
}
/*

void set_speed(float speed){
	static bool last =true;
	int signal=(int) speed;
	if (speed>0 && last==false){
		digitalWrite(CONTROL_PIN1, HIGH);//set speed forward
	}else if (speed <0 && last == true){
		digitalWrite(CONTROL_PIN1, LOW);//set speed backwards
	}
	//myESC.speed(speed); // speed command goes from 0 to 1000
}*/



