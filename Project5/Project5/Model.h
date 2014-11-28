/*
	Andrew wrote all this.
*/


#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/freeglut.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "vgl.h"
#include "vmath.h"
#include "vec.h"
#include "Shader.h"
#include "Texture.h"
#include "Color.h"
#include "Object.h"

using namespace std;

class Model : public Object
{

public:

	Model();
	~Model();

	void draw(Shader);
	void init(string);
	void loadObject(string);

	void calculateDimentions();
	float getWidth();
	float getHeight();
	float getDepth();

	void activateTextures(Shader);
	void deactivateTextures();

	void setTexture(Texture*);
	void setColor(Color);

	void scale(float scaleFactor);
	void translate(glm::vec3 by);
	void rotate(float angle, glm::vec3 axis);
	void updateCenter();

	void updateTransform(glm::mat4);
	void updateNormalMat();

	float getMaxY();

	glm::vec4 center;
	glm::mat4 transform;

private:

	
	vector<glm::vec2> texels;
	vector<glm::vec3> normals;
	vector<int> textureIDs;
	Texture* texture;

	//---------------------------------------------------------
	// Declare Data (Vertex Arrays and Buffers)
	//---------------------------------------------------------
	enum { POS_BUFFER, TEXEL_BUFFER, NORMAL_BUFFER, TEXTURE_BUFFER, NUM_BUFFERS };

	GLuint _vaoID;
	GLuint Buffers[NUM_BUFFERS];
	//---------------------------------------------------------

	//---------------------------------------------------------
	// Vertex Attributes
	//---------------------------------------------------------
	enum {
		vPosition, vTexel, vNormal, vTexture, vIsTextured, vIsTransformed,
		vModelMatrix0, vModelMatrix1, vModelMatrix2, vModelMatrix3, vColor,
		vNormalMatrix0, vNormalMatrix1, vNormalMatrix2
	};
	//---------------------------------------------------------

	int isTransformed;
	GLuint isTextured;

	Color color;

	float width;
	float height;
	float depth;

	glm::mat3 nTransform;

	float max_x;
	float max_y;
	float max_z;
	float min_x;
	float min_y;
	float min_z;

protected:

	string name;
	vector<glm::vec4> vertices;
};

