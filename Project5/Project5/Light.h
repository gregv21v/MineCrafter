#pragma once


#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "Shader.h"



class Light
{
public:
	Light();

	void render(Shader shader);
	void init();
	void toggle();

//private:
	long double _index;
	bool _isEnabled;
	bool _isLocal;
	bool _isSpot;
	glm::vec3 _ambient;
	glm::vec3 _color;
	glm::vec3 _position;
	glm::vec3 _halfVector;
	glm::vec3 _coneDirection; // for spot lights
	float _spotCosCutoff;
	float _spotExponent;
	float _constantAttenuation;
	float _linearAttenuation;
	float _quadraticAttenuation;


	// Global
	float _shininess;
	float _strength;
	glm::vec3 _eyeDirection;
};

