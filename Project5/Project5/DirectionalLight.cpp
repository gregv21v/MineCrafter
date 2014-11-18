#include "DirectionalLight.h"


DirectionalLight::DirectionalLight() : Light::Light() {}


DirectionalLight::~DirectionalLight() {}




void DirectionalLight::render(Shader shader)
{
	glUniform3f(shader.getUniformLocation("Ambient"), _ambient.red, _ambient.green, _ambient.blue);
	glUniform3f(shader.getUniformLocation("LightColor"), _color.red, _color.green, _color.blue);
	glUniform3f(shader.getUniformLocation("LightDirection"), _direction[0], _direction[1], _direction[2]);
	glUniform3f(shader.getUniformLocation("HalfVector"), _halfVector[0], _halfVector[1], _halfVector[2]);
	glUniform1f(shader.getUniformLocation("Shininess"), _shininess);
	glUniform1f(shader.getUniformLocation("Strength"), _strength);


	if (_on)
		glUniform1f(shader.getUniformLocation("directionalLightingOn"), 1.0);
	else
		glUniform1f(shader.getUniformLocation("directionalLightingOn"), 0.0);
}
