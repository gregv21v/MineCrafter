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

void World::init(Window * window)
{

	_window = window;
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
	Block * block; 
	float distance = 0.1; 
	vmath::vec4 eye = _player.getPosition();
	black.red = 0;
	black.green = 255;
	black.blue = 0;
	black.alpha = 1;
	
	switch (key)
	{
	case 'p':
		block = new Block();
		block->init("Models/Block.obj");
		block->setColor(black);
		block->translate(eye[0], eye[1], eye[2]);
		_blocks.push_back(block);
		break;
	case 'n':

		break;
	case 'g':
		run_game = !run_game;
		break;
	case 'l':
		_light.toggle();
		//cout << "Is state: " << _light.isOn() << endl;
		break;
	case 'i':
		//_cam.camIn(CAM_MOVE);
		break;
	case 'o':
		//_cam.camOut(CAM_MOVE);
		break;
	case 'q':
		drawAxes = !drawAxes;
		break;
	// movement
	case 'w':
	case 'W':
		_player.moveForward(distance);
		_cam.moveIn(distance);
		cout << "( " << _player.getPosition()[0] << ", " << _player.getPosition()[2]  << ") " << endl;
		break;
	case 's':
	case 'S':
		_player.moveBackwards(distance);
		_cam.moveOut(distance);
		break;
	case 'a':
	case 'A':
		_player.moveLeft(distance);
		_cam.moveLeft(distance);
		break;
	case 'd':
	case 'D':
		_player.moveRight(distance);
		_cam.moveRight(distance);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void World::mousePressed(int button, int state, int x, int y)
{

	Color blockColor;
	Block * block;
	float distance = 0.1;
	
	glm::vec2 mousePos = glm::vec2(x, y);
	mousePos = _window->normalizeTo(mousePos);
	glm::vec3 projection = glm::vec3(mousePos.x, 0.0, mousePos.y);
	blockColor.red = 0;
	blockColor.green = 255;
	blockColor.blue = 0;
	blockColor.alpha = 1;


	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		block = new Block();
		block->init("Models/Block.obj");
		block->setColor(blockColor);
		block->translate(projection.x, projection.y, projection.z/200);
		_blocks.push_back(block);
		cout << "Block added" << endl;
	}

}

void World::mousePassiveMove(int x, int y)
{
	vec2 direction = _lastMousePosition - vec2(x, y); // the direction the mouse is moving
	_lastMousePosition = vec2(x, y);
	
	
	
}



void World::arrowInput(int key, int x, int y)
{
	float distance = 0.1;
	switch (key)
	{
	case GLUT_KEY_UP:
		_cam.panUp(distance);
		break;
	case GLUT_KEY_DOWN:
		_cam.panDown(distance);
		break;
	case GLUT_KEY_LEFT:
		_cam.panLeft(distance);

		break;
	case GLUT_KEY_RIGHT:
		_cam.panRight(distance);
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

	for (int i = 0; i < _blocks.size(); i++)
	{
		_blocks[i]->draw(_shader);
	}

	_terrain.draw(_shader);


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

	_cam.init();

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


	_terrain.init("Models/terrain.obj");
	_terrain.setColor(terrainColor);
	_terrain.translate(0, -1.0, 0);



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