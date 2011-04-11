#ifndef LEVEL_H
#define LEVEL_H

#include "Color.h"
#include "GameObject.h"
#include "Vector2.h"

class Level : public GameObject {
public:
	Level();
	virtual ~Level();

	void setBackground(Color colorA, Color colorB);

	void onInit();
	void onRender();

	void setSpawn(const Vector2 &spawn);
	const Vector2 &spawn() const;
	void setGravitation(const Vector2 &gravitation);
	const Vector2 &gravitation() const;

	bool collides(GameObject * object);

private:
	Color m_bgColorA;
	Color m_bgColorB;

	Vector2 m_spawn;
	Vector2 m_gravitation;
};

#endif /* end of include guard: LEVEL_H */
