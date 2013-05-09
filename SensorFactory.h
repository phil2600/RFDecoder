#pragma once
#ifndef _SENSOR_FACTORY_H_
# define _SENSOR_FACTORY_H_
# include "OregonDecoderV2.h"
# include "OregonDecoderV3.h"
# include "LacrosseDecoder.h"
# include "Sensor.h"


/*************** FIXME ***********************/
# include "SPI.h"
# include "Ethernet.h"
/*************** FIXME ***********************/

/*
** Factory Definition from its abstract
*/
class SensorFactory
{
public:
	SensorFactory(): _index(0) { }
	
	typedef enum type { eTHGR810, eTHN132N, eTHGR228N, eLC } e_type;

	// Getters
    Sensor* new_THGR810();
    Sensor* new_THN132N();
  	Sensor* new_LC_sensor();
	Sensor* new_THGR228N();

	// Manipulation methods
	void	print_sensors();
	void	trigger(word	old_pulse);
	void	print_sensor(int	i);
	void	parse_data(GlobalDecoder*	dec);
	Sensor*	search_sensor(byte	id, enum type	t);
	Sensor*	add_id(byte	id, enum type	t);
	void	send_client();
	void	init_server();
private:
	typedef struct sensors
	{
		Sensor*			_sensor;
		byte			_id;
		e_type			_type;
		int				_used;
		GlobalDecoder*	_decoder;
	} s_sensors;
	
	int					_index;
	s_sensors			_sensors[10];

	void print_data_flow(GlobalDecoder*	dec);
	Sensor*		get_current_sensor(const byte* data);

	const byte*	_data;
	// Checksum
	int		Sum(byte count, const byte* data);
	byte	checksum(const byte* data);
	byte	checksum2(const byte* data);
	byte	validate_checksum(const byte* data);

	EthernetServer*	_server; //FIXME

	EthernetClient	_client; //FIXME
	char			_client_buffer[1024];
	byte			_is_writable;
};
#endif
