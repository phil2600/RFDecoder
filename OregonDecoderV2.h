#pragma once
#ifndef _OREGON_DECODERV2_H_
# define _OREGON_DECODERV2_H_
# include "GlobalDecoder.h"

class OregonDecoderV2 : public GlobalDecoder
{
public:
	OregonDecoderV2();
	~OregonDecoderV2();

	void	add_bit(char	value);

	// gets called once per incoming pulse with the width in us
    // return values: 0 = keep going, 1 = done, -1 = no match
	char	decode(word	width);
	void	printSerial();
	int		id_;
private:
	int		_max_bits;
};
 
#endif