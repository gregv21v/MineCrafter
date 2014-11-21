#pragma once
#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\freeglut.h>
#include <glm\glm.hpp>
#include <math.h>




class ShadowMap
{


public:
	ShadowMap();
	~ShadowMap();



	void render(); 
	void init(); 

private:
	GLuint _textureID;
	GLuint _fboID;




};

