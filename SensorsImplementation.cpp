#include "SensorsImplementation.h"
#include "SingletonDecoder.h"

// ------------------------------------------------------------
// Instanciation for the different sensors of the virtual class
// ------------------------------------------------------------


float 
temperature(const byte*	data)
{
	int sign = (data[6]&0x8) ? -1 : 1;
	float temp = ((data[5] & 0xF0) >> 4) * 10 \
				+ (data[5] & 0xF) \
				+ (float)(((data[4] & 0xF0) >> 4) / 10.0);
	return sign * temp;
}
	 
byte 
humidity(const byte* data)
{
	return (data[7] & 0xF) * 10 \
		+ ((data[7] & 0xF0) >> 4);
}
	 
char 
battery(const byte* data)
{
	return (data[4] & 0x4) ? 'L' : 'H';
}
	 
byte 
channel(const byte* data) //FIXME : (1 << (channel-1))
{
	return BYTE2HI(data[2]);
	//byte channel = 7;
	//switch (data[2])
	//{
	//	case 0x10:
	//		channel = 1;
	//		break;
	//	case 0x20:
	//		channel = 2;
	//		break;
	//	case 0x40:
	//		channel = 3;
	//		break;
	//	case 0x50:
	//		channel = 3;
	//		break;
	//	}
	// 
	//	return channel;
}

/*
** THGR228N
*/

char* 
THGR228N::Name()
{
	return "THGR228N";
}

void
THGR228N::print(const byte* data)
{
	Serial.println(Name());
	Serial.print("\tId: ");
	Serial.println(data[3], HEX);
	Serial.print("\tChannel: ");
	Serial.println(channel(data));
	Serial.print("\tTemp: ");
	Serial.println(temperature(data));
	Serial.print("\tHumidity: ");
	Serial.print(humidity(data));
	Serial.print("\tBat:");
	Serial.println(battery(data)); 
}


/*
** THGR810
*/

char* 
THGR810::Name()
{
	return "THGR810";
}

void
THGR810::print(const byte* data)
{
	Serial.println(Name());
	Serial.print("\tId: ");
	Serial.println(data[3], HEX);
	Serial.print("\tChannel: ");
	Serial.println(channel(data));
	Serial.print("\tTemp: ");
	Serial.println(temperature(data));
	Serial.print("\tHumidity: ");
	Serial.print(humidity(data));
	Serial.print("\tBat:");
	Serial.println(battery(data)); 
}


/*
** THN132N
*/
char* 
THN132N::Name()
{
    return "THN132N";
}

void
THN132N::print(const byte* data)
{
	Serial.println(Name());
	Serial.print("\tId: ");
	Serial.println(data[3], HEX);
	Serial.print("\tChannel: ");
	Serial.println(channel(data));
	Serial.print("\tTemp: ");
	Serial.println(temperature(data));
	Serial.print("\tBat:");
	Serial.println(battery(data)); 
}


/*
** LaCrosseNoName
*/

char* 
LaCrosseNoName::Name()
{
    return "LaCrosseNoName";
}

void
LaCrosseNoName::print(const byte* data)
{
	Serial.print(Name());
	Serial.print(' ');
	Serial.print(data[3], HEX);
	Serial.println();
}
