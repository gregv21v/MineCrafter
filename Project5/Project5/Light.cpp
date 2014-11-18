#include "Light.h"


Light::Light() :
	_isEnabled(false),
	_isLocal(false),
	_isSpot(false),
	_ambient(0.0, 0.0, 0.0),
	_color(0.0, 0.1, 0.1),
	_position(0.0, 0.0, 0.0),
	_halfVector(0.0, 0.0, 0.0),
	_coneDirection(0.0, 0.0, 0.0), // for spot lights
	_spotCosCutoff(5),
	_spotExponent(5),
	_constantAttenuation(5),
	_linearAttenuation(5),
	_quadraticAttenuation(5),


	// "Global"
	_shininess(5),
	_strength(5), 
	_eyeDirection(0.0, 1.0, 0.0)
{
	
}


Light::~Light()
{


}


void Light::render(Shader shader)
{
	glUniform1i(shader.getUniformLocation("LightProperties[" + std::to_string(index) + "].isEnabled"), _isEnabled);
	glUniform1i(shader.getUniformLocation("LightProperties[" + std::to_string(index) + "].isLocal"), _isLocal);
	glUniform1i(shader.getUniformLocation("LightProperties[" + std::to_string(index) + "].isSpot"), _isSpot);
	glUniform3fv(shader.getUniformLocation("LightProperties[" + std::to_string(index) + "].ambient"), 3, glm::value_ptr(_ambient));
	glUniform3fv(shader.getUniformLocation("LightProperties[" + std::to_string(index) + "].color"), 3, glm::value_ptr(_color));
	glUniform3fv(shader.getUniformLocation("LightProperties[" + std::to_string(index) + "].position"), 3, glm::value_ptr(_position));
	glUniform3fv(shader.getUniformLocation("LightProperties[" + std::to_string(index) + "].halfVector"), 3, glm::value_ptr(_halfVector));
	glUniform3fv(shader.getUniformLocation("LightProperties[" + std::to_string(index) + "].coneDirection"), 3, glm::value_ptr(_coneDirection));
	glUniform1f(shader.getUniformLocation("LightProperties[" + std::to_string(index) + "].spotCosCutoff"), _spotCosCutoff);
	glUniform1f(shader.getUniformLocation("LightProperties[" + std::to_string(index) + "].spotExponent"), _spotExponent);
	glUniform1f(shader.getUniformLocation("LightProperties[" + std::to_string(index) + "].constantAttenuation"), _constantAttenuation);
	glUniform1f(shader.getUniformLocation("LightProperties[" + std::to_string(index) + "].linearAttenuation"), _linearAttenuation);
	glUniform1f(shader.getUniformLocation("LightProperties[" + std::to_string(index) + "].quadraticAttenuation"), _quadraticAttenuation);

	glUniform1f(shader.getUniformLocation("Shininess"), _shininess);
	glUniform1f(shader.getUniformLocation("Strength"), _strength);
	glUniform3fv(shader.getUniformLocation("EyeDirection"), 3, glm::value_ptr(_eyeDirection));
	
