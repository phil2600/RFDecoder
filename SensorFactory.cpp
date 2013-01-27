#include "SensorFactory.h"
#include "SingletonDecoder.h"
#include "SensorsImplementation.h"

#define BYTE2LO(c)           ((c)&0xF)
#define BYTE2HI(c)           (((c)>>4)&0xF)
#define NIBBLES2BYTE(lo, hi) ((((hi)&0xF)<<4)|((lo)&0xF))
#define INSERTLO(c, lo)      (((c)&0xF0)|((lo)&0xF))
#define INSERTHI(c, hi)      (((c)&0xF)|(((hi)&0xF)<<4))

void	
SensorFactory::initialize(OregonDecoderV2*	dec)
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
	_sensors[_index]._sensor = new THGR810();
	_sensors[_index]._type = eTHGR810;
	_sensors[_index]._used = 0;
	_sensors[_index]._id = 0;
	return _sensors[_index++]._sensor;
}

Sensor*
SensorFactory::new_THN132N()
{
    _sensors[_index]._sensor = new THN132N();
	_sensors[_index]._type = eTHN132N;
	_sensors[_index]._used = 0;
	_sensors[_index]._id = 0;
	return _sensors[_index++]._sensor;
}

Sensor*
SensorFactory::new_LC_sensor()
{
	_sensors[_index]._sensor = new LaCrosseNoName();
	_sensors[_index]._type = eLC;
	_sensors[_index]._used = 0;
	_sensors[_index]._id = 0;
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
		if (_dec->nextPulse(old_pulse))
			_dec->printSerial();
}


void
SensorFactory::print_data_flow()
{
	byte		pos;
	const byte* data = _dec->get_data(pos);

	for (byte i = 0; i < pos; ++i) 
	{
		Serial.print(BYTE2HI(data[i]), HEX);
		Serial.print(BYTE2LO(data[i]), HEX);
	}
	Serial.println();
}


Sensor*
SensorFactory::get_current_sensor()
{
	Sensor*		tmp = NULL;
	byte		pos;
	const byte* data = _dec->get_data(pos);
	
	if (!validate_checksum(data))
		return NULL;
	if (data[0] == 0xEA && data[1] == 0x4C)
	{
		tmp = search_sensor(data[3], eTHN132N);
		if (!tmp)
			return add_id(data[3], eTHN132N);
		else
			return tmp;
	}

	if (data[0] == 0x1A && data[1] == 0x2D)
	{
		tmp = search_sensor(data[3], eTHGR810);
		if (!tmp)
			return add_id(data[3], eTHGR810);
		else
			return tmp;
	}

	if (data[0] == 0xFF && data[1] == 0xFF)
	{
		tmp = search_sensor(data[3], eLC);
		if (!tmp)
			return add_id(data[3], eLC);
		else
			return tmp;
	}

	return NULL;
}

void
SensorFactory::parse_data()
{
	byte		pos;
	const byte* data = _dec->get_data(pos);

	Serial.println();
	
	
	
	print_data_flow(); //debug
	Sensor* current = get_current_sensor();
	if (current != NULL)
		current->print(data);
	//else
	//{
	//	Serial.println("NULL Sensor Returned");
	//	Serial.print(current->Name());

	//	for (int i = 0; i < _index; i++)
	//	{
	//			Serial.println();
	//			Serial.println(i);
	//			Serial.print("\tUsed: ");
	//			Serial.println(_sensors[i]._used);
	//			Serial.print("\tType: ");
	//			Serial.print(_sensors[i]._type);
	//			Serial.print("\tID: ");
	//			Serial.println(_sensors[i]._id, HEX);
	//			Serial.print("\tName: ");
	//			Serial.println(_sensors[i]._sensor->Name());
	//			
	//	}

	//}
	//if (data[0] == 0xEA && data[1] == 0x4C)
	//{

	//}
	//// Inside Temp-Hygro : THGR228N,...
	//else if(data[0] == 0x1A && data[1] == 0x2D)
	//{
	//	//parse_THGR810();
	//	Serial.print("[THGR810,...] Id:");
	//	Serial.print(data[3], HEX);
	//	Serial.print(", Channel:");
	//	Serial.print(channel(data));
	//	Serial.print(", temp:");
	//	Serial.print(temperature(data));
	//	Serial.print(", hum:");
	//	Serial.print(humidity(data));
	//	Serial.print(", bat:");
	//	Serial.print(battery(data)); 
	//	Serial.println();
	//}

	_dec->reset_decoder();
}

/*
** List Manipulation
*/
Sensor*	
SensorFactory::search_sensor(byte	id, enum type	t) // FIXME: Add Enumeration with Sensor TYPE
{
	for (int i = 0; i < _index; i++)
	{
		if (_sensors[i]._type == t && _sensors[i]._id == id)
		{
			return _sensors[i]._sensor;
		}
	}
	
	return NULL;
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
	 
	for(byte i = 0; i<count;i++)
	{
		s += (data[i]&0xF0) >> 4;
		s += (data[i]&0xF);
	}
	 
	if(int(count) != count)
		s += (data[count]&0xF0) >> 4;
	 
	return s;
}

byte 
SensorFactory::checksum(const byte* data)
{
	int c = ((data[6]&0xF0) >> 4) + ((data[7]&0xF)<<4);
	int s = ((Sum(6, data) + (data[6]&0xF) - 0xa) & 0xff);
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
	if (data[0] == 0xEA && data[1] == 0x4C)
		return checksum(data);

	if (data[0] == 0x1A && data[1] == 0x2D)
		return checksum2(data); //FIXME : check if good
		return 1;
	return 0;
}