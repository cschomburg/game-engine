#ifndef YAMLLOADER_H
#define YAMLLOADER_H

#include <yaml-cpp/yaml.h>

class Color;
class Level;
class Prop;

namespace YamlLoader {
	void openFile(YAML::Node &node, const char * file);

	Level * loadLevel(const char * file);
	Prop * loadProp(const YAML::Node &node);
}

void operator >> (const YAML::Node &node, Level * level);
void operator >> (const YAML::Node &node, Color &color);

#endif /* end of include guard: YAMLLOADER_H */
