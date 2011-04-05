#include <iostream>
#include <fstream>
#include <SDL/SDL_opengl.h>

#include "Level.h"

Level::Level() {
	m_size.x = 0;
	m_size.y = 0;

	setBackground(Color(1,1,1), Color(1,1,1));
}

Level::~Level() {
	for (propVector::iterator i = m_props.begin(); i != m_props.end(); ++i) {
		delete *i;
	}
	m_props.clear();
}

void Level::setSize(int width, int height) {
	m_size.x = width;
	m_size.y = height;
}

void Level::setBackground(Color colorA, Color colorB) {
	m_bgColorA = colorA;
	m_bgColorB = colorB;
}

void Level::addProp(Prop * prop) {
	m_props.push_back(prop);
}

void Level::onInit() {
	glClearColor(0, 0, 0, 0);
}

void Level::onRender() {
	glBegin(GL_QUADS);
		glColor3f(m_bgColorB.r, m_bgColorB.g, m_bgColorB.b);
		glVertex3f(0, 0, -0.9f);
		glVertex3f(m_size.x, 0, -0.9f);
		glColor3f(m_bgColorA.r, m_bgColorA.g, m_bgColorA.b);
		glVertex3f(m_size.x, m_size.y, -0.9f);
		glVertex3f(0, m_size.y, -0.9f);
	glEnd();

	for (propVector::iterator i = m_props.begin(); i != m_props.end(); ++i) {
		(*i)->onRender();
	}
}
