#include "GlobalDecoder.h"
#include "OregonDecoderV2.h"
#include "ASensorFactory.h"

#define SerialBaudrate 115200
// The datapin defines the pin which is wired-up to the Data-output-pin of the receiver-module.
unsigned int DATAPIN = 14;      // The pin number of the data signal
unsigned int STATUSLEDPIN = 0; // The pin number of the status-led (Sanguino: 0)
// If the receiver-module has a RSSI-output-pin, this pin can be wired-up to only process strongly received signals.
// If the receiver-module does not have a RSSI-output-pin, the data-output-pin can be used as a trigger on every signal (even noise). 
unsigned int RSSIPIN    = 10; // The pin number of the RSSI signal (Sanguino pins: 10, 11, 2)
unsigned int RSSIIRQNR  = 1;  // The irq number of the RSSI pin (Saguino pin=irqnr: 10=0 , 11=1, 2=2)

volatile word	pulse;
OregonDecoderV2	orscV2;
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
	Serial.begin(SerialBaudrate);
    Serial.println("\n-= Poulpe Decoder =-");
	
	sensor_pool = ASensorFactory::CreateFactory();
	sensor_pool->initialize(&orscV2);
	orscV2.initialize(sensor_pool);

	sensor_pool->new_THGR810();
	sensor_pool->new_THGR810();
	//sensor_pool->new_THN132N();
	//sensor_pool->new_THN132N();

    attachInterrupt(RSSIIRQNR, ext_int_1, CHANGE);

    DDRE  &= ~_BV(PE5); //input with pull-up 
    PORTE &= ~_BV(PE5);
}
 
void	loop()
{
    word old_pulse = pulse;

	cli();
		pulse = 0;
    sei();
 
	sensor_pool->trigger(old_pulse);
}
