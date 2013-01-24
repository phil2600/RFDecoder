#include "SingletonDecoder.h"

void
SingletonDecoder::setValue(OregonDecoder*	decoder) 
{
	_value = decoder; 
}
  
OregonDecoder* 
SingletonDecoder::getValue() 
{ 
	return _value; 
}

SingletonDecoder*
SingletonDecoder::getInstance()
{
	if (NULL == _singleton)
		_singleton =  new SingletonDecoder;

	return _singleton;
}

void 
SingletonDecoder::kill()
{
	if (NULL != _singleton)
	{
		delete _singleton;
		_singleton = NULL;
	}
}

SingletonDecoder *SingletonDecoder::_singleton = NULL;
