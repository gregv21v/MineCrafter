/*
	DirectonalLight.h
	Author: Gregory Venezia
	Date: 10/27/2014
	Course: CSC5210
	Description: A light pointing an a particular direction
*/
#pragma once

#include <glm\glm.hpp>
#include "Shader.h"
#include "Color.h"
#include "Light.h"

class DirectionalLight : public Light 
{
public:
	DirectionalLight();
};

