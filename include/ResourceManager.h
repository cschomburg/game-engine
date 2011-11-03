#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <memory>
#include <string>

#include "Resource.h"

class Texture;

class ResourceManager {
public:
	ResourceManager();
	virtual ~ResourceManager();

	std::shared_ptr<Texture> texture(const std::string &name);

private:
	std::map<std::string, std::weak_ptr<Texture>> m_textures;
};

#endif /* end of include guard: RESOURCEMANAGER_H */
