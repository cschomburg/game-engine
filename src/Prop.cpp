#include "Application.h"
#include "Prop.h"

Prop::Prop(float x, float y, float w, float h, const std::string &texturePath) {
	setPos(x, y);
	m_size.x = w;
	m_size.y = h;
	m_texture = Application::instance()->manager()->getTexture(texturePath);
	m_texture->init();
}

void Prop::onRender() {
	m_texture->draw(pos().x, pos().y, m_size.x, m_size.y);
}
