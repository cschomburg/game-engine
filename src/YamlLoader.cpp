#include <fstream>
#include "YamlLoader.h"

#include "Level.h"

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
	level->setBackground(node["background"][0],
			             node["background"][1],
						 node["background"][2]);
}
