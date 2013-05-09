#include "OregonDecoderV2.h"

// add one bit to the packet _data buffer
void
OregonDecoderV2::add_bit(char	value)
{
    if (!(_total_bits & 0x01))
		_data[_pos] = (_data[_pos] >> 1) | (value ? 0x80 : 00);

    _total_bits++;
    _pos = _total_bits >> 4;

    if (_pos >= sizeof _data)
    {
        Serial.println("sizeof data");
        reset_decoder();
        return;
    }

    _state = OK;
}

	 
char 
OregonDecoderV2::decode(word	width) 
{
	//Serial.println("DecodeV2");
       if (200 <= width && width < 1200) {
            byte w = width >= 700;
 
            switch (_state) {
                case UNKNOWN:
                    if (w != 0) {
                        // Long pulse
                        ++_flip;
                    } else if (w == 0 && 24 <= _flip) {
                        // Short pulse, start bit
                        _flip = 0;
                        _state = T0;
                    } else {
                        // Reset decoder
                        return -1;
                    }
                    break;
                case OK:
                    if (w == 0) {
                        // Short pulse
                        _state = T0;
                    } else {
                        // Long pulse
                        manchester(1);
                    }
                    break;
                case T0:
                    if (w == 0) {
                      // Second short pulse
                        manchester(0);
                    } else {
                        // Reset decoder
                        return -1;
                    }
                    break;
              }
        } else if (width >= 2500  && _pos >= 8) {
            return 1;
        } else {
            return -1;
        }
        return 0;
    }
	
