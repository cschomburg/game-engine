#include <fstream>
#include "YamlLoader.h"

#include "Level.h"
#include "Primitives.h"
#include "Renderable.h"
#include "Vector2.h"

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

		Vector2 gravitation;
		node["gravitation"] >> gravitation;
		level->setGravitation(gravitation);

		const YAML::Node &nRenderables = node["props"];
		for (YAML::Iterator i = nRenderables.begin(); i != nRenderables.end(); ++i) {
			level->addRenderable(loadRenderable(*i));
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

Renderable * YamlLoader::loadRenderable(const YAML::Node &node) {
	int x, y, w, h;
	node["pos"][0] >> x;
	node["pos"][1] >> y;
	node["size"][0] >> w;
	node["size"][1] >> h;

	std::string texturePath;
	node["texture"] >> texturePath;
	
	Renderable * renderable = new Renderable();
	renderable->setPos(x, y);
	renderable->setSize(w, h);
	renderable->setTexture(texturePath);

	return renderable;
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

void operator >> (const YAML::Node &node, Vector2 &vector) {
	node[0] >> vector.x;
	node[1] >> vector.y;
}
