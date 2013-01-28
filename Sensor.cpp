#include "Sensor.h"

/*
** Sensor Global Methods
*/
Sensor::Sensor()
{
    _id = _total++;
}

int
Sensor::get_id()
{
	return _id;
}