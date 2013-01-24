#pragma once
#ifndef _SENSOR_FACTORY_H_
# define _SENSOR_FACTORY_H_
# include "OregonDecoder.h"
# include "Sensor.h"
# include "ASensorFactory.h"

/*
** Factory Definition from its abstract
*/
class SensorFactory : public ASensorFactory
{
public:
	// Getters
    Sensor* new_THGR810();
    Sensor* new_THN132N();
  	Sensor* new_LC_sensor();
	void	initialize(OregonDecoder*	dec);

	// Manipulation methods
	void	print_sensors();
	void	trigger(word	old_pulse);
	void	print_sensor(int	i);
	void	parse_data();
	Sensor*	search_sensor(int	id);
private:
	void	print_data_flow();
	Sensor* get_current_sensor();
};
#endif
