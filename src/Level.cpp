#include <iostream>
#include <fstream>
#include <SDL/SDL_opengl.h>

#include "Level.h"

Level::Level() {
	m_width = 0;
	m_height = 0;

	setBackground(0, 0, 0);

	m_texture = Texture::fromFile("res/images/island.png");
}

Level::~Level() {
	delete m_texture;
}

void Level::setSize(int width, int height) {
	m_width = width;
	m_height = height;
}

void Level::setBackground(int r, int g, int b) {
	m_backgroundR = r;
	m_backgroundG = g;
	m_backgroundB = b;

	glClearColor(float(r) / 255, float(g) / 255, float(b) / 255, 1);
}

void Level::onRender() {
	m_texture->draw(0, 0);
}
