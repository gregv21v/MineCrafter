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
	translate(move, 0, 0);
}

void Camera::moveRight(float move)
{
	translate(-move, 0, 0);
}

void Camera::panUp(float distance)
{
	_eye.z += distance; 
	updateLookAt();
}
void Camera::panDown(float distance)
{
	_eye.z -= distance;
	updateLookAt();
}
void Camera::panRight(float distance)
{
	_eye.x += distance;
	updateLookAt();
}
void Camera::panLeft(float distance)
{
	_eye.x -= distance;
	updateLookAt();
}



void Camera::init()
{
	_eye[0] = 0;
	_eye[1] = 2;
	_eye[2] = 3;

	_center = glm::vec3(0, 0, 0);
	_up = glm::vec3(0, 1, 0);

	
	//overhead = glm::rotate((float)60, glm::vec3(1, 0, 0)) * glm::rotate((float)-90, glm::vec3(0, 1, 0));
	_view = glm::lookAt(_eye, _center, _up);// *overhead;

	_frustum = glm::frustum((float)-0.2f, (float)0.2f, (float)-0.2f, (float)0.2f, (float)0.3f, (float)100);
}

void Camera::translate(float x, float y, float z)
{
	_transform = glm::translate(glm::mat4(), glm::vec3(x, y, z));
	_view = _view * _transform;

	// _update _center
	_center = glm::vec3(_transform[3]);

}

void Camera::updateLookAt()
{
	_view = glm::lookAt(_eye, _center, _up);
	_view = _view * _transform;


}

void Camera::reverse()
{
	//_eye[2] *= -1;
	//_eye[0] *= -1;

}

// Sets _up uniform for the View Projection Matrix
void Camera::render(Shader shader)
{
	glUniformMatrix4fv(shader.getUniformLocation("VPMatrix"), 1, GL_FALSE, glm::value_ptr(_frustum * _view));
	glUniformMatrix4fv(shader.getUniformLocation("VMatrix"), 1, GL_FALSE, glm::value_ptr(_view));
}


glm::mat4 Camera::getViewFrustum()
{
	return _frustum * _view;
}