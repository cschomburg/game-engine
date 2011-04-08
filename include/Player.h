#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity {
public:
	Player();

	void setMovement(float x = 0, float y = 0);

private:
	Vector2 m_controlAcceleration;
};

#endif /* end of include guard: PLAYER_H */
