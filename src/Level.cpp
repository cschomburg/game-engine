#include <iostream>
#include <fstream>
#include <SDL/SDL_opengl.h>

#include "Level.h"

Level::Level() {
	setBackground(Color(1,1,1), Color(1,1,1));
}

Level::~Level() {}

void Level::setBackground(Color colorA, Color colorB) {
	m_bgColorA = colorA;
	m_bgColorB = colorB;
}

void Level::onInit() {
	glClearColor(0, 0, 0, 0);
}

void Level::onRender() {
	glBegin(GL_QUADS);
		glColor3f(m_bgColorB.r, m_bgColorB.g, m_bgColorB.b);
		glVertex3f(0, 0, -0.9f);
		glVertex3f(size().x, 0, -0.9f);
		glColor3f(m_bgColorA.r, m_bgColorA.g, m_bgColorA.b);
		glVertex3f(size().x, size().y, -0.9f);
		glVertex3f(0, size().y, -0.9f);
	glEnd();

	glColor3f(1, 1, 1);
	GameObject::onRender();
}

void Level::setSpawn(const Vector2 &spawn) {
	m_spawn = spawn;
}

const Vector2 &Level::spawn() const {
	return m_spawn;
}

void Level::setGravitation(const Vector2 &gravitation) {
	m_gravitation = gravitation;
}

const Vector2 &Level::gravitation() const {
	return m_gravitation;
}
