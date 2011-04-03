#include <fstream>
#include "YamlLoader.h"

#include "Level.h"
#include "Primitives.h"

namespace YamlLoader {

	void openFile(YAML::Node &node, const char * file) {
		std::ifstream fin(file);
		YAML::Parser parser(fin);
		parser.GetNextDocument(node);
	}

	Level * loadLevel(const char * file) {
		Level * level = new Level();

		try {
			YAML::Node node;
			openFile(node, file);
			node >> level;
		} catch (YAML::Exception &e) {
			printf("error: Could not load '%s': %s\n", file, e.what());
			if (level != 0) {
				delete level;
				level = 0;
			}
		}

		return level;
	}
}

void operator >> (const YAML::Node &node, Level * level) {
	level->setSize(node["width"], node["height"]);

	Color bgColorA;
	Color bgColorB;
	node["background"]["colorA"] >> bgColorA;
	node["background"]["colorB"] >> bgColorB;
	level->setBackground(bgColorA, bgColorB);
}

void operator >> (const YAML::Node &node, Color &color) {
	int r, g, b;
	node[0] >> r;
	node[1] >> g;
	node[2] >> b;
	color.r = float(r) / 255;
	color.g = float(g) / 255;
	color.b = float(b) / 255;
}
