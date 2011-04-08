#ifndef YAMLLOADER_H
#define YAMLLOADER_H

#include <yaml-cpp/yaml.h>

class Color;
class Level;
class Renderable;
class Vector2;

namespace YamlLoader {
	void openFile(YAML::Node &node, const char * file);

	Level * loadLevel(const char * file);
	Renderable * loadRenderable(const YAML::Node &node);
}

void operator >> (const YAML::Node &node, Level * level);
void operator >> (const YAML::Node &node, Color &color);
void operator >> (const YAML::Node &node, Vector2 &vector);

#endif /* end of include guard: YAMLLOADER_H */
