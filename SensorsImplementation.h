#pragma once
#ifndef _DEFINITIONSENSORS_H_
# define _DEFINITIONSENSORS_H_
# include "Arduino.h"
# include "Sensor.h"
# include "SPI.h"
# include "Ethernet.h"


#define BYTE2LO(c)           ((c)&0xF)
#define BYTE2HI(c)           (((c)>>4)&0xF)
#define NIBBLES2BYTE(lo, hi) ((((hi)&0xF)<<4)|((lo)&0xF))
#define INSERTLO(c, lo)      (((c)&0xF0)|((lo)&0xF))
#define INSERTHI(c, hi)      (((c)&0xF)|(((hi)&0xF)<<4))


/*
** Implementation of the THGR810 Sensor
*/
class THGR810 : public Sensor
{
public:
    char*	Name();
	void	print(const byte* data);
	void	print_client(const byte* data, EthernetClient client);
};

/*
** Implementation of the THN132N Sensor
*/
class THN132N : public Sensor
{
public:
    char*	Name();
	void	print(const byte* data);
	void	print_client(const byte* data, EthernetClient client);
};

class THGR228N : public Sensor
{
public:
    char*	Name();
	void	print(const byte* data);
	void	print_client(const byte* data, EthernetClient client);
};

/*
** Implementation of a global LaCrosse Sensor
*/
class LaCrosseNoName : public Sensor
{
public:
    char*	Name();
	void	print(const byte* data);
	void	print_client(const byte* data, EthernetClient client);
};

#endif
