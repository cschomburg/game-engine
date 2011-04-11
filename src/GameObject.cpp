#include "Application.h"
#include "GameObject.h"

GameObject::GameObject(GameObject * parent) {
	m_parent = parent;
	m_texture = 0;
}

GameObject::~GameObject() {
	if (m_texture) {
		m_texture->free();
		m_texture = 0;
	}

	for (GameObjectsVector::iterator i = m_children.begin(); i != m_children.end(); ++i) {
		delete *i;
	}
	m_children.clear();
}

GameObject * GameObject::parent() const {
	return m_parent;
}

void GameObject::setParent(GameObject * parent) {
	m_parent = parent;
}

void GameObject::addChild(GameObject * object) {
	m_children.push_back(object);
}

Vector2 GameObject::worldPos() {
	if (m_parent)
		return m_parent->worldPos() + pos();
	else
		return pos();
}

void GameObject::setTexture(const std::string &texturePath) {
	if (m_texture) {
		m_texture->free();
	}
	m_texture = Application::instance()->manager()->getTexture(texturePath);
	m_texture->init();
}

void GameObject::onRender() {
	if (m_texture) {
		Vector2 pos = worldPos();
		m_texture->draw(pos.x, pos.y, size().x, size().y);
	}

	for (GameObjectsVector::iterator i = m_children.begin(); i != m_children.end(); ++i) {
		(*i)->onRender();
	}
}
