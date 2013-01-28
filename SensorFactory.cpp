#include "SensorFactory.h"
#include "SingletonDecoder.h"
#include "SensorsImplementation.h"

#define IS_THN132N(d)		(d[0] == 0xEA && d[1] == 0x4C)
#define IS_THGR228N(d)		(d[0] == 0x1A && d[1] == 0x2D)
#define IS_THGR810(d) 		(d[0] == 0xFA && d[1] == 0x28)

/*
** Getters for Sensor creation
*/
Sensor* 
SensorFactory::new_THGR810()
{
	_sensors[_index]._sensor = new THGR810();
	_sensors[_index]._type = eTHGR810;
	_sensors[_index]._used = 0;
	_sensors[_index]._id = 0;
	_sensors[_index]._decoder = new OregonDecoderV3();
	return _sensors[_index++]._sensor;
}

Sensor*
SensorFactory::new_THN132N()
{
    _sensors[_index]._sensor = new THN132N();
	_sensors[_index]._type = eTHN132N;
	_sensors[_index]._used = 0;
	_sensors[_index]._id = 0;
	_sensors[_index]._decoder = new OregonDecoderV2();
	return _sensors[_index++]._sensor;
}

Sensor*
SensorFactory::new_THGR228N()
{
    _sensors[_index]._sensor = new THGR228N();
	_sensors[_index]._type = eTHGR228N;
	_sensors[_index]._used = 0;
	_sensors[_index]._id = 0;
	_sensors[_index]._decoder = new OregonDecoderV2();
	return _sensors[_index++]._sensor;
}

Sensor*
SensorFactory::new_LC_sensor()
{
	_sensors[_index]._sensor = new LaCrosseNoName();
	_sensors[_index]._type = eLC;
	_sensors[_index]._used = 0;
	_sensors[_index]._id = 0;
	_sensors[_index]._decoder = NULL;
	return _sensors[_index++]._sensor;
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
	Serial.print(_sensors[i]._sensor->get_id());
	Serial.print(" -> Sensor ");
	Serial.println(_sensors[i]._sensor->Name());
}


void
SensorFactory::trigger(word old_pulse)
{
	if (0 != old_pulse)
		for (int i = 0; i < _index; i++)
		{
			if (_sensors[i]._decoder && _sensors[i]._decoder->nextPulse(old_pulse))
			{
				parse_data(_sensors[i]._decoder);
			}
		}
}


void
SensorFactory::print_data_flow(GlobalDecoder*	dec)
{
	byte		pos;
	const byte* data = dec->get_data(pos);

	for (byte i = 0; i < pos; ++i) 
	{
		Serial.print(BYTE2HI(data[i]), HEX);
		Serial.print(BYTE2LO(data[i]), HEX);
	}
	Serial.println();
}



Sensor*
SensorFactory::get_current_sensor(const byte* data)
{
	Sensor*		tmp = NULL;
	
	if (!validate_checksum(data))
		return NULL;

	if (IS_THN132N(data))
		return search_sensor(data[3], eTHN132N);

	if (IS_THGR228N(data))
		return search_sensor(data[3], eTHGR228N);

	if (data[0] == 0xFF && data[1] == 0xFF)
		return search_sensor(data[3], eLC);

	if (IS_THGR810(data))
		return search_sensor(data[3], eTHGR810);

	return NULL;
}

void
SensorFactory::parse_data(GlobalDecoder*	dec)
{
	
	//print_data_flow(dec); //debug
	Sensor* current = get_current_sensor(dec->get_data());
	if (current)
		current->print(dec->get_data());

	dec->reset_decoder();
}

/*
** List Manipulation
*/
Sensor*	
SensorFactory::search_sensor(byte	id, enum type	t) // FIXME: Add Enumeration with Sensor TYPE
{
	for (int i = 0; i < _index; i++)
		if (_sensors[i]._type == t && _sensors[i]._id == id)
			return _sensors[i]._sensor;

	return add_id(id, t);
}

Sensor*	
SensorFactory::add_id(byte	id, enum type	t) // FIXME: Add Enumeration with Sensor TYPE
{
	for (int i = 0; i < _index; i++)
	{
		if (_sensors[i]._used == 0 && _sensors[i]._type == t)
		{
			_sensors[i]._used = 1;
			_sensors[i]._id = id;
			return _sensors[i]._sensor;
		}
	}

	return NULL;
}


int 
SensorFactory::Sum(byte count, const byte* data)
{
	int s = 0;
	 
	for (byte i = 0; i < count; i++)
	{
		s += (data[i] & 0xF0) >> 4;
		s += (data[i] & 0xF);
	}
	 
	if (int(count) != count)
		s += (data[count] & 0xF0) >> 4;
	 
	return s;
}

byte 
SensorFactory::checksum(const byte* data)
{
	int c = ((data[6] & 0xF0) >> 4) + ((data[7] & 0xF) << 4);
	int s = ((Sum(6, data) + (data[6] & 0xF) - 0xa) & 0xff);
	return s == c; 
}
	 
byte 
SensorFactory::checksum2(const byte* data)
{
	return data[8] == ((Sum(8, data) - 0xa) & 0xff);
}

byte
SensorFactory::validate_checksum(const byte* data)
{
	if (IS_THN132N(data))
		return checksum(data);

	if (IS_THGR228N(data))
		return checksum2(data);

	if (IS_THGR810(data))
		return checksum2(data);

	return 0;
}