#pragma once
#include <GL\glew.h>
#include <GL\GL.h>
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
	void generate(); // renders the scene to make the actual shadow map
	void setupFramebuffer();
	void renderFromLight(glm::mat4 frustum);

private:
	GLuint _textureID;
	GLuint _fboID;

	const static int DEPTH_TEXTURE_SIZE = 10; // don't know what this is for.


	int _time;
	glm::vec3 Y;
	glm::vec3 light_position;
	

	glm::mat4 scene_model_matrix;
	glm::mat4 light_view_matrix;
	glm::mat4 light_projection_matrix;

	Shader shader;





};

