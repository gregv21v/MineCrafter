#include "Camera.h"


Camera::Camera()
{
	
}


Camera::~Camera()
{
}

void Camera::camOut(float move)
{
	eye[2] += move;
	update();
}

void Camera::camIn(float move)
{
	eye[2] -= move;
	update();
}

void Camera::camUp(float move)
{
	eye[1] += move;
	update();
}

void Camera::camDown(float move)
{
	eye[1] -= move;
	update();
}

void Camera::camLeft(float move)
{
	eye[0] -= move;
	update();
}

void Camera::camRight(float move)
{
	eye[0] += move;
	update();
}

void Camera::init()
{
	eye[0] = 0;
	eye[1] = 2;
	eye[2] = 3;

	center = vmath::vec3(0, 0, 0);
	up = vmath::vec3(0, 1, 0);

	
	//overhead = vmath::rotate((float)60, vmath::vec3(1, 0, 0)) * vmath::rotate((float)-90, vmath::vec3(0, 1, 0));
	view = vmath::lookat(eye, center, up);// *overhead;

	frustum = vmath::frustum(-0.2, 0.2, -0.2, 0.2, 0.3, 100);
}

void Camera::update()
{
	view = vmath::lookat(eye, center, up);// *overhead;
}

void Camera::setEye(vmath::vec3 eye)
{

}

void Camera::reverse()
{
	eye[2] *= -1;
	eye[0] *= -1;

	update();
}

// Sets up uniform for the View Projection Matrix
void Camera::render(Shader shader)
{
	glUniformMatrix4fv(shader.getUniformLocation("VPMatrix"), 1, GL_FALSE, frustum * view);
	glUniformMatrix4fv(shader.getUniformLocation("VMatrix"), 1, GL_FALSE, view);
}