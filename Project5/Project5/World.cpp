#include "World.h"

World::World()
{

	axes = new Axes();
	drawAxes = false;


	run_game = false;
}

World::~World()
{
	for (int i = 0; i < _textures.size(); i++)
	{
		delete _textures[i];
	}

	for (int i = 0; i < _blocks.size(); i++)
	{
		delete _blocks[i];
	}
}

void World::init(Window * window)
{

	_window = window;
	initValues();
	_cam.init();
	//_shader.init("Shaders/PointLight.vert", "Shaders/PointLight.frag");
	_shader.init("Shaders/MultipleLights.vert", "Shaders/MultipleLights.frag");
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

	// update the shadow map
	_shadowMap.init(_cam.getFrustum());
	_shadowMap.startRenderFromLight();
		draw();
	_shadowMap.endRenderFromLight();

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
	glm::vec3 eye = _player.getPosition();
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
		block->translate(eye.x, eye.y, eye.z);
		_blocks.push_back(block);
		break;
	case 'n':

		break;
	case 'g':
		run_game = !run_game;
		break;
	case 'l':
		_light.toggle();
		//cout << "Is state: " << _light._isEnabled << endl;
		break;
	case 'f':
		_flashLight.toggle();
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

	case 27: // escape key
		_followMouse = false;
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
	glm::vec2 mousePos = glm::vec2(x, y);
	mousePos = _window->normalizeTo(mousePos);
	glm::vec4 projection = _cam.getViewFrustum() * glm::vec4(mousePos.x - 1, mousePos.y, 0.0, 1.0);
	
	blockColor.red = 0;
	blockColor.green = 255;
	blockColor.blue = 0;
	blockColor.alpha = 1;

	


	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		_followMouse = true;

		block = new Block();
		block->setTexture(_textures[0]);
		block->init("Models/Block.obj");
		block->setColor(blockColor);
		block->translate(projection.x, projection.y, projection.z);
		_blocks.push_back(block);
		//cout << "Block added" << endl;
	}

	glutPostRedisplay();

}

void World::mousePassiveMove(int x, int y)
{
	glm::vec2 mousePos(x, y);
	mousePos = _window->normalizeTo(mousePos);
	glm::vec2 direction = _lastMousePosition - mousePos; // the direction the mouse is moving
	
	if (_followMouse)
	{
		_cam.rotate((_lastMousePosition[0] - mousePos[0]) * 350.0, 0.0, 1.0, 0.0);
		_cam.rotate((_lastMousePosition[1] - mousePos[1]) * 350.0, 1.0, 0.0, 0.0);

		// update the flashlight
		_flashLight._position = _player.getPosition();
		_flashLight._coneDirection = _cam.getDirection();
		_flashLight._eyeDirection = _cam.getDirection();
		
	}
		

	_lastMousePosition = mousePos;

	glutPostRedisplay();
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
	//_shadowMapShader.use();
	_shadowMap.render(_shader);

	
	// setup lighting uniforms
	_light.render(_shader);
	_flashLight.render(_shader);

	//_test.draw(_shader);

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
	_light._index = 0;
	_light._isLocal = false;
	_light._ambient = glm::vec3(1.0, 1.0, 1.0);
	_light._color = glm::vec3(1.0, 1.0, 1.0);
	_light._strength = 1;
	_light._shininess = 1;


	_flashLight._index = 1;
	_flashLight._isLocal = true;
	_flashLight._coneDirection = glm::vec3(0.0, 0.0, -1.0);
	_flashLight._shininess = 1;
	_flashLight._strength = 0.5;
	_flashLight._color = glm::vec3(1.0, 1.0, 1.0);
	_flashLight._ambient = glm::vec3(1.0, 1.0, 1.0);
	_flashLight._constantAttenuation = 0.25;
	_flashLight._linearAttenuation = 0.25;
	_flashLight._quadraticAttenuation = 0.11;
	_flashLight._position = _player.getPosition() + glm::vec3(0.0, 0.0, -1.0);
	_flashLight._halfVector = glm::vec3(0.0, 0.0, 1.0);
	_flashLight._spotExponent = 2;
	_flashLight._spotCosCutoff = 1.5;

	_flashLight._eyeDirection = glm::vec3(0.0, 1.0, 1.0); // this applies to all lights
														 // so it should be moved from the 
														 // light class

	


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

	//_test.init("Models/Block.obj");
	//_test.setColor(terrainColor);
	//_test.translate(0, 2.0, 0);

	_shadowMap.init(_cam.getFrustum());
	_shadowMap.startRenderFromLight();
		draw();
	_shadowMap.endRenderFromLight();


}

void World::setupTextures()
{

	// Texture Files
	_textureFilenames.push_back("Textures/dirtBlock.png");
	_textureFilenames.push_back("Textures/stoneBlock.png");

	
	for (int i = 0; i < _textureFilenames.size(); i++)
	{

		_textures.push_back(new Texture());
		_textures.back()->loadFromFile(_textureFilenames[i]);
		_textures.back()->load();
	}

	
}

void World::idleFunc()
{

}