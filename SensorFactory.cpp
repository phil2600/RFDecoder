#include "SensorFactory.h"
#include "SingletonDecoder.h"
#include "SensorsImplementation.h"

#define BYTE2LO(c)           ((c)&0xF)
#define BYTE2HI(c)           (((c)>>4)&0xF)
#define NIBBLES2BYTE(lo, hi) ((((hi)&0xF)<<4)|((lo)&0xF))
#define INSERTLO(c, lo)      (((c)&0xF0)|((lo)&0xF))
#define INSERTHI(c, hi)      (((c)&0xF)|(((hi)&0xF)<<4))

void	
SensorFactory::initialize(OregonDecoder*	dec)
{
	_dec = dec;
	SingletonDecoder::getInstance()->setValue(dec);
}


/*
** Getters for Sensor creation
*/
Sensor* 
SensorFactory::new_THGR810()
{
    _sensors[_index] = new THGR810();
	return _sensors[_index++];
}

Sensor*
SensorFactory::new_THN132N()
{
    _sensors[_index] = new THN132N();
	return _sensors[_index++];
}

Sensor*
SensorFactory::new_LC_sensor()
{
    _sensors[_index] = new LaCrosseNoName();
	return _sensors[_index++];
}

/*
** Manipulation methods
*/
void	
SensorFactory::print_sensors()
{
	for (int i = 0; i < _index; i++) 
		print_sensor(i);
}

void	
SensorFactory::print_sensor(int		i)
{
	Serial.print("id ");
	Serial.print(_sensors[i]->get_id());
	Serial.print(" -> Sensor ");
	Serial.println(_sensors[i]->Name());
}


void
SensorFactory::trigger(word old_pulse)
{
	if (0 != old_pulse)
		if (_dec->nextPulse(old_pulse))
			_dec->printSerial();
}


float 
temperature(const byte*	data)
{
	int sign = (data[6]&0x8) ? -1 : 1;
	float temp = ((data[5]&0xF0) >> 4)*10 + (data[5]&0xF) + (float)(((data[4]&0xF0) >> 4) / 10.0);
	return sign * temp;
}
	 
byte 
humidity(const byte* data)
{
	return (data[7]&0xF) * 10 + ((data[6]&0xF0) >> 4);
}
	 
// Ne retourne qu'un apercu de l'etat de la baterie : 10 = faible
byte 
battery(const byte* data)
{
	return (data[4] & 0x4) ? 10 : 90;
}
	 
byte 
channel(const byte* data)
{
	byte channel;
	switch (data[2])
	{
		case 0x10:
			channel = 1;
			break;
		case 0x20:
			channel = 2;
			break;
		case 0x40:
			channel = 3;
			break;
		}
	 
		return channel;
}

void
SensorFactory::print_data_flow()
{
	byte		pos;
	const byte* data = _dec->get_data(pos);

	Serial.print(' ');
	for (byte i = 0; i < pos; ++i) 
	{
		Serial.print(BYTE2HI(data[i]), HEX);
		Serial.print(BYTE2LO(data[i]), HEX);
	}
	Serial.print(' ');
}


Sensor*
SensorFactory::get_current_sensor()
{
	byte		pos;
	const byte* data = _dec->get_data(pos);

	if (data[0] == 0xEA && data[1] == 0x4C)
		return NULL;
	if (data[0] == 0xEA && data[1] == 0x4C)
		return NULL;
	data[3];
}

void
SensorFactory::parse_data()
{
	byte		pos;
	const byte* data = _dec->get_data(pos);

	Serial.print("Sensor:");
	
	print_data_flow(); //debug
	
	Sensor* current = get_current_sensor();
	if (data[0] == 0xEA && data[1] == 0x4C)
	{
		Serial.print("[THN132N,...] Id:");
		Serial.print(data[3], HEX);
		Serial.print(" ,Channel:");
		Serial.print(channel(data));
		Serial.print(" ,temp:");
		Serial.print(temperature(data));
		Serial.print(" ,bat:");
		Serial.print(battery(data)); 
		Serial.println();
	}
	// Inside Temp-Hygro : THGR228N,...
	else if(data[0] == 0x1A && data[1] == 0x2D)
	{
		//parse_THGR810();
		Serial.print("[THGR810,...] Id:");
		Serial.print(data[3], HEX);
		Serial.print(", Channel:");
		Serial.print(channel(data));
		Serial.print(", temp:");
		Serial.print(temperature(data));
		Serial.print(", hum:");
		Serial.print(humidity(data));
		Serial.print(", bat:");
		Serial.print(battery(data)); 
		Serial.println();
	}

	_dec->reset_decoder();
}

/*
** List Manipulation
*/
Sensor*	
SensorFactory::search_sensor(int	id)
{
	for (int i = 0; i < _index; i++)
	{

	}
}
