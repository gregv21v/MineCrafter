#include "Player.h"


Player::Player()
{
	transform = mat4::identity();
	center = vmath::vec4(0, 0, 0, 1);
}

Player::~Player()
{
}







void Player::draw(Shader shader)
{

}


// Transformation Stuff
void Player::scale(float scaleFactor)
{
	// Translate to center
	vmath::mat4 translate1 = vmath::translate(-center[0], -center[1], -center[2]);
	vmath::mat4 scale = vmath::scale(scaleFactor);
	vmath::mat4 translate2 = vmath::translate(center[0], center[1], center[2]);

	scale = (translate2 * scale * translate1);
	transform = scale * transform;
	updateCenter();

}

void Player::translate(float x, float y, float z)
{
	vmath::mat4 translate = vmath::translate(x, y, z);
	transform = translate * transform;

	updateCenter();

}

void Player::rotate(float angle, vmath::vec3 inAxis)
{
	// Translate to center
	vmath::mat4 translate1 = vmath::translate(-center[0], -center[1], -center[2]);
	vmath::mat4 rotate = vmath::rotate(angle, inAxis);
	vmath::mat4 translate2 = vmath::translate(center[0], center[1], center[2]);

	rotate = (translate2 * rotate * translate1);
	transform = rotate * transform;
	updateCenter();
}

void Player::updateCenter()
{
	center[0] = transform[3][0];
	center[1] = transform[3][1];
	center[2] = transform[3][2];
}
