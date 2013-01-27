#pragma once
#ifndef A_SENSOR_FACTORY_H
# define A_SENSOR_FACTORY_H
# include "Sensor.h"
# include "OregonDecoderV2.h"

/*
** Definition of the Abstract Factory
*/
class ASensorFactory
{    
public:
	ASensorFactory(): _index(0)
	{ }

	typedef enum type { eTHGR810, eTHN132N, eLC } e_type;
	
	virtual Sensor* new_THGR810() = 0;
    virtual Sensor* new_THN132N() = 0;
	virtual Sensor* new_LC_sensor() = 0;
	virtual void	print_sensors() = 0;
	virtual void	trigger(word	old_pulse) = 0;
	virtual void	print_sensor(int	i) = 0;
	virtual void	parse_data() = 0;
	virtual Sensor*	search_sensor(byte	id, enum type	t) = 0;
	virtual Sensor*	add_id(byte	id, enum type t) = 0;

	// Method for the Factory instanciation
    static ASensorFactory*	CreateFactory();
	virtual void	initialize(OregonDecoderV2*	dec) = 0;
	
protected:
	
	typedef struct sensors
	{
		Sensor*		_sensor;
		byte		_id;
		e_type		_type;
		int			_used;
	} s_sensors;
	
	int				_index;
	s_sensors		_sensors[10];
	OregonDecoderV2*	_dec;
};

#endif
