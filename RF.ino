#include "GlobalDecoder.h"
#include "OregonDecoderV2.h"
#include "OregonDecoderV3.h"
#include "SensorFactory.h"

#define SERIAL_BAUDRATE 57600

unsigned int	RSSIIRQNR  = 1;

volatile word	pulse;
int				Sensor::_total = 0;
SensorFactory	sensor_pool;

void	ext_int_1(void)
{
    static word last;
    // determine the pulse length in microseconds, for either polarity
    pulse = micros() - last;
    last += pulse;
}
 
void	setup()
{
	Serial.begin(SERIAL_BAUDRATE);
    Serial.println("\n-= Poulpe Decoder =-");

	sensor_pool.new_THGR810();
	sensor_pool.new_THN132N();
	sensor_pool.new_THN132N();

    attachInterrupt(RSSIIRQNR, ext_int_1, CHANGE);

    DDRE  &= ~_BV(PE5); //input with pull-up 
    PORTE &= ~_BV(PE5);
}
 
void	loop()
{
	static int i = 0;
    

	cli();
		word old_pulse = pulse;
		pulse = 0;
    sei();
 
	sensor_pool.trigger(old_pulse);
}

