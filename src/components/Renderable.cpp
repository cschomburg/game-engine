#include <string>
#include <SDL/SDL_opengl.h>

#include "Application.h"
#include "components/Movable.h"
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

	// Debug shape 
	glColor3f(0, 1, 0);
	Polygon poly = shape->shape();
	poly.translate(positionable->pos());
	glBegin(GL_LINES);
	for (int i = 0; i < poly.points.size(); i++) {
		Vector2 axis = poly.points[i] - poly.points[(i+1) % poly.points.size()];

		Vector2 start = poly.points[(i+1) % poly.points.size()];
		Vector2 end = start + axis;

		glVertex3f(start.x, start.y, 0.1f);
		glVertex3f(end.x, end.y, 0.1f);
	}
	glEnd();

	// Debug velocity and acceleration
	Movable *movable = object()->component<Movable>();
	if (movable) {
		Vector2 pos = positionable->pos();
		Vector2 vel = pos + movable->velocity()/5;
		Vector2 acc = pos + movable->acceleration()/100;
		glBegin(GL_LINES);
		glColor3f(0, 0, 1);
		glVertex3f(pos.x, pos.y, 0.1f);
		glVertex3f(vel.x, vel.y, 0.1f);
		glColor3f(1, 1, 0);
		glVertex3f(pos.x, pos.y, 0.1f);
		glVertex3f(acc.x, acc.y, 0.1f);
		glEnd();
	}

	// Collision vector
	Vector2 collVec;
	if (Application::instance()->engine()->checkCollision(object(), &collVec)) {
		Vector2 pos = positionable->pos();
		collVec += pos;
		glBegin(GL_LINES);
		glColor3f(0, 1, 1);
		glVertex3f(pos.x, pos.y, 0.1f);
		glVertex3f(collVec.x, collVec.y, 0.1f);
		glEnd();
	}

	glColor3f(1, 1, 1); // Reset
}
