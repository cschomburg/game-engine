#include <fstream>
#include "YamlLoader.h"

#include "Level.h"
#include "Color.h"
#include "GameObject.h"
#include "Vector2.h"

using namespace YamlLoader;

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
	} catch (YAML::Exception &e) {
		printf("error: Could not load '%s': %s\n", file, e.what());
		if (level != 0) {
			delete level;
			level = 0;
		}
	}

	return level;
}

GameObject * YamlLoader::loadGameObject(const YAML::Node &node) {
	int x, y, w, h;
	std::string texturePath;
	node["texture"] >> texturePath;
	
	GameObject * object = new GameObject();
	object->setPos(loadVector2(node["pos"]));
	object->setSize(loadVector2(node["size"]));
	object->setTexture(texturePath);

	if (const YAML::Node *nCollision = node.FindValue("collision")) {
		object->setCollision(nCollision);
	}

	if (const YAML::Node *nObjects = node.FindValue("children")) {
		for (YAML::Iterator i = nObjects->begin(); i != nObjects->end(); ++i) {
			GameObject * child = loadGameObject(*i);
			child->setParent(object);
			object->addChild(child);
		}
	}

	return object;
}

void operator >> (const YAML::Node &node, Level * level) {
	level->setSize(loadVector2(node["size"]));

	Color bgColorA;
	Color bgColorB;
	node["background"]["colorA"] >> bgColorA;
	node["background"]["colorB"] >> bgColorB;
	level->setBackground(bgColorA, bgColorB);

	level->setGravitation(loadVector2(node["gravitation"]));
	level->setSpawn(loadVector2(node["spawn"]));

	const YAML::Node &nObjects = node["objects"];
	for (YAML::Iterator i = nObjects.begin(); i != nObjects.end(); ++i) {
		level->addChild(loadGameObject(*i));
	}
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

const Vector2 YamlLoader::loadVector2(const YAML::Node &node) {
	Vector2 vec;
	node >> vec;
	return vec;
}
