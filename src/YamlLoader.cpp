#include <fstream>
#include "YamlLoader.h"

#include "Level.h"
#include "Primitives.h"
#include "Prop.h"

void YamlLoader::openFile(YAML::Node &node, const char * file) {
	std::ifstream fin(file);
	YAML::Parser parser(fin);
	parser.GetNextDocument(node);
}

Level * YamlLoader::loadLevel(const char * file) {
	Level * level = new Level();

	try {
		YAML::Node node;
		openFile(node, file);
		node >> level;

		const YAML::Node &nProps = node["props"];
		for (YAML::Iterator i = nProps.begin(); i != nProps.end(); ++i) {
			level->addProp(loadProp(*i));
		}
			
	} catch (YAML::Exception &e) {
		printf("error: Could not load '%s': %s\n", file, e.what());
		if (level != 0) {
			delete level;
			level = 0;
		}
	}

	return level;
}

Prop * YamlLoader::loadProp(const YAML::Node &node) {
	int x, y, w, h;
	node["pos"][0] >> x;
	node["pos"][1] >> y;
	node["size"][0] >> w;
	node["size"][1] >> h;

	std::string texturePath;
	node["texture"] >> texturePath;
	return new Prop(x, y, w, h, texturePath.c_str());
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
