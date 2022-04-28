#include "defines.h"

unsigned int pwm;

//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(115200); // to read serial
	/*
	 * you can read PWM like this
	 * https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/mcpwm.html
	 * */
	mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM_CAP_0, PWM_READ_PIN);
	xTaskCreatePinnedToCore(reader, "PWM_reader", 2048, NULL, 1, NULL, 1);

}

// The loop function is called in an endless loop
void loop()
{
	vTaskDelay(100000);

}


void reader(void *pvParameters) {
	int32_t pos_edge, neg_edge;
	while(true){
		mcpwm_capture_enable(MCPWM_UNIT_0, MCPWM_SELECT_CAP0, MCPWM_NEG_EDGE, 0);
		neg_edge = mcpwm_capture_signal_get_value(MCPWM_UNIT_0, MCPWM_SELECT_CAP0);
		Serial.println(neg_edge);
		mcpwm_capture_enable(MCPWM_UNIT_0, MCPWM_SELECT_CAP0, MCPWM_POS_EDGE, 0);
		pos_edge = mcpwm_capture_signal_get_value(MCPWM_UNIT_0, MCPWM_SELECT_CAP0);
		Serial.println(pos_edge);
		pwm=1000000+(pos_edge-neg_edge);
	}
}
