/*
	Andrew originially wrote this class.
	Greg worked on all the code related to the blocks and textures.
	Greg added the terrain, lighting, and shadow map functionality in its entirity, but shadow mapping doesn't work correctly, so...
	Alex wrote the code in the mousePassiveMove function that effects the rotation of the camera.
	
*/



#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>

#include <iostream>
#include <ctime>
#include <vector>
#include <stdlib.h>

#include "LoadShaders.h"
#include "vgl.h"
#include "Object.h"
#include "Texture.h"
#include "Shader.h"
#include "Axes.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "Camera.h"
#include "Model.h"
#include "Block.h"
#include "Window.h"
#include "ShadowMap.h"
#include "Player.h"
#include "Terrain.h"




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
	void mouseActiveMove(int x, int y);
	void draw();							// draw function for entire World
	void initValues();						// initializes values
	void setupTextures();
	
	void idleFunc();

private:
	
	Shader _shader, _shadowMapShader;
	Window * _window;
	
	std::vector<Block *> _blocks;
	std::vector<std::string> _textureFilenames;
	std::vector<Texture *> _textures;

	// Mouse Movement variables
	glm::vec2 _lastMousePosition;
	bool _followMouse;
	bool _shadowMapppingEnabled;


	

	bool drawAxes;
	Axes* axes;
	
	GLuint _program;


	
	// Game Objects
	Player _player;
	Model _test;
	Terrain _terrain;
	Camera _cam;

	DirectionalLight _light;
	SpotLight _flashLight;

	ShadowMap _shadowMap;

	int sequenceTest;

	bool PLAY_TURN;
	bool run_game;
};

