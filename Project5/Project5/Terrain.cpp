#include "Terrain.h"


Terrain::Terrain() : 
	_selectedFace(nullptr),
	_extruding(false)
{

}


Terrain::~Terrain()
{
	for (int i = 0; i < _faces.size(); i++)
	{
		delete _faces[i];
	}
}


void Terrain::makeFace(glm::vec3 center)
{
	// create the 4 vertices equidistant from the center point, and lying on zx-plane, where y = center.y.
	float distanceX = 0.5, distanceZ = 0.5;
	
	if (_selectedFace == nullptr) // only for the first face
	{
		_selectedFace = new Face();
	} 
	else
	{
		_faces.push_back(_selectedFace);
		_selectedFace = new Face();
	}

	// update the vertices
	_selectedFace->setVertex(0, glm::vec4(center.x + distanceX, center.y, center.z + distanceZ, 1.0));
	_selectedFace->setVertex(1, glm::vec4(center.x - distanceX, center.y, center.z + distanceZ, 1.0));
	_selectedFace->setVertex(2, glm::vec4(center.x + distanceX, center.y, center.z - distanceZ, 1.0));
	_selectedFace->setVertex(3, glm::vec4(center.x - distanceX, center.y, center.z - distanceZ, 1.0));

	
	



}
void Terrain::extrude(glm::vec3 direction)
{
	if (_selectedFace != nullptr)
		_selectedFace->translate(direction);
}


void Terrain::endExtrution()
{
	_extruding = false;
}


void Terrain::draw(Shader shader)
{
	for (int i = 0; i < _faces.size(); i++)
	{
		_faces[i]->draw(shader);
	}
}