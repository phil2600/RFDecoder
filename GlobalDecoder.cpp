#include "GlobalDecoder.h"

GlobalDecoder::GlobalDecoder()
{ 
	reset_decoder();
}
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
GlobalDecoder::nextPulse(word	width)
{
	if (DONE != _state)
			switch (decode(width))
			{
				case -1:
					reset_decoder();
					break;
				case 1:
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
		get_bit(0);
	_state = DONE;
}	 

void
GlobalDecoder::get_bit(char	value)
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
	get_bit(_flip);
}

// move _bits to the front so that all the _bits are aligned to the end
void
GlobalDecoder::alignTail(byte	max)
{
	// align _bits
	if (_bits != 0) 
	{
		_data[_pos] >>= 8 - _bits;
		for (byte i = 0; i < _pos; ++i)
			_data[i] = (_data[i] >> _bits) | (_data[i+1] << (8 - _bits));
		_bits = 0;
	}
	// optionally shift bytes down if there are too many of 'em
	if (max > 0 && _pos > max) 
	{
		byte n = _pos - max;
		_pos = max;
		for (byte i = 0; i < _pos; ++i)
			_data[i] = _data[i+n];
	}
}

void
GlobalDecoder::reverse_bits()
{
	for (byte i = 0; i < _pos; ++i) 
	{
		byte b = _data[i];
		for (byte j = 0; j < 8; ++j) 
		{
			_data[i] = (_data[i] << 1) | (b & 1);
			b >>= 1;
		}
	}
}

void
GlobalDecoder::reverseNibbles()
{
	for (byte i = 0; i < _pos; ++i)
		_data[i] = (_data[i] << 4) | (_data[i] >> 4);
}

