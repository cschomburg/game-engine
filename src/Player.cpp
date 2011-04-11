#include "Player.h"

Player::Player() {
	setSize(Vector2(32, 32));
	setTexture("res/images/foo.png");
}

void Player::setMovement(float x, float y) {
	Vector2 accel = m_controlAcceleration * -1;
	m_controlAcceleration = Vector2(x, y) * 500;
	accel += m_controlAcceleration + acceleration();
	setAcceleration(accel);
}
