#include <FunctionalInterrupt.h>

class pwm_reader
{
public:
    float pwm_value;
	pwm_reader(uint8_t reqPin);
	~pwm_reader();

	void ARDUINO_ISR_ATTR pwm_change();

	void checkPressed();

private:
	const uint8_t PIN;
    volatile uint32_t time_on;
    volatile uint32_t time_off;
};

void reader(void *pvParameters);
