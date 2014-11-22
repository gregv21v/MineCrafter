#version 330 core

uniform mat4 MVPMatrix;


void main()
{
	gl_Position = MVPMatrix * position;
}