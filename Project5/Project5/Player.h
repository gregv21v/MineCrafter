/*
	Andrew originally wrote this whole class.
	But then Greg modified it and added a few things.
	All the affine transformation functions are Andrews.

*/


#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
	void rotate(float, glm::vec3);
	void updatePosition();
	
	

	void moveLeft(float distance);
	void moveRight(float distance);
	void moveForward(float distance);
	void moveBackwards(float distance);

	glm::vec3 getPosition();

private:

	glm::vec3 _position;
	glm::mat4 _transform;
	
};

