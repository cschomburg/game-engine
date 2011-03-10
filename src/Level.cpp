#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>

#include "Level.h"

Level::Level(int width, int height) {
	m_width = width;
	m_height = height;

	setBackground(0, 0, 0);
}

Level::~Level() {}

Level * Level::fromFile(const char * file) {
	int width, height;
	int r, g, b;

	try {
		std::ifstream fin(file);
		YAML::Parser parser(fin);
		YAML::Node level;
		parser.GetNextDocument(level);

		level["width"] >> width;
		level["height"] >> height;

		level["background"][0] >> r;
		level["background"][1] >> g;
		level["background"][2] >> b;
	} catch (YAML::Exception &e) {
		std::cout << "Could not load level '" << file << "'!\n" << e.what() << "\n";
		return 0;
	}
	printf("lol%d, %d, %d\n", r, g, b);

	Level * level = new Level(width, height);
	level->setBackground(r, g, b);
	return level;
}

void Level::setBackground(Uint8 r, Uint8 g, Uint8 b) {
	m_bgR = r;
	m_bgG = g;
	m_bgB = b;

	printf("%d, %d, %d\n", r, g, b);
}

void Level::onRender(SDL_Surface * display) {
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = display->w;
	rect.h = display->h;

	SDL_FillRect(display, &rect, SDL_MapRGB(display->format, m_bgR, m_bgG, m_bgB));
}
