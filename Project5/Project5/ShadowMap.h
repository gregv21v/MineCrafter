#pragma once
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <math.h>

#include "Shader.h"
#include "Camera.h"




class ShadowMap
{


public:
	ShadowMap();
	~ShadowMap();

	void init(Camera * camera, glm::vec3 lightPosition);
	void render(Shader shader);
	void generate(); // renders the scene to make the actual shadow map
	void setupFramebuffer();
	void startRenderFromLight();
	void endRenderFromLight();

private:
	GLuint _textureID;
	GLuint _fboID;

	// depth texture
	//glm::vec3 material_ambient;
	//glm::vec3 material_diffuse;
	//glm::vec3 material_specular;
	//float material_specular_power;

	const static int DEPTH_TEXTURE_SIZE = 1024; // tutorial says this is enough 

	glm::vec3 _up; // i don't exactly know what this is
	glm::vec3 _lightPosition;
	
	glm::mat4 _sceneModelMatrix;
	glm::mat4 _sceneViewMatrix;
	glm::mat4 _sceneProjectionMatrix;

	glm::mat4 _scaleBiasMatrix;

	glm::mat4 _lightViewMatrix;
	glm::mat4 _lightProjectionMatrix;

	glm::mat4 _shadowMatrix;

	Shader _shader;





};

