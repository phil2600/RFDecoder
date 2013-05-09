#pragma once
#ifndef GLOBAL_DECODER_H_
# define GLOBAL_DECODER_H_
# include "Arduino.h"
# include "SingletonDecoder.h"

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
	
	bool			nextPulse(word	width);
	bool			is_done() const;
	void 			accomplished();
	const byte 		*get_data(byte	&count) const;
	const byte 		*get_data() const;
	void 			reset_decoder();
	void 			manchester(char	value);
	bool			checkRepeats();
	
	GlobalDecoder(byte gap = 5, byte count = 0)
		: lastCrc (0), lastTime (0), repeats (0), minGap (gap), minCount (count) { reset_decoder(); }
	~GlobalDecoder();

protected:
	byte 			_total_bits;
	byte 			_bits;
	byte 			_flip;
	byte 			_state;
	byte 			_pos;
	byte 			_data[25];

	virtual char	decode(word width) = 0;
	
	virtual void	add_bit(char	value);
private:
	// the following fields are used to deal with duplicate packets
    word lastCrc, lastTime;
    byte repeats, minGap, minCount;
};

#endif
