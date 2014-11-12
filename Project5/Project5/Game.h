#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/freeglut.h>
#include <iostream>
#include <time.h>
#include <queue>

#include "vmath.h"
#include "Player.h"

#define FRAME_RATE .002
#define ANIMATE_MAX 100


using namespace std;

class Game
{

public:

	Game();
	~Game();

	void init();
	void draw(Shader);



private:

	Player player1;

};

