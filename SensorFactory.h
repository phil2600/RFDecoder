#pragma once
#ifndef _SENSOR_FACTORY_H_
# define _SENSOR_FACTORY_H_
# include "OregonDecoderV2.h"
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
	void	initialize(OregonDecoderV2*	dec);

	// Manipulation methods
	void	print_sensors();
	void	trigger(word	old_pulse);
	void	print_sensor(int	i);
	void	parse_data();
	Sensor*	search_sensor(byte	id, enum type	t);
	Sensor*	add_id(byte	id, enum type	t);
private:
	void	print_data_flow();
	Sensor* get_current_sensor();
	int Sum(byte count, const byte* data);
	byte checksum(const byte* data);
	byte checksum2(const byte* data);
	byte validate_checksum(const byte* data);

};
#endif
