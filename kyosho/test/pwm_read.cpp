#include "defines.h"
class pwm_reader
{
public:
	pwm_reader(uint8_t reqPin) : PIN(reqPin){
		pinMode(PIN, INPUT_PULLUP);
		attachInterrupt(PIN, std::bind(&pwm_reader::pwm_change,this), FALLING);

	}
	~pwm_reader() {
		detachInterrupt(PIN);
	}

	void ARDUINO_ISR_ATTR pwm_change() {
		time_on=1;
	}

	void checkPressed() {
		if (true) {
			Serial.printf("Button on pin %u has been pressed %u times\n", PIN, numberKeyPresses);
			pressed = false;
		}
	}
	float read(){
		return pwm_value;
	}

private:
	const uint8_t PIN;
    volatile uint32_t time_on;
    volatile uint32_t time_off;
    float pwm_value = 0;
};


void reader(void *pvParameters) {
	int a = 0;
}
