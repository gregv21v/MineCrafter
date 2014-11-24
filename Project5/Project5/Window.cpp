#include "Window.h"


Window::Window()
{
}


Window::~Window()
{
}


glm::vec2 Window::normalizeTo(glm::vec2 vect)
{
	return glm::vec2(2 * vect[0] / _width, 2 * vect[1] / _height);
}


void Window::init(int width, int height)
{
	_width = width;
	_height = height;

	glutInitWindowSize(_width, _height);
}

int Window::getWidth()
{
	return _width;
}

int Window::getHeight()
{
	return _height;
}
