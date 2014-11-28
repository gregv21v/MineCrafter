#pragma once


#include <vector>

#include <glm\glm.hpp>

#include "Model.h"
#include "Face.h"



class Terrain : public Model
{
public:


	Terrain();
	~Terrain();

	void makeFace(glm::vec3 center);
	void extrude(glm::vec3 direction);
	void endExtrution();

	void draw(Shader shader);


private:

	Face * _selectedFace;

	vector<Face *> _faces;

	bool _extruding;
	
	


};

