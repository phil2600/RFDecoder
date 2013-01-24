#include "ASensorFactory.h"
#include "SensorFactory.h"

// Sensor Factory Creation by the Abstract Factory
// FIXME : CAN CREATE DIFFERENT FACTORIES depends on an ENUMERATION argument
ASensorFactory* 
ASensorFactory::CreateFactory()
{
	return new SensorFactory();
}
