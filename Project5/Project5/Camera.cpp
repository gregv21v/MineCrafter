#include "Camera.h"


Camera::Camera()
{
	
}


Camera::~Camera()
{
}

void Camera::moveOut(float move)
{
	translate(0, 0, -move);
}

void Camera::moveIn(float move)
{
	translate(0, 0, move);
}

void Camera::moveUp(float move)
{
	translate(0, move, 0);
}

void Camera::moveDown(float move)
{
	translate(0, -move, 0);
}

void Camera::moveLeft(float move)
{
	translate(-move, 0, 0);
}

void Camera::moveRight(float move)
{
	translate(move, 0, 0);
}

void Camera::panUp(float distance)
{
	rotate(distance, glm::vec3(0, 0, 1));
}
void Camera::panDown(float distance)
{
	rotate(-distance, glm::vec3(0, 0, 1));
}
void Camera::panRight(float distance)
{
	rotate(distance, glm::vec3(1, 0, 0));
}
void Camera::panLeft(float distance)
{
	rotate(-distance, glm::vec3(1, 0, 0));
}



void Camera::init()
{
	_eye[0] = 0;
	_eye[1] = 2;
	_eye[2] = 3;

	center = glm::vec3(0, 0, 0);
	up = glm::vec3(0, 1, 0);

	
	//overhead = glm::rotate((float)60, glm::vec3(1, 0, 0)) * glm::rotate((float)-90, glm::vec3(0, 1, 0));
	view = glm::lookAt(_eye, center, up);// *overhead;

	frustum = glm::frustum((float)-0.2f, (float)0.2f, (float)-0.2f, (float)0.2f, (float)0.3f, (float)100);
}

void Camera::translate(float x, float y, float z)
{
	glm::mat4 transform = glm::translate(glm::mat4(), glm::vec3(x, y, z));
	view = view * transform;

	// update center
}

void Camera::rotate(float angle, glm::vec3 axis)
{
	glm::mat4 vecMatrix;
	vecMatrix[3] += glm::vec4(_eye, 1);
	glm::mat4 rot = glm::rotate(vecMatrix, angle, axis);
	vecMatrix *= rot;

	_eye = glm::vec3(vecMatrix[3]);

	view = glm::lookAt(_eye, center, up);
	view = view * transform;
}

void Camera::reverse()
{
	//_eye[2] *= -1;
	//_eye[0] *= -1;

}

// Sets up uniform for the View Projection Matrix
void Camera::render(Shader shader)
{
	glUniformMatrix4fv(shader.getUniformLocation("VPMatrix"), 1, GL_FALSE, glm::value_ptr(frustum * view));
	glUniformMatrix4fv(shader.getUniformLocation("VMatrix"), 1, GL_FALSE, glm::value_ptr(view));
}