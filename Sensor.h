#pragma once
#ifndef SENSOR_H_
# define SENSOR_H_
# include "GlobalDecoder.h"

/*
** Definition of a Global Sensor
*/
class Sensor 
{
public:
	Sensor();

	//
	// Virtual methods
	//
	virtual char*	Name() = 0;
	virtual void	print(const byte* data) = 0;

	//
	// Global methods
	//
	int				get_id();
protected:
	int				_id;
	static int		_total;
	
};
#endif
