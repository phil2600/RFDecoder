#pragma once
#ifndef GLOBAL_DECODER_H_
# define GLOBAL_DECODER_H_
# include "Arduino.h"

class ASensorFactory;

class GlobalDecoder
{
public:
	enum 
	{
		UNKNOWN, 
		T0, 
		T1, 
		T2, 
		T3, 
		OK, 
		DONE
	};

	GlobalDecoder();
	~GlobalDecoder();
		
	bool			nextPulse(word	width);
	bool			is_done() const;
	void 			accomplished();
	const byte 		*get_data(byte	&count) const;
	void 			reset_decoder();
	void 			manchester(char	value);
	void 			alignTail(byte 	max = 0);
	void 			reverse_bits();
	void 			reverseNibbles();

	virtual void	printSerial() = 0;
	void			initialize(ASensorFactory*	sensor_pool);
	
protected:
	byte 			_total_bits;
	byte 			_bits;
	byte 			_flip;
	byte 			_state;
	byte 			_pos;
	byte 			_data[25];
	ASensorFactory*	_sensor_pool;

	virtual char	decode(word width) = 0;

	virtual void	get_bit(char	value); 
};

#endif
