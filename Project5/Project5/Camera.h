#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cstdlib>
#include <math.h>

#include "LoadShaders.h"
#include "vgl.h"
#include "vmath.h"


#include "Shader.h"

using vmath::mat4;

class Camera
{
public:
	Camera();
	~Camera();

	void moveOut(float);
	void moveIn(float);
	void moveUp(float);
	void moveDown(float);
	void moveLeft(float);
	void moveRight(float);

	void panUp(float distance);
	void panDown(float distance);
	void panRight(float distance);
	void panLeft(float distance);

	

	void init();
	void translate(float x, float y, float z);
	void updateLookAt();
	void reverse();
	void render(Shader);

private:

	glm::vec3 _center;
	glm::vec3 _up;
	glm::vec3 _eye;

	glm::mat4 _view;
	glm::mat4 _transform;
	glm::mat4 _frustum;
};

