#include "Player.h"


Player::Player()
{
	transform = vmath::mat4::identity();
	_position = vmath::vec4(0, 6, 0, 1);
}

Player::~Player()
{
}







/*void Player::draw(Shader shader)
{

}
*/

// Transformation Stuff
void Player::scale(float scaleFactor)
{
	// Translate to _position
	vmath::mat4 translate1 = vmath::translate(-_position[0], -_position[1], -_position[2]);
	vmath::mat4 scale = vmath::scale(scaleFactor);
	vmath::mat4 translate2 = vmath::translate(_position[0], _position[1], _position[2]);

	scale = (translate2 * scale * translate1);
	transform = scale * transform;
	updatePosition();

}

void Player::translate(float x, float y, float z)
{
	vmath::mat4 translate = vmath::translate(x, y, z);
	transform = translate * transform;

	updatePosition();

}

void Player::rotate(float angle, vmath::vec3 inAxis)
{
	// Translate to _position
	vmath::mat4 translate1 = vmath::translate(-_position[0], -_position[1], -_position[2]);
	vmath::mat4 rotate = vmath::rotate(angle, inAxis);
	vmath::mat4 translate2 = vmath::translate(_position[0], _position[1], _position[2]);

	rotate = (translate2 * rotate * translate1);
	transform = rotate * transform;
	updatePosition();
}

void Player::updatePosition()
{
	_position[0] = transform[3][0];
	_position[1] = transform[3][1];
	_position[2] = transform[3][2];
}




void Player::moveLeft(float distance)
{
	translate(-distance, 0, 0);
}
void Player::moveRight(float distance)
{
	translate(distance, 0, 0);
}
void Player::moveForward(float distance)
{
	translate(0, 0, distance);
}
void Player::moveBackwards(float distance)
{
	translate(0, 0, -distance);
}


vmath::vec4 Player::getPosition()
{
	return _position;
}