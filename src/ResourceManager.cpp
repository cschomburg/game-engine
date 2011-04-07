#include "ResourceManager.h"
#include "Texture.h"

ResourceManager::ResourceManager() {}

Texture * ResourceManager::getTexture(const std::string &name) {
	Resource * res = m_resources[name];
	if (res)
		return dynamic_cast<Texture *>(res);

	Texture * tex = new Texture(name);
	m_resources[name] = dynamic_cast<Resource *>(tex);
	return tex;
}
