#version 330 core

uniform mat4 VPMatrix;

layout (location = 0) in vec4 position;
layout (location = 6) in mat4 ModelMatrix;


void main()
{
	gl_Position = VPMatrix * ModelMatrix * position;
}