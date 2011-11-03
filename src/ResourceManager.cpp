#include <sstream>

#include "ResourceManager.h"
#include "Font.h"
#include "Texture.h"

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {}

std::shared_ptr<Font> ResourceManager::font(const std::string &name, int height) {
	std::stringstream resName(name);
	resName << "-" << height;
	// Existing resource
	auto it = m_fonts.find(resName.str());
	if (it != m_fonts.end() && !it->second.expired())
		return it->second.lock();

	// New resource
	std::shared_ptr<Font> font(new Font(name, height));
	m_fonts[resName.str()] = font;
	return font;
}

std::shared_ptr<Texture> ResourceManager::texture(const std::string &name) {
	// Existing resource
	auto it = m_textures.find(name);
	if (it != m_textures.end() && !it->second.expired())
		return it->second.lock();

	// New resource
	std::shared_ptr<Texture> tex(new Texture(name));
	m_textures[name] = tex;
	return tex;
}
