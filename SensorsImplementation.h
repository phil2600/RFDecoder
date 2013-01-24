#pragma once
#ifndef _DEFINITIONSENSORS_H_
# define _DEFINITIONSENSORS_H_
# include "Arduino.h"
# include "Sensor.h"

/*
** Implementation of the THGR810 Sensor
*/
class THGR810 : public Sensor
{
public:
	THGR810();
    char*	Name();
	void	print();
};

/*
** Implementation of the THN132N Sensor
*/
class THN132N : public Sensor
{
public:
	THN132N();
    char*	Name();
	void	print();
};

/*
** Implementation of a global LaCrosse Sensor
*/
class LaCrosseNoName : public Sensor
{
public:
	LaCrosseNoName();
    char*	Name();
	void	print();
};

#endif
