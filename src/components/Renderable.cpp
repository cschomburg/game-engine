#include <string>
#include <SDL/SDL_opengl.h>

#include "Application.h"
#include "components/Positionable.h"
#include "components/Renderable.h"
#include "components/Shape.h"
#include "Texture.h"

const ComponentType Renderable::componentType = "Renderable";

Renderable::Renderable(Object *object)
	: Component(componentType, object) {
	m_texture = 0;
	}

Renderable::~Renderable() {
	if (m_texture)
		m_texture->free();
}

void Renderable::setGradient(const Color &colorA, const Color &colorB) {
	m_colorA = colorA;
	m_colorB = colorB;
}

void Renderable::setTexture(const std::string &texturePath) {
	m_texture = Application::instance()->manager()->getTexture(texturePath);
	m_texture->init();
}

void Renderable::onRender() {
	Positionable *positionable = object()->component<Positionable>();
	Shape *shape = object()->component<Shape>();
	if (!positionable || !shape)
		return;

	Vector2 pos = positionable->pos();
	Vector2 size = shape->size();

	if (m_colorA.a > 0 || m_colorB.a > 0) {
		glBegin(GL_QUADS);
			glColor3f(m_colorB.r, m_colorB.g, m_colorB.b);
			glVertex3f(pos.x, pos.y, -0.9f);
			glVertex3f(pos.x + size.x, pos.y, -0.9f);
			glColor3f(m_colorA.r, m_colorA.g, m_colorA.b);
			glVertex3f(pos.x + size.x, pos.y + size.y, -0.9f);
			glVertex3f(pos.x, pos.y + size.y, -0.9f);
		glEnd();

		glColor3f(1, 1, 1); // Reset
	}
	if (m_texture) {
		m_texture->draw(pos.x, pos.y, size.x, size.y);
	}
}
