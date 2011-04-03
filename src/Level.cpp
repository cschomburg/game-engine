#include <iostream>
#include <fstream>
#include <SDL/SDL_opengl.h>

#include "Primitives.h"
#include "Level.h"

Level::Level() {
	m_width = 0;
	m_height = 0;

	setBackground(Color(1,1,1), Color(1,1,1));

	m_sun = Texture::fromFile("res/images/sun.png");
	m_tree = Texture::fromFile("res/images/tree.png");
	m_island = Texture::fromFile("res/images/island.png");
}

Level::~Level() {
	delete m_sun;
	delete m_island;
	delete m_tree;
}

void Level::setSize(int width, int height) {
	m_width = width;
	m_height = height;
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
		glVertex3f(m_width, 0, -0.9f);
		glColor3f(m_bgColorA.r, m_bgColorA.g, m_bgColorA.b);
		glVertex3f(m_width, m_height, -0.9f);
		glVertex3f(0, m_height, -0.9f);
	glEnd();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	m_sun->draw(512, 287);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_tree->draw(512, 287 + 58);
	m_island->draw(512, 287 - 60);
}
