#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>

#include "vmath.h"
#include "Shader.h"

using vmath::mat4;

class Player
{

public:

	Player();
	~Player();


	void draw(Shader);



	void scale(float);
	void translate(float, float, float);
	void rotate(float, vmath::vec3);
	void updateCenter();



	vmath::vec4 center;

private:

	

	
	mat4 transform;
	
};

