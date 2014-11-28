/*
	Andrew wrote all this.
*/

#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/freeglut.h>

#include <glm\glm.hpp>

using namespace std;

class Object
{

public:
	Object();
	~Object();

	virtual void scale(float scaleFactor) = 0;
	virtual void translate(glm::vec3 by) = 0;
	virtual void rotate(float angle, glm::vec3) = 0;
	virtual void updateCenter() = 0;

protected:

	glm::vec4 center;
};

