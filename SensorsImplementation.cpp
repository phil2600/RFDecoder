#include "SensorsImplementation.h"
#include "SingletonDecoder.h"

// ------------------------------------------------------------
// Instanciation for the different sensors of the virtual class
// ------------------------------------------------------------

/*
** THGR810
*/

THGR810::THGR810()
{
	Serial.print(Name());
	_dec = SingletonDecoder::getInstance()->getValue();
}

char* 
THGR810::Name()
{
	return "THGR810";
}

void
THGR810::print()
{

}


/*
** THN132N
*/
THN132N::THN132N()
{	
	Serial.print(Name());
	_dec = SingletonDecoder::getInstance()->getValue();
}

char* 
THN132N::Name()
{
    return "THN132N";
}

void
THN132N::print()
{
	
}


/*
** LaCrosseNoName
*/
LaCrosseNoName::LaCrosseNoName()
{
	Serial.print(Name());
	_dec = SingletonDecoder::getInstance()->getValue();
}

char* 
LaCrosseNoName::Name()
{
    return "LaCrosseNoName";
}

void
LaCrosseNoName::print()
{

}