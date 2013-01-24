#pragma once
#ifndef A_SENSOR_FACTORY_H
# define A_SENSOR_FACTORY_H
# include "Sensor.h"
# include "OregonDecoder.h"

/*
** Definition of the Abstract Factory
*/
class ASensorFactory
{    
public:
	ASensorFactory(): _index(0)
	{ }

	virtual Sensor* new_THGR810() = 0;
    virtual Sensor* new_THN132N() = 0;
	virtual Sensor* new_LC_sensor() = 0;
	virtual void	print_sensors() = 0;
	virtual void	trigger(word	old_pulse) = 0;
	virtual void	print_sensor(int	i) = 0;
	virtual void	parse_data() = 0;
	virtual Sensor*	search_sensor(int	id) = 0;

	// Method for the Factory instanciation
    static ASensorFactory*	CreateFactory();
	virtual void	initialize(OregonDecoder*	dec) = 0;
	
protected:
	typedef struct sensors
	{
		Sensor*		_sensor;
		int			_id;
		int			_used;
	} s_sensors;
	int				_index;
    //Sensor*			_sensors[10];
	s_sensors		_sensors[10];
	OregonDecoder*	_dec;
};

#endif
