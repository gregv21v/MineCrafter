#include "World.h"

World::World()
{
	srand(time(NULL));

	sequenceTest = 0;

	axes = new Axes();
	drawAxes = false;

	// Lighting parameters
	
	_directionalColor.red = 0.9;
	_directionalColor.green = 0.9;
	_directionalColor.blue = 0.9;
	_ambientColor.red = 0.7;
	_ambientColor.green = 0.7;
	_ambientColor.blue = 0.4;

	run_game = false;
}

World::~World()
{
	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		delete _textures[i];
	}
}

void World::init()
{
	initValues();
	_cam.init();
	_shader.init("Shaders/PointLight.vert", "Shaders/PointLight.frag");
	//_roomShader.init("RoomVert.vert", "RoomFrag.frag");


	// Antialiasing
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

	glLineWidth(3);

	glEnable(GL_DEPTH_TEST);
	//game.init();
	setupTextures();
}

void World::display()
{
	// clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// draw world
	draw();

	// swap the buffers at the end of the display sequence
	glutSwapBuffers();
}

void World::keyPress(unsigned char key, int x, int y)
{
	Color black;
	black.red = 0;
	black.green = 0;
	black.blue = 0;
	black.alpha = 1;
	Block * block;
	switch (key)
	{
	case 'p':
		block = new Block();
		block->init("Models/Block.obj");
		block->setColor(black);
		blocks.push_back(block);
		break;
	case 'n':

		break;
	case 'g':
		run_game = !run_game;
		break;
	case 'l':
		_light.toggle();
		cout << "Is state: " << _light.isOn() << endl;
		break;
	case 'i':
		_cam.camIn(CAM_MOVE);
		break;
	case 'o':
		_cam.camOut(CAM_MOVE);
		break;
	case 'q':
		drawAxes = !drawAxes;
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void World::arrowInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		_cam.camIn(CAM_MOVE);
		break;
	case GLUT_KEY_DOWN:
		_cam.camOut(CAM_MOVE);
		break;
	case GLUT_KEY_LEFT:
		_cam.camLeft(CAM_MOVE);
		break;
	case GLUT_KEY_RIGHT:
		_cam.camRight(CAM_MOVE);
		break;
	}

	glutPostRedisplay();
}

void World::draw()
{
	_shader.use();

	// setup lighting uniforms
	_light.render(_shader);

	// setup camera uniforms
	_cam.render(_shader);

	if (drawAxes)
		axes->draw(_shader);

	//game.draw(_shader);

	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i]->draw(_shader);
	}

	terrain.draw(_shader);

}

void World::initValues()
{
	// init light values
	_light.setColor(_directionalColor);
	_light.setAmbient(_ambientColor);
	_light.setPosition(vmath::vec3(0.5, 0.5, 0.5));
	_light.setShininess(2);
	_light.setStrength(6);
	_light.setConstantAttenuation(0.25);
	_light.setLinearAttenuation(0.25);
	_light.setQuadraticAttenuation(0.01);
	_light.setEyeDirection(vmath::vec3(0, 0, 1));
	_light.toggle();

	//----------------------------------------------------------
	// Data for Axes
	//----------------------------------------------------------
	vec4 axesPosition[NUM_AXES][2] = {
		{ vec4(-5.0, 0.0, 0.0, 1.0), vec4(5.0, 0.0, 0.0, 1.0) },
		{ vec4(0.0, -5.0, 0.0, 1.0), vec4(0.0, 5.0, 0.0, 1.0) },
		{ vec4(0.0, 0.0, -5.0, 1.0), vec4(0.0, 0.0, 5.0, 1.0) }
	};

	Color axesColor, terrainColor;
	axesColor.red = 0.8;
	axesColor.green = 0.8;
	axesColor.blue = 0.8;
	axesColor.alpha = 1.0;

	terrainColor.red = 1.0;
	terrainColor.blue = 0.3;
	terrainColor.green = 0.0;
	terrainColor.alpha = 1.0;

	axes->init(axesPosition);
	axes->setColor(axesColor);


	terrain.init("Models/terrain.obj");
	terrain.setColor(terrainColor);



}

void World::setupTextures()
{

	// Texture Files

	/*
	for (int i = 0; i < 3; i++)
	{
		_textures[i] = new Texture();
		_textures[i]->loadFromFile(_textureFilenames[i]);
	}

	_textures[0]->load();
	_textures[1]->load();
	_textures[2]->load();
	*/
}

void World::idleFunc()
{

}