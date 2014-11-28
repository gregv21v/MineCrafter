#include "Face.h"


Face::Face()
{
	vertices.resize(4);
}


Face::~Face()
{
}


void Face::setVertex(int index, glm::vec4 value)
{
	if (index < 4) // cause you want a face 
		vertices[index] = value;
}