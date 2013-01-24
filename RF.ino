#include "GlobalDecoder.h"
#include "OregonDecoder.h"
#include "ASensorFactory.h"

volatile word	pulse;
OregonDecoder	orscV2;
int				Sensor::_total = 0;
ASensorFactory*	sensor_pool;

void	ext_int_1(void)
{
    static word last;
    // determine the pulse length in microseconds, for either polarity
    pulse = micros() - last;
    last += pulse;
}
 
void	setup()
{
	Serial.begin(115200);
    Serial.println("\n-= Poulpe Decoder =-");

	sensor_pool = ASensorFactory::CreateFactory();
	sensor_pool->initialize(&orscV2);
	orscV2.initialize(sensor_pool);
	
	sensor_pool->new_THGR810();
	sensor_pool->new_THGR810();
	sensor_pool->new_THN132N();
	   
    attachInterrupt(1, ext_int_1, CHANGE);

    //DDRE  &= ~_BV(PE5); //input with pull-up 
    //PORTE &= ~_BV(PE5);
}
 
void	loop()
{
    word old_pulse = pulse;

	cli();
		pulse = 0;
    sei();
 
	sensor_pool->trigger(old_pulse);
}
