#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/freeglut.h>

#include <iostream>
#include <ctime>
#include <vector>
#include <stdlib.h>

#include "LoadShaders.h"
#include "vgl.h"
#include "vmath.h"
#include "Object.h"
#include "Texture.h"
#include "Shader.h"
#include "Axes.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "Camera.h"
#include "Game.h"
#include "Model.h"
#include "Block.h"
#include "Window.h"




using vmath::mat4;

static class World
{

public:

	World();
	~World();
	void init(Window * window);							// initializes World
	void display();							// display function
	void keyPress(unsigned char, int, int);
	void arrowInput(int, int, int);
	void mousePressed(int button, int state, int x, int y);
	void mousePassiveMove(int x, int y);
	void draw();							// draw function for entire World
	void initValues();						// initializes values
	void setupTextures();
	
	void idleFunc();

private:
	
	Shader _shader;
	Window * _window;
	
	std::vector<Block *> _blocks;
	std::vector<std::string> _textureFilenames;
	std::vector<Texture *> _textures;

	// Mouse Movement variables
	vec2 _lastMousePosition;


	

	bool drawAxes;
	Axes* axes;
	
	GLuint _program;


	
	// Game Objects
	Game _game;
	Player _player;
	Model _terrain;
	Camera _cam;

	DirectionalLight _light;
	SpotLight _flashLight;

	int sequenceTest;

	bool PLAY_TURN;
	bool run_game;
};

