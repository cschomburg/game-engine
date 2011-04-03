#ifndef YAMLLOADER_H
#define YAMLLOADER_H

#include <yaml-cpp/yaml.h>

class Level;

void operator >> (const YAML::Node &node, Level * level);

namespace YamlLoader {
	void openFile(YAML::Node &node, const char * file);

	Level * loadLevel(const char * file);
}

#endif /* end of include guard: YAMLLOADER_H */
