#include "OregonDecoder.h"
#include "ASensorFactory.h"

OregonDecoder::OregonDecoder() {}
OregonDecoder::~OregonDecoder() {}
//
//float 
//temperature(const byte*	data)
//{
//	int sign = (data[6]&0x8) ? -1 : 1;
//	float temp = ((data[5]&0xF0) >> 4)*10 + (data[5]&0xF) + (float)(((data[4]&0xF0) >> 4) / 10.0);
//	return sign * temp;
//}
//	 
//byte 
//humidity(const byte* data)
//{
//	return (data[7]&0xF) * 10 + ((data[6]&0xF0) >> 4);
//}
//	 
//// Ne retourne qu'un apercu de l'etat de la baterie : 10 = faible
//byte 
//battery(const byte* data)
//{
//	return (data[4] & 0x4) ? 10 : 90;
//}
//	 
//byte 
//channel(const byte* data)
//{
//	byte channel;
//	switch (data[2])
//	{
//		case 0x10:
//			channel = 1;
//			break;
//		case 0x20:
//			channel = 2;
//			break;
//		case 0x40:
//			channel = 3;
//			break;
//		}
//	 
//		return channel;
//}
	 
// add one bit to the packet _data buffer
void
OregonDecoder::get_bit(char	value)
{
    if(!(_total_bits & 0x01))
    {
        _data[_pos] = (_data[_pos] >> 1) | (value ? 0x80 : 00);
    }
    _total_bits++;
    _pos = _total_bits >> 4;
    if(_pos == 2)
    {
        // Taille de trame par défaut (utilisée dans la majorité des sondes)
        int max_bits = 160;
 
        // Exceptions :
        if(_data[0] == 0xEA)
        {
        if(_data[1] == 0x4C) max_bits = 136; // TH132N : 68 * 2
        else if(_data[1] == 0x7C) max_bits = 240; // UV138 : 120 * 2
        }
        else if(_data[0] == 0x5A)
        {
        if(_data[1] == 0x5D) max_bits = 176; // THGR918 : 88 * 2
        else if(_data[1] == 0x6D)max_bits = 192; // BTHR918N : 96 * 2
        }
        else if(_data[0] == 0x1A  && _data[1] == 0x99)
        max_bits = 176; // WTGR800 : 88 * 2
        else if(_data[0] == 0xDA  && _data[1] == 0x78)
        max_bits = 144; // UVN800 : 72 * 2
        else if((_data[0] == 0x8A || _data[0] == 0x9A) && _data[1] == 0xEC)
        max_bits = 208; // RTGR328N 104 * 2
        else if(_data[0] == 0x2A)
        {  
        if(_data[1] == 0x19) max_bits = 184; // RCR800 : 92 * 2
        else if(_data[1] == 0x1d) max_bits = 168; // WGR918 : 84 * 2
        }
    }
 
    if (_pos >= sizeof _data)
    {
        Serial.println("sizeof data");
        reset_decoder();
        return;
    }
    _state = OK;
}

int 
Sum(byte count, const byte* data)
{
	int s = 0;
	 
	for(byte i = 0; i<count;i++)
	{
	s += (data[i]&0xF0) >> 4;
	s += (data[i]&0xF);
	}
	 
	if(int(count) != count)
	s += (data[count]&0xF0) >> 4;
	 
	return s;
}

byte 
checksum(const byte* data)
{
	int c = ((data[6]&0xF0) >> 4) + ((data[7]&0xF)<<4);
	int s = ((Sum(6, data) + (data[6]&0xF) - 0xa) & 0xff);
	return s == c; 
}
	 
byte 
checksum2(const byte* data)
{
	return data[8] == ((Sum(8, data) - 0xa) & 0xff);
}
	 
char 
OregonDecoder::decode(word	width) 
{
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
	
void
OregonDecoder::printSerial()
{
	_sensor_pool->parse_data();
	//byte pos;
	//const byte* data = get_data(pos);
	//Serial.print("OS:");
	//Serial.print(id_);
	//Serial.print(' ');
	//for (byte i = 0; i < pos; ++i) {
	//	Serial.print(data[i] >> 4, HEX);
	//	Serial.print(data[i] & 0x0F, HEX);
	//}
	// 
	//// Outside/Water Temp : THN132N,...
	//if(data[0] == 0xEA && data[1] == 0x4C)
	//{
	//	_sensor_pool->parse_data();
	//	Serial.print("[THN132N,...] Id:");
	//	Serial.print(data[3], HEX);
	//	Serial.print(" ,Channel:");
	//	Serial.print(channel(data));
	//	Serial.print(" ,temp:");
	//	Serial.print(temperature(data));
	//	Serial.print(" ,bat:");
	//	Serial.print(battery(data)); 
	//	Serial.println();
	//}
	//// Inside Temp-Hygro : THGR228N,...
	//else if(data[0] == 0x1A && data[1] == 0x2D)
	//{
	//	Serial.print("[THGR228N,...] Id:");
	//	Serial.print(data[3], HEX);
	//	Serial.print(" ,Channel:");
	//	Serial.print(channel(data));
	//	Serial.print(" ,temp:");
	//	Serial.print(temperature(data));
	//	Serial.print(" ,hum:");
	//	Serial.print(humidity(data));
	//	Serial.print(" ,bat:");
	//	Serial.print(battery(data)); 
	//	Serial.println();
	//}
	// 
	//reset_decoder();
}
