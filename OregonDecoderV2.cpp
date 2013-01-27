#include "OregonDecoderV2.h"
#include "ASensorFactory.h"

OregonDecoderV2::OregonDecoderV2() {}
OregonDecoderV2::~OregonDecoderV2() {}
	 
// add one bit to the packet _data buffer
void
OregonDecoderV2::add_bit(char	value)
{
    if (!(_total_bits & 0x01))
		_data[_pos] = (_data[_pos] >> 1) | (value ? 0x80 : 00);

    _total_bits++;
    _pos = _total_bits >> 4;


  //  if (_pos == 2)
  //  {
  //      // Flow length
  //      _max_bits = 160; // --> This one
 
  //      // Exceptions :
  //      if (_data[0] == 0xEA)
  //      {
		//	if (_data[1] == 0x4C) _max_bits = 136; // TH132N : 68 * 2 --> This one
		//	else if(_data[1] == 0x7C) _max_bits = 240; // UV138 : 120 * 2
  //      }
  //      else if(_data[0] == 0x5A)
		//{
		//	if(_data[1] == 0x5D) _max_bits = 176; // THGR918 : 88 * 2
		//	else if(_data[1] == 0x6D)_max_bits = 192; // BTHR918N : 96 * 2
  //      }
  //      else if(_data[0] == 0x1A  && _data[1] == 0x99)
		//	_max_bits = 176; // WTGR800 : 88 * 2
  //      else if(_data[0] == 0xDA  && _data[1] == 0x78)
		//	_max_bits = 144; // UVN800 : 72 * 2
  //      else if((_data[0] == 0x8A || _data[0] == 0x9A) && _data[1] == 0xEC)
		//	_max_bits = 208; // RTGR328N 104 * 2
  //      else if(_data[0] == 0x2A)
  //      {  
		//	if(_data[1] == 0x19) _max_bits = 184; // RCR800 : 92 * 2
		//	else if(_data[1] == 0x1d) _max_bits = 168; // WGR918 : 84 * 2
  //      }
  //  }
 
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

	        if (200 <= width && width < 1200) {
            byte w = width >= 700;
            switch (_state) {
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
        } else {
            return -1;
        }
        return  _total_bits == 80 ? 1: 0;
    

	//width = _max_bits;
	//if (200 <= width && width < 1200) {
 //       byte w = width >= 700;
 //
 //       switch (_state) 
	//	{
 //           case UNKNOWN:
 //               if (w != 0) {
 //                   // Long pulse
 //                   ++_flip;
 //               } else if (w == 0 && 24 <= _flip) {
 //                   // Short pulse, start bit
 //                   _flip = 0;
 //                   _state = T0;
 //               } else {
 //                   // Reset decoder
 //                   return -1;
 //               }
 //               break;
 //           case OK:
 //               if (w == 0) {
 //                   // Short pulse
 //                   _state = T0;
 //               } else {
 //                   // Long pulse
 //                   manchester(1);
 //               }
 //               break;
 //           case T0:
 //               if (w == 0) {
 //                   // Second short pulse
 //                   manchester(0);
 //               } else {
 //                   // Reset decoder
 //                   return -1;
 //               }
 //               break;
 //           }
 //   } else if (width >= 2500  && _pos >= 8) {
 //       return 1;
 //   } else {
 //       return -1;
 //   }
 //   return 0;
}
	
void
OregonDecoderV2::printSerial()
{
	_sensor_pool->parse_data();
}
