#include "Application.h"
#include "Renderable.h"

Renderable::Renderable() {
	m_texture = 0;
}

Renderable::~Renderable() {
	if (m_texture) {
		m_texture->free();
		m_texture = 0;
	}
}

void Renderable::setTexture(const std::string &texturePath) {
	if (m_texture) {
		m_texture->free();
	}
	m_texture = Application::instance()->manager()->getTexture(texturePath);
	m_texture->init();
}

void Renderable::onRender() {
	if (!m_texture)
		return;

	m_texture->draw(pos().x, pos().y, size().x, size().y);
}
