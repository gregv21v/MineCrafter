#include "Player.h"


Player::Player()
{
	_transform = glm::mat4();
	_position = glm::vec3(0, 6, 0);
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
	glm::mat4 translate1 = glm::translate(glm::mat4(), -_position);
	glm::mat4 scale = glm::scale(glm::mat4(), glm::vec3(scaleFactor));
	glm ::mat4 translate2 = glm::translate(glm::mat4(), _position);

	scale = (translate2 * scale * translate1);
	_transform = scale * _transform;
	updatePosition();

}

void Player::translate(float x, float y, float z)
{
	glm::mat4 translate = glm::translate(glm::mat4(), glm::vec3(x, y, z));
	_transform = translate * _transform;

	updatePosition();

}

void Player::rotate(float angle, glm::vec3 inAxis)
{
	// Translate to _position
	glm::mat4 translate1 = glm::translate(glm::mat4(), -_position);
	glm::mat4 rotate = glm::rotate(glm::mat4(), angle, inAxis);
	glm::mat4 translate2 = glm::translate(glm::mat4(), _position);;

	rotate = (translate2 * rotate * translate1);
	_transform = rotate * _transform;
	updatePosition();
}

void Player::updatePosition()
{
	_position = glm::vec3(_transform[3]);
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


glm::vec3 Player::getPosition()
{
	return _position;
}