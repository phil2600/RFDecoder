#pragma once
#ifndef _SINGLETONDECODER_H_
# define _SINGLETONDECODER_H_
# include "Arduino.h"

template <typename T>
class Singleton
{
private:
	//Singleton () { }
	//~Singleton () { }

public:
	static T*	getInstance ()
	{
		if (NULL == _singleton)
		{
			Serial.println("New Singleton");
			_singleton = new T;
		}
		else
			Serial.println("Already Created");

		(static_cast<T*> (_singleton))->print();
		return (static_cast<T*> (_singleton));
	}

	static void kill ()
	{
		if (NULL != _singleton)
		{
			delete _singleton;
			_singleton = NULL;
		}
	}

private:
	static T*	_singleton;
};

template <typename T>
T *Singleton<T>::_singleton = NULL;


#endif
