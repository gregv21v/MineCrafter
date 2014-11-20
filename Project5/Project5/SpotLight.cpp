#include "SpotLight.h"


SpotLight::SpotLight() 
{
	Light::Light();
	_isSpot = true;
	_isLocal = false;
}
