#include "Camera.h"


Camera::Camera()
{
	
}


Camera::~Camera()
{
}

void Camera::moveOut(float move)
{
	translate(0, 0, move);
}

void Camera::moveIn(float move)
{
	translate(0, 0, -move);
}

void Camera::moveUp(float move)
{
	translateEye(0, move, 0);
}

void Camera::moveDown(float move)
{
	translateEye(0, -move, 0);
}

void Camera::moveLeft(float move)
{
	translateEye(move, 0, 0);
}

void Camera::moveRight(float move)
{
	translateEye(-move, 0, 0);
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

glm::vec3 Camera::getDirection()
{
	return _center - _eye;
}
glm::vec3 Camera::getEye()
{
	return _eye;
}




void Camera::init()
{
	_eye = glm::vec3(0, 2, 3);
	_center = glm::vec3(0, 2, 0);
	_up = glm::vec3(0, 1, 0);

	
	_view = glm::lookAt(_eye, _center, _up);

	_frustum = glm::frustum((float)-0.2f, (float)0.2f, (float)-0.2f, (float)0.2f, (float)0.3f, (float)100);
}

void Camera::translate(float x, float y, float z)
{
	_transform = glm::translate(glm::mat4(), glm::vec3(x, y, z));
	_view = _view * _transform;

	_center = glm::vec3(_transform[3]);

	// TOFIX: When translate and rotation happen at the same time the camera 
	// spazes out.
	_eye += _center;


	updateLookAt();

}

void Camera::translate(glm::vec3 direction)
{
	translate(direction.x, direction.y, direction.z);
}


void Camera::rotate(float angle, float x, float y, float z)
{
	glm::mat4 translate = glm::translate(glm::mat4(), _center - _eye);
	glm::mat4 rotate = glm::rotate(glm::mat4(), angle, glm::vec3(x, y, z));


	_center = glm::vec3((rotate * translate)[3]);

	_center += _eye;

}
void Camera::translateEye(float x, float y, float z)
{
	_center += glm::vec3(x, y, z);
	_eye += glm::vec3(x, y, z);


	updateLookAt();
}


void Camera::turnEyeY(float angle)
{


	// bounding "box"
	if (!(_center.y - _eye.y > 2 && angle > 0) && !(_center.y - _eye.y < -2 && angle < 0))
	{
		glm::mat4 translate = glm::translate(glm::mat4(), _center - _eye);
		glm::mat4 rotate = glm::rotate(glm::mat4(), -angle, glm::vec3((_center.z - _eye.z), 0.0, -(_center.x - _eye.x)));

		_center = glm::vec3((rotate * translate)[3]);

		_center += _eye;

		updateLookAt();
	}

}

void Camera::turnEyeX(float angle)
{
	glm::mat4 translate = glm::translate(glm::mat4(), _center - _eye);
	glm::mat4 rotate = glm::rotate(glm::mat4(), angle, glm::vec3(0.0, 1.0, 0.0));
	
	_center = glm::vec3((rotate*translate)[3]);

	_center += _eye;

	updateLookAt();
}

void Camera::updateLookAt()
{
	_view = glm::lookAt(_eye, _center, _up) * _transform;
}

void Camera::reverse()
{
	_eye[2] *= -1;
	_eye[0] *= -1;
}

// Sets _up uniform for the View Projection Matrix
void Camera::render(Shader shader)
{
	glUniformMatrix4fv(shader.getUniformLocation("VPMatrix"), 1, GL_FALSE, glm::value_ptr(_frustum * _view));
	glUniformMatrix4fv(shader.getUniformLocation("ViewMatrix"), 1, GL_FALSE, glm::value_ptr(_view));
	glUniformMatrix4fv(shader.getUniformLocation("ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(_frustum));
}


glm::mat4 Camera::getViewFrustum()
{
	return _frustum * _view;
}

glm::mat4 Camera::getFrustum()
{
	return _frustum;
}


float Camera::getFrustumDepth()
{
	return 100.0f;
}

