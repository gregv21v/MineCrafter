#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>

#include "vmath.h"
#include "Shader.h"

class Player
{

public:

	Player();
	~Player();


	//void draw(Shader);


	
	void scale(float);
	void translate(float, float, float);
	void rotate(float, vmath::vec3);
	void updatePosition();
	
	

	void moveLeft(float distance);
	void moveRight(float distance);
	void moveForward(float distance);
	void moveBackwards(float distance);

	vmath::vec4 getPosition();

private:

	vmath::vec4 _position;

	
	vmath::mat4 transform;
	
};

