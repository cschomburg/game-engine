#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>

#include "Texture.h"
#include "Rect.h"
#include "Vector2.h"

class GameObject;
typedef std::vector<GameObject *> GameObjectsVector;

class GameObject : public Rect {
public:
	GameObject(GameObject * parent = 0);
	virtual ~GameObject();

	GameObject * parent() const;
	const GameObjectsVector &children() const;
	void setParent(GameObject * parent);
	void addChild(GameObject * object);

	Vector2 worldPos();

	bool collision() const;
	void setCollision(bool collision);
	virtual bool collides(GameObject * object);

	void setTexture(const std::string &texturePath);
	virtual void onRender();

private:
	GameObject * m_parent;
	GameObjectsVector m_children;

	bool m_collision;

	Texture * m_texture;
};

#endif /* end of include guard: GAMEOBJECT_H */
