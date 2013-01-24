#pragma once
#ifndef _OREGON_DECODER_H_
# define _OREGON_DECODER_H_
# include "GlobalDecoder.h"

class OregonDecoder : public GlobalDecoder
{
public:
	OregonDecoder();
	~OregonDecoder();

	void	get_bit(char	value);
	char	decode(word	width);
	void	printSerial();
	int		id_;
private:
	
};
 
#endif