#include "LacrosseDecoder.h"
#include <stdlib.h>

// add one bit to the packet _data buffer
void
LacrosseDecoder::add_bit(char	value)
{
  //      _data[_pos] = (_data[_pos] >> 1) | (value ? 0x80 : 00);
  //      _total_bits++;
  //      _pos = _total_bits >> 3;
  //      if (_pos >= sizeof _data) 
		//{
  //          reset_decoder();
  //          return;
  //      }
  //      _state = OK;
}
//
//// This function returns the bitvalue
//bool GetBit(byte* bitbuffer, byte bitbufferlength , unsigned short bitpos)
//{
//    byte bytepos = bitpos >> 3;
//  
//    if (bytepos >= bitbufferlength || bitbuffer==0) 
//  { 
//    return false;
//  }
//  
//  if ((bitbuffer[bytepos] & (128 >> (bitpos % 8))) != 0) return true;
//  return false;
//}
//
//void SetBit(byte *& bitbuffer, byte & bitbufferlength, byte bitpos, bool value)
//{
//  // Calculate at what byte-position the bit needs to be set or cleared in the byte.
//  int bytepos = bitpos >> 3; // Divide by 8, because 8 bits are stored in one byte
//  //  Is the position outside the current allocated bitbuffer ?
//  if (bytepos>=bitbufferlength)
//  { // Yes, it's outside the current allocated bitbuffer
//	// Increase the size of the bitbuffer to be able to store the bit in the byte.
//	dynamicarrayhelper.SetArrayLength( (void *&)bitbuffer , bytepos + 1 , bitbufferlength , sizeof(byte) );
//  }
//  
//  // Is the position inside the current allocated bitbuffer ?
//  if (bytepos<bitbufferlength)
//  { // Yes
//    byte bitvalue = (128 >> (bitpos % 8));
//	if (value)
//	{ // Set the bit
//		bitbuffer[ bytepos ] |= bitvalue;
//	} else
//	{ // Clear the bit
//		bitbuffer[ bytepos ] &= (~ bitvalue );
//	}
//  }
//}
//
//unsigned int CalculateDeviation(unsigned int duration , unsigned int expectedduration)
//{
//  long deviation = (long)duration ;
//  deviation -= (long)expectedduration;
//  deviation = (deviation<0?-deviation:deviation);
//  return deviation;
//}
//
//bool WithinExpectedDeviation(unsigned int duration , unsigned int expectedduration , unsigned int acceptabledeviation)
//{
//    if (CalculateDeviation(duration, expectedduration)<=acceptabledeviation) return true;
//    return false;
//}
//
//void AddBit(byte *& bitbuffer, byte & bitbufferlength,  byte& bitpos, bool value)
//{
//  SetBit(bitbuffer, bitbufferlength, bitpos, value);
//  bitpos++;
//}

char 
LacrosseDecoder::decode(word	width) 
{
		//if (decoder_bitpos==GetBitstreamLength())
		//{
		//	byte device= GetBit(decoder_bitbuffer,decoder_bitbufferlength, 9 )?4:0; 
		//	device |= GetBit(decoder_bitbuffer,decoder_bitbufferlength, 10 )?2:0; 
		//	device |= GetBit(decoder_bitbuffer,decoder_bitbufferlength, 11 )?1:0; 

		//	if (_BitsstreamReceivedEvent!=0) _BitsstreamReceivedEvent( this , decoder_bitbuffer , decoder_bitpos);
		//	
		//	// c1 and c2 seem to be part of a checksum. Upon a repetition the values in c1 and c2 are flipped. in comparison to the first transmission. 
		//	bool c1 = GetBit(decoder_bitbuffer,decoder_bitbufferlength, 8 ); 
		//	bool c2 = GetBit(decoder_bitbuffer,decoder_bitbufferlength, 26 ); 
		//	
		//	bool c3 = GetBit(decoder_bitbuffer,decoder_bitbufferlength, 47 ); 
		//	bool c4 = GetBit(decoder_bitbuffer,decoder_bitbufferlength, 48 ); 
		//	bool c5 = GetBit(decoder_bitbuffer,decoder_bitbufferlength, 49 ); 
		//	if (device==4)
		//	{
		//		// 39-46 is the reverse of 27-34
		//		int v1 = GetBit(decoder_bitbuffer,decoder_bitbufferlength, 28 )?1024:0; 
		//		v1 |= GetBit(decoder_bitbuffer,decoder_bitbufferlength, 29 )?512:0; 
		//		v1 |= GetBit(decoder_bitbuffer,decoder_bitbufferlength, 30 )?256:0; 
		//		v1 |= GetBit(decoder_bitbuffer,decoder_bitbufferlength, 31 )?128:0; 
		//		v1 |= GetBit(decoder_bitbuffer,decoder_bitbufferlength, 32 )?64:0; 
		//		v1 |= GetBit(decoder_bitbuffer,decoder_bitbufferlength, 33 )?32:0; 
		//		v1 |= GetBit(decoder_bitbuffer,decoder_bitbufferlength, 34 )?16:0; 
		//		v1 |= GetBit(decoder_bitbuffer,decoder_bitbufferlength, 35 )?8:0; 
		//		v1 |= GetBit(decoder_bitbuffer,decoder_bitbufferlength, 36 )?4:0; 
		//		v1 |= GetBit(decoder_bitbuffer,decoder_bitbufferlength, 37 )?2:0; 
		//		v1 |= GetBit(decoder_bitbuffer,decoder_bitbufferlength, 38 )?1:0; 

		//		if (_RainReceivedEvent!=0) _RainReceivedEvent( this , 0 , v1 );
		//	}
		//	
		//	// Temperature device
		//	if (device==0)
		//	{
		//	    // 40-46 is inverse of 28-34 
		//		int v1 = GetBit(decoder_bitbuffer,decoder_bitbufferlength, 28 )?1024:0; 
		//		v1 |= GetBit(decoder_bitbuffer,decoder_bitbufferlength, 29 )?512:0; 
		//		v1 |= GetBit(decoder_bitbuffer,decoder_bitbufferlength, 30 )?256:0; 
		//		v1 |= GetBit(decoder_bitbuffer,decoder_bitbufferlength, 31 )?128:0; 
		//		v1 |= GetBit(decoder_bitbuffer,decoder_bitbufferlength, 32 )?64:0; 
		//		v1 |= GetBit(decoder_bitbuffer,decoder_bitbufferlength, 33 )?32:0; 
		//		v1 |= GetBit(decoder_bitbuffer,decoder_bitbufferlength, 34 )?16:0; 
		//		v1 |= GetBit(decoder_bitbuffer,decoder_bitbufferlength, 35 )?8:0; 
		//		v1 |= GetBit(decoder_bitbuffer,decoder_bitbufferlength, 36 )?4:0; 
		//		v1 |= GetBit(decoder_bitbuffer,decoder_bitbufferlength, 37 )?2:0; 
		//		v1 |= GetBit(decoder_bitbuffer,decoder_bitbufferlength, 38 )?1:0;
		//		Serial.print(" ");
		//		Serial.print(v1,DEC);				
		//		//if (_WindReceivedEvent!=0) _WindReceivedEvent( this , 0 , v1 );
		//	}
		//}
}
