#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/freeglut.h>
#include <iostream>
#include <ctime>
#include <stdlib.h>

#include "LoadShaders.h"
#include "vgl.h"
#include "vmath.h"
#include "Object.h"
#include "Texture.h"
#include "Shader.h"
#include "Axes.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Camera.h"
#include "Game.h"
#include "Model.h"

#define NUM_TEXTURES 3 // cards and table
#define CAM_MOVE .1
#define NUM_OBJECTS 4

using vmath::mat4;

static class World
{

public:

	World();
	~World();
	void init();							// initializes World
	void display();							// display function
	void keyPress(unsigned char, int, int);
	void arrowInput(int, int, int);
	void draw();							// draw function for entire World
	void initValues();						// initializes values
	void setupTextures();
	
	void idleFunc();

private:
	
	Shader _shader;
	Shader _roomShader;
	PointLight _light;

	std::string _textureFilenames[NUM_TEXTURES];
	Texture * _textures[NUM_TEXTURES];

	Camera _cam;

	bool drawAxes;
	Axes* axes;
	
	GLuint _program;

	//--------------------------------
	// Lighting variables
	//--------------------------------
	float _lightStrength;
	float _lightShinniness;
	vmath::vec3 _lightDirection;

	Color _directionalColor;
	Color _ambientColor;
	//--------------------------------
	
	// Models
	Game _game;
	Player _player;
	Model _terrain;

	int sequenceTest;

	bool PLAY_TURN;
	bool run_game;
};

