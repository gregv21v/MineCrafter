#version 330 core

uniform mat4 MVPMatrix;

<<<<<<< HEAD
=======
layout (location = 0) in vec4 position;

>>>>>>> origin/Gregory

void main()
{
	gl_Position = MVPMatrix * position;
}