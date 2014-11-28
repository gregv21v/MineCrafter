#include "World.h"

World::World()
{

	axes = new Axes();
	drawAxes = false;
	_followMouse = true;
	_shadowMapppingEnabled = true;


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
	setupTextures();
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
	
}

void World::display()
{
	// clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// update the shadow map
	_shadowMap.startRenderFromLight();
		draw();
	_shadowMap.endRenderFromLight();

	// draw world
	_shader.use();
	_shadowMap.render(_shader);
	draw();

	

	// swap the buffers at the end of the display sequence
	glutSwapBuffers();
}




void World::keyPress(unsigned char key, int x, int y)
{
	Color black; 
	Block * block; 
	float distance = 0.1; 
	glm::vec3 eye = _cam.getEye();

	
	switch (key)
	{
	case 'p':
		block = new Block();
		block->init("Models/Block.obj");
		block->setTexture(_textures[0]);
		block->translate(eye);
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
	case 'm':
		_shadowMapppingEnabled = !_shadowMapppingEnabled;
		break;
	// movement
	case 'w':
	case 'W':
		_player.moveForward(distance);
		_cam.moveIn(distance);
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
	Block * block;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		_followMouse = true;

		/*
			block = new Block();
			block->setTexture(_textures[0]);
			block->init("Models/Block.obj");
			block->translate(_cam.getCenter());
			_blocks.push_back(block);
		*/
		
		//cout << "Block added" << endl;


		// create the face
		//_terrain.makeFace(_cam.getCenter());
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
		_cam.turnEyeX(direction[0] * 350.0);
		_cam.turnEyeY(direction[1] * 350.0);

		//glm::mat4 rotate1 = glm::rotate(glm::mat4(), direction[0] * 350, glm::vec3(1, 0, 0));
		//glm::mat4 rotate2 = glm::rotate(glm::mat4(), direction[1] * 350, glm::vec3(0, 1, 0));


		// update the flashlight

		_flashLight._position = _cam.getCenter();
		//_flashLight._position.z += 1;
		_flashLight._coneDirection = _cam.getDirection();
		//_flashLight._coneDirection.y += 1;
		//_flashLight._eyeDirection = _cam.getDirection();
		
	}


	_lastMousePosition = mousePos;


	glutPostRedisplay();

}

void World::mouseActiveMove(int x, int y)
{
	glm::vec2 mousePos(x, y);
	mousePos = _window->normalizeTo(mousePos);
	glm::vec2 direction = _lastMousePosition - mousePos; // the direction the mouse is moving

	_terrain.extrude(glm::vec3(0, mousePos.y, 0));
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
	//_shadowMapShader.use();
	
	glUniform1i(_shader.getUniformLocation("shadowMappingEnabled"), _shadowMapppingEnabled);
	// setup lighting uniforms
	_light.render(_shader);
	_flashLight.render(_shader);

	// setup camera uniforms
	_cam.render(_shader);

	if (drawAxes)
		axes->draw(_shader);

	//game.draw(_shader);

	for (int i = 0; i < _blocks.size(); i++)
	{
		_blocks[i]->render(_shader);
		_blocks[i]->draw(_shader);
	}

	_terrain.draw(_shader);

	


}

void World::initValues()
{
	// directional light
	_light._index = 0;
	_light._isLocal = false;
	_light._isSpot = false;
	_light._halfVector = glm::vec3(0.0, 0.0, 1.0);
	_light._ambient = glm::vec3(0.7, 0.7, 0.4);
	_light._color = glm::vec3(0.9, 0.9, 0.9);
	_light._position = glm::vec3(0, 0, 1.0);
	_light._strength = 2;
	_light._shininess = 2;

	// spot light
	_flashLight._index = 1;
	_flashLight._isLocal = true;
	_flashLight._coneDirection = glm::vec3(0.0, 0.0, -1.0);
	_flashLight._shininess = 1;
	_flashLight._strength = 1.0;
	_flashLight._color = glm::vec3(1.0, 1.0, 1.0);
	_flashLight._ambient = glm::vec3(1.0, 1.0, 1.0);
	_flashLight._constantAttenuation = 0.25;
	_flashLight._linearAttenuation = 0.25;
	_flashLight._quadraticAttenuation = 0.11;
	_flashLight._position = _cam.getEye();
	_flashLight._halfVector = glm::vec3(0.0, 0.0, 1.0);
	_flashLight._spotExponent = 2;
	_flashLight._spotCosCutoff = 0.1;

	_flashLight._eyeDirection = glm::vec3(0.0, 0.0, 1.0); // this applies to all lights
														 // so it should be moved from the 
														 // light class


	_light._isEnabled = _flashLight._isEnabled = false;
	_shadowMapppingEnabled = false;

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
	terrainColor.blue = 1.0;
	terrainColor.green = 1.0;
	terrainColor.alpha = 1.0;

	axes->init(axesPosition);
	axes->setColor(axesColor);


	_terrain.init("Models/terrain.obj");
	_terrain.setColor(terrainColor);
	_terrain.translate(glm::vec3(0, -1.0, 0));
	_terrain.setTexture(_textures[2]);

	//_test.init("Models/Block.obj");
	//_test.setColor(terrainColor);
	//_test.translate(0, 2.0, 0);

	_shadowMap.init(&_cam, glm::vec3(0, 0.5, 0.5));

	_shadowMap.startRenderFromLight();
		draw();
	_shadowMap.endRenderFromLight();


}

void World::setupTextures()
{

	// Texture Files
	_textureFilenames.push_back("Textures/dirtBlock.png");
	_textureFilenames.push_back("Textures/stoneBlock.png");
	_textureFilenames.push_back("Textures/grassTerrain.png");
	
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