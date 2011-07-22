#include <string>
#include <SDL/SDL_opengl.h>

#include "Application.h"
#include "components/Positionable.h"
#include "components/Renderable.h"
#include "components/Shape.h"
#include "Rect.h"
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

	Rect rect = shape->boundingBox();
	rect.translate(positionable->pos());

	if (m_colorA.a > 0 || m_colorB.a > 0) {
		glBegin(GL_QUADS);
			glColor3f(m_colorB.r, m_colorB.g, m_colorB.b);
			glVertex3f(rect.x, rect.y, -0.9f);
			glVertex3f(rect.x + rect.w, rect.y, -0.9f);
			glColor3f(m_colorA.r, m_colorA.g, m_colorA.b);
			glVertex3f(rect.x + rect.w, rect.y + rect.h, -0.9f);
			glVertex3f(rect.x, rect.y + rect.h, -0.9f);
		glEnd();

		glColor3f(1, 1, 1); // Reset
	}
	if (m_texture) {
		m_texture->draw(rect.x, rect.y, rect.w, rect.h);
	}
}
