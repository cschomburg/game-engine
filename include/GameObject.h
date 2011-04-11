#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>

#include "Texture.h"
#include "Vector2.h"

class GameObject;
typedef std::vector<GameObject *> GameObjectsVector;

class GameObject {
public:
	GameObject(GameObject * parent = 0);
	virtual ~GameObject();

	GameObject * parent() const;
	void setParent(GameObject * parent);
	void addChild(GameObject * object);

	const Vector2 &pos() const;
	Vector2 worldPos();
	void setPos(const Vector2 &pos);
	void addPos(const Vector2 &pos);

	const Vector2 &size() const;
	void setSize(const Vector2 &size);

	void setTexture(const std::string &texturePath);
	virtual void onRender();

private:
	GameObject * m_parent;
	GameObjectsVector m_children;

	Vector2 m_pos;
	Vector2 m_size;

	Texture * m_texture;
};

#endif /* end of include guard: GAMEOBJECT_H */
