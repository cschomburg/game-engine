#include <iostream>
#include <fstream>
#include <SDL/SDL_opengl.h>

#include "Level.h"

Level::Level() {
	m_size.x = 0;
	m_size.y = 0;

	setBackground(Color(1,1,1), Color(1,1,1));

	m_sun = new Prop(512, 287, 512, 512, "res/images/sun.png");
	m_tree = new Prop(512, 287 + 58, 100, 110, "res/images/tree.png");
	m_island = new Prop(512, 287 - 60, 200, 128, "res/images/island.png");
}

Level::~Level() {
	delete m_sun;
	delete m_tree;
	delete m_island;
}

void Level::setSize(int width, int height) {
	m_size.x = width;
	m_size.y = height;
}

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
		glVertex3f(m_size.x, 0, -0.9f);
		glColor3f(m_bgColorA.r, m_bgColorA.g, m_bgColorA.b);
		glVertex3f(m_size.x, m_size.y, -0.9f);
		glVertex3f(0, m_size.y, -0.9f);
	glEnd();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	m_sun->onRender();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_tree->onRender();
	m_island->onRender();
}
