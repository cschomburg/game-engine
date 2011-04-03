#include <iostream>
#include <fstream>
#include <SDL/SDL_opengl.h>

#include "Primitives.h"
#include "Level.h"

Level::Level() {
	m_width = 0;
	m_height = 0;

	setBackground(Color(1,1,1), Color(1,1,1));

	m_texture = Texture::fromFile("res/images/island.png");
}

Level::~Level() {
	delete m_texture;
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
	glClearColor(m_bgColorA.r, m_bgColorA.g, m_bgColorA.b, 1.0f);
}

void Level::onRender() {
	glTranslatef(-m_width/2, m_height/2, 0);

	glBegin(GL_QUADS);
		glColor3f(m_bgColorB.r, m_bgColorB.g, m_bgColorB.b);
		glVertex3f(0, -m_height, -0.9f);
		glVertex3f(m_width, -m_height, -0.9f);
		glColor3f(m_bgColorA.r, m_bgColorA.g, m_bgColorA.b);
		glVertex3f(m_width, 0, -0.9f);
		glVertex3f(0, 0, -0.9f);
	glEnd();

	m_texture->draw(400, -300);
}
