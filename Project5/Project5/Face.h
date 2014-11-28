#pragma once

#include "Model.h"

class Face : public Model
{
public:
	Face();
	~Face();


	void setVertex(int index, glm::vec4 value);



};

