#include "GlobalDecoder.h"
#include <util/crc16.h>

//GlobalDecoder::GlobalDecoder(byte gap =5, byte count =0)
//{ 
//	reset_decoder();
//}

GlobalDecoder::~GlobalDecoder() {}

void
GlobalDecoder::initialize(ASensorFactory*	sensor_pool)
{
	_sensor_pool = sensor_pool;
}

void
GlobalDecoder::reset_decoder()
{
	_total_bits = 0;
	_bits = 0;
	_pos = 0;
	_flip = 0;
	_state = UNKNOWN;
}

bool 
GlobalDecoder::checkRepeats () 
{
	// calculate the checksum over the current packet
	word crc = ~0;

	for (byte i = 0; i < _pos; ++i)
		crc = _crc16_update(crc, _data[i]);
	
	// how long was it since the last decoded packet
	word now = millis() / 100; // tenths of seconds
	word since = now - lastTime;
	
	// if different crc or too long ago, this cannot be a repeated packet
	if (crc != lastCrc || since > minGap)
		repeats = 0;
	
	// save last values and decide whether to report this as a new packet
	lastCrc = crc;
	lastTime = now;
	
	return repeats++ == minCount;
}

bool
GlobalDecoder::nextPulse(word	width)
{
	if (DONE != _state)
		switch (decode(width))
		{
			case -1: // decoding failed
				reset_decoder();
				break;
			case 1: // decoding finished
				accomplished();
				break;
		}

	return is_done();
}

bool
GlobalDecoder::is_done() const
{ 
	return DONE == _state;
}

void
GlobalDecoder::accomplished()
{
	while (_bits)
		add_bit(0); // padding
	//_state = checkRepeats() ? DONE : UNKNOWN; //FIXME : debug
	_state = DONE;
}	 

void
GlobalDecoder::add_bit(char	value)
{
	_total_bits++;
	byte *ptr = _data + _pos;
	*ptr = (*ptr >> 1) | (value << 7);
	if (++_bits >= 8) 
	{
		_bits = 0;
		if (++_pos >= sizeof (_data))
		{
			reset_decoder();
			return;
		}
	}
	_state = OK;
}

const byte*
GlobalDecoder::get_data(byte	&count) const
{
	count = _pos;
	return _data;
}

// store a bit using Manchester encoding
void
GlobalDecoder::manchester(char	value)
{
	_flip ^= value; // manchester code, long pulse _flips the bit
	add_bit(_flip);
}

// move _bits to the front so that all the _bits are aligned to the end
//void
//GlobalDecoder::alignTail(byte	max)
//{
//	// align _bits
//	if (_bits != 0) 
//	{
//		_data[_pos] >>= 8 - _bits;
//		for (byte i = 0; i < _pos; ++i)
//			_data[i] = (_data[i] >> _bits) | (_data[i+1] << (8 - _bits));
//		_bits = 0;
//	}
//	// optionally shift bytes down if there are too many of 'em
//	if (max > 0 && _pos > max) 
//	{
//		byte n = _pos - max;
//		_pos = max;
//		for (byte i = 0; i < _pos; ++i)
//			_data[i] = _data[i+n];
//	}
//}
//
//void
//GlobalDecoder::reverse_bits()
//{
//	for (byte i = 0; i < _pos; ++i) 
//	{
//		byte b = _data[i];
//		for (byte j = 0; j < 8; ++j) 
//		{
//			_data[i] = (_data[i] << 1) | (b & 1);
//			b >>= 1;
//		}
//	}
//}
//
//void
//GlobalDecoder::reverseNibbles()
//{
//	for (byte i = 0; i < _pos; ++i)
//		_data[i] = (_data[i] << 4) | (_data[i] >> 4);
//}
//
