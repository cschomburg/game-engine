#include "ResourceManager.h"
#include "Texture.h"

ResourceManager::ResourceManager() {}
ResourceManager::~ResourceManager() {}

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
