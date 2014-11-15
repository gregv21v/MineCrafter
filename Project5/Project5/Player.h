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


	/*
	void scale(float);
	void translate(float, float, float);
	void rotate(float, vmath::vec3);
	void updateCenter();
	*/
	

	void moveLeft(float distance);
	void moveRight(float distance);
	void moveForward(float distance);
	void moveBackwards(float distance);

	vmath::vec3 getPosition();

private:

	vmath::vec3 _position;

	
	//mat4 transform;
	
};

