#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <memory>
#include <string>

#include "Resource.h"

class Font;
class Texture;

class ResourceManager {
public:
	ResourceManager();
	virtual ~ResourceManager();

	std::shared_ptr<Font> font(const std::string &name, int height);
	std::shared_ptr<Texture> texture(const std::string &name);

private:
	std::map<std::string, std::weak_ptr<Font>> m_fonts;
	std::map<std::string, std::weak_ptr<Texture>> m_textures;
};

#endif /* end of include guard: RESOURCEMANAGER_H */
