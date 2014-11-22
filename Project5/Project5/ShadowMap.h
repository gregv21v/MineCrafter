#pragma once
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <math.h>

#include "Shader.h"




class ShadowMap
{


public:
	ShadowMap();
	~ShadowMap();

	void init(glm::mat4 frustum);
	void render();
	void generate(); // renders the scene to make the actual shadow map
	void setupFramebuffer();
	void renderFromLight(glm::mat4 frustum);

private:
	GLuint _textureID;
	GLuint _fboID;

	const static int DEPTH_TEXTURE_SIZE = 1024; // tutorial says this is enough 

	int _time;

	glm::vec3 _Y; // i don't exactly know what this is
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

