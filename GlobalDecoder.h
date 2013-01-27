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

	GlobalDecoder(byte gap =5, byte count =0): lastCrc (0), lastTime (0), repeats (0), minGap (gap), minCount (count) { reset_decoder(); }
	~GlobalDecoder();
		
	bool			nextPulse(word	width);
	bool			is_done() const;
	void 			accomplished();
	const byte 		*get_data(byte	&count) const;
	void 			reset_decoder();
	void 			manchester(char	value);
	//void 			alignTail(byte 	max = 0);
	//void 			reverse_bits();
	//void 			reverseNibbles();
	bool			checkRepeats();

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

	// the following fields are used to deal with duplicate packets
    word lastCrc, lastTime;
    byte repeats, minGap, minCount;

	virtual char	decode(word width) = 0;

	virtual void	add_bit(char	value); 
};

#endif
