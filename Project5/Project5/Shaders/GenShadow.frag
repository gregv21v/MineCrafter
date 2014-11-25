#version 330 core
layout (location = 0) out float color;


void main()
{
	color = gl_FragDepth;
}