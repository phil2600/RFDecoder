#include "OregonDecoderV3.h"

// add one bit to the packet _data buffer
void
OregonDecoderV3::add_bit(char	value)
{
        _data[_pos] = (_data[_pos] >> 1) | (value ? 0x80 : 00);
        _total_bits++;
        _pos = _total_bits >> 3;
        if (_pos >= sizeof _data) 
		{
            reset_decoder();
            return;
        }
        _state = OK;
}

	 
char 
OregonDecoderV3::decode(word	width) 
{
	if (200 <= width && width < 1200) 
	{
		byte w = width >= 700;
		switch (_state) 
		{
			case UNKNOWN:
				if (w == 0)
					++_flip;
				else if (32 <= _flip) {
					_flip = 1;
					manchester(1);
				} else
					return -1;
				break;
			case OK:
				if (w == 0)
					_state = T0;
				else
					manchester(1);
				break;
			case T0:
				if (w == 0)
					manchester(0);
				else
					return -1;
				break;
        }
    }
	else
        return -1;

    return  _total_bits == 80 ? 1: 0;
}
