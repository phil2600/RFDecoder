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
	virtual void	print() = 0;

	//
	// Global methods
	//
	GlobalDecoder*  get_dec();
	int				get_id();
	GlobalDecoder*	_dec;
protected:
	int				_id;
	static int		_total;
	
};
#endif
