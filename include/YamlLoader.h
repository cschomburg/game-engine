#ifndef YAMLLOADER_H
#define YAMLLOADER_H

#include <yaml-cpp/yaml.h>

class Level;
class Color;

void operator >> (const YAML::Node &node, Level * level);
void operator >> (const YAML::Node &node, Color &color);

namespace YamlLoader {
	void openFile(YAML::Node &node, const char * file);

	Level * loadLevel(const char * file);
}

#endif /* end of include guard: YAMLLOADER_H */
