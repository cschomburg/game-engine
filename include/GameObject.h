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
	void setParent(GameObject * parent);
	void addChild(GameObject * object);

	Vector2 worldPos();

	void setTexture(const std::string &texturePath);
	virtual void onRender();

private:
	GameObject * m_parent;
	GameObjectsVector m_children;

	Texture * m_texture;
};

#endif /* end of include guard: GAMEOBJECT_H */
