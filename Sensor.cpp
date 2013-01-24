#include "Sensor.h"

/*
** Sensor Global Methods
*/
Sensor::Sensor()
{
    _id = _total++;
}

GlobalDecoder*
Sensor::get_dec()
{
	return _dec;
}

int
Sensor::get_id()
{
	return _id;
}