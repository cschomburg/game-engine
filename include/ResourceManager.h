#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>

#include "Resource.h"

class Texture;

class ResourceManager {
public:
	ResourceManager();

	Texture * getTexture(const std::string &name);

private:
	std::map<std::string, Resource *> m_resources;
};

#endif /* end of include guard: RESOURCEMANAGER_H */
