#include "Prop.h"

Prop::Prop(float x, float y, float w, float h, const char * texturePath) {
	setPos(x, y);
	m_size.x = w;
	m_size.y = h;

	m_texture = Texture::fromFile(texturePath);
}

void Prop::onRender() {
	m_texture->draw(pos().x, pos().y, m_size.x, m_size.y);
}
