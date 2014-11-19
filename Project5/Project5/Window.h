#pragma once

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <glm\glm.hpp>
#include <math.h>





class Window
{
public:


	Window();
	~Window();


	void init(int width, int height);
	glm::vec2 normalizeTo(glm::vec2 vect);

	int getWidth();
	int getHeight();



private: 
	int _width, _height;

};

