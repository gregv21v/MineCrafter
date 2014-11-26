/*
	Andrew Joyal wrote the class originally.
	Alex Deacon added the rotation, then Gregory Venezia modified it so it was more concise.
	Alex, and Greg wrote an equal amount of each of the getter functions.
	Alex wrote all the Eye functions minus the getEye function
*/



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

	glm::vec3 getDirection();
	glm::vec3 getEye();

	

	void init();
	void translate(float x, float y, float z);
	void translate(glm::vec3 direction);
	void rotate(float angle, float x, float y, float z);

	void translateEye(float X, float y, float z);
	void turnEyeX(float angle);
	void turnEyeY(float angle);
	void turnEye(float angle, float x, float y, float z);
	void updateLookAt();
	void reverse();
	void render(Shader);
	glm::mat4 getViewFrustum();
	glm::mat4 getFrustum();
	glm::mat4 getView();
	glm::vec3 getCenter();

	float getFrustumDepth();


private:

	glm::vec3 _center;
	glm::vec3 _up;
	glm::vec3 _eye;

	glm::mat4 _view;
	glm::mat4 _transform;
	glm::mat4 _frustum;

};

