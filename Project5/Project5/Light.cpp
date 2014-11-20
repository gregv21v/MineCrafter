#include "Light.h"


Light::Light() :
	_isEnabled(true),
	_isLocal(true),
	_isSpot(false),
	_ambient(1.0, 1.0, 1.0),
	_color(1.0, 1.0, 1.0),
	_position(0.0, 0.0, 0.0),
	_halfVector(1.0, 1.0, 1.0),
	_coneDirection(0.0, 0.0, 0.0), // for spot lights
	_spotCosCutoff(5),
	_spotExponent(5),
	_constantAttenuation(2),
	_linearAttenuation(2),
	_quadraticAttenuation(2),

	_index(0),


	// "Global"
	_shininess(2),
	_strength(2), 
	_eyeDirection(0.0, 0.0, 1.0)
{
	
}


void Light::render(Shader shader)
{
	glUniform1i(shader.getUniformLocation("Lights[" + std::to_string(_index) + "].isEnabled"), _isEnabled);
	glUniform1i(shader.getUniformLocation("Lights[" + std::to_string(_index) + "].isLocal"), _isLocal);
	glUniform1i(shader.getUniformLocation("Lights[" + std::to_string(_index) + "].isSpot"), _isSpot);
	glUniform3fv(shader.getUniformLocation("Lights[" + std::to_string(_index) + "].ambient"), 1, glm::value_ptr(_ambient));
	glUniform3fv(shader.getUniformLocation("Lights[" + std::to_string(_index) + "].color"), 1, glm::value_ptr(_color));
	glUniform3fv(shader.getUniformLocation("Lights[" + std::to_string(_index) + "].position"), 1, glm::value_ptr(_position));
	glUniform3fv(shader.getUniformLocation("Lights[" + std::to_string(_index) + "].halfVector"), 1, glm::value_ptr(_halfVector));
	glUniform3fv(shader.getUniformLocation("Lights[" + std::to_string(_index) + "].coneDirection"), 1, glm::value_ptr(_coneDirection));
	glUniform1f(shader.getUniformLocation("Lights[" + std::to_string(_index) + "].spotCosCutoff"), _spotCosCutoff);
	glUniform1f(shader.getUniformLocation("Lights[" + std::to_string(_index) + "].spotExponent"), _spotExponent);
	glUniform1f(shader.getUniformLocation("Lights[" + std::to_string(_index) + "].constantAttenuation"), _constantAttenuation);
	glUniform1f(shader.getUniformLocation("Lights[" + std::to_string(_index) + "].linearAttenuation"), _linearAttenuation);
	glUniform1f(shader.getUniformLocation("Lights[" + std::to_string(_index) + "].quadraticAttenuation"), _quadraticAttenuation);

	glUniform1f(shader.getUniformLocation("Shininess"), _shininess);
	glUniform1f(shader.getUniformLocation("Strength"), _strength);
	glUniform3fv(shader.getUniformLocation("EyeDirection"), 1, glm::value_ptr(_eyeDirection));
}

void Light::toggle()
{
	_isEnabled = !_isEnabled;
}
