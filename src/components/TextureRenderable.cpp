#include "GameEngine.h"
#include "ResourceManager.h"
#include "Texture.h"

#include "components/TextureRenderable.h"

TextureRenderable::TextureRenderable()
	: Renderable("TextureRenderable") {
	m_texture = 0;
}

TextureRenderable::~TextureRenderable() {}

Texture::Ptr TextureRenderable::texture() const {
	return m_texture;
}

void TextureRenderable::setTexture(const std::string &texturePath) {
	m_texture = GameEngine::instance()->manager()->texture(texturePath);
}

void TextureRenderable::render() {
	if (!m_texture)
		return;

	Renderable::render();
	m_texture->draw(boundingRect());
}
