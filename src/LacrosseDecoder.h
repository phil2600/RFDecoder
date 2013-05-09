#pragma once
#ifndef _LACROSSE_DECODER_H_
# define _LACROSSE_DECODER_H_
# include "GlobalDecoder.h"

class LacrosseDecoder : public GlobalDecoder
{
public:
	void	add_bit(char	value);

	// gets called once per incoming pulse with the width in us
    // return values: 0 = keep going, 1 = done, -1 = no match
	char	decode(word	width);
	int		id_;

	
		//void Decode(short state, unsigned int duration);
		//
		//void EncodeBit(unsigned int *& pulsebuffer, byte & pulsebufferlength, bool bitvalue);
		//
		//void EncodeTerminator(unsigned int *& pulsebuffer, byte & pulsebufferlength) ;
		//
		//// This function returns a bitbuffer
		//void EncodeTemperatureCommand(byte device, float value , byte *& bitbuffer, byte &bitbufferlength );
		//void EncodeRainCommand(byte device, int value , byte *& bitbuffer, byte &bitbufferlength );
		//void EncodeHygroCommand(byte device, float value , byte *& bitbuffer, byte &bitbufferlength );

private:
	int		_max_bits;



	/*	unsigned int prevduration;
		float _timeperiodduration;
		float _maxdeviation;
		void (*_TemperatureReceivedEvent)(ProtocolBase * protocol, byte device , float temperature);
		void (*_HygroReceivedEvent)(ProtocolBase * protocol, byte device , float hygro);
		void (*_RainReceivedEvent)(ProtocolBase * protocol, byte device , int rain);*/

};
 
#endif