#include <string>
#include <vector>
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
	m_color = Color(1, 1, 1, 1);
	m_texture = 0;
}

Renderable::~Renderable() {
	if (m_texture)
		m_texture->free();
}

void Renderable::setColor(const Color &color) {
	m_color = color;
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

	glPushMatrix();
	glTranslatef(positionable->pos().x, positionable->pos().y, 0);
	Rect rect = shape->boundingBox();

	glColor4f(m_color.r, m_color.g, m_color.b, m_color.a);
	if (m_texture) {
		m_texture->draw(rect.x, rect.y, rect.w, rect.h);
	} else if (m_colorA.a > 0 || m_colorB.a > 0) {
		glBegin(GL_QUADS);
			glColor4f(m_colorB.r, m_colorB.g, m_colorB.b, m_colorB.a);
			glVertex3f(rect.x, rect.y, -0.9f);
			glVertex3f(rect.x + rect.w, rect.y, -0.9f);
			glColor4f(m_colorA.r, m_colorA.g, m_colorA.b, m_colorA.a);
			glVertex3f(rect.x + rect.w, rect.y + rect.h, -0.9f);
			glVertex3f(rect.x, rect.y + rect.h, -0.9f);
		glEnd();
	} else {
		std::vector<Vector2> points = shape->shape().points;
		glBegin(GL_POLYGON);
		for (std::vector<Vector2>::const_iterator i = points.begin(); i != points.end(); ++i) {
			glVertex3f(i->x, i->y, 0.0f);
		}
		glEnd();
	}

#ifdef DEBUG_RENDERABLE
	// Debug shape 
	glColor3f(0, 1, 0);
	Convex convex = shape->shape();
	glBegin(GL_LINES);
	for (int i = 0; i < convex.points.size(); i++) {
		Vector2 axis = convex.points[i] - convex.points[(i+1) % convex.points.size()];

		Vector2 start = convex.points[(i+1) % convex.points.size()];
		Vector2 end = start + axis;

		glVertex3f(start.x, start.y, 0.1f);
		glVertex3f(end.x, end.y, 0.1f);
	}
	glEnd();

	// Debug velocity and acceleration
	Movable *movable = object()->component<Movable>();
	if (movable) {
		Vector2 vel = movable->velocity()/5;
		Vector2 acc = movable->acceleration()/100;
		glBegin(GL_LINES);
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0.1f);
		glVertex3f(vel.x, vel.y, 0.1f);
		glColor3f(1, 1, 0);
		glVertex3f(0, 0, 0.1f);
		glVertex3f(acc.x, acc.y, 0.1f);
		glEnd();
	}

#endif /* end of DEBUG_RENDERABLE */

	glPopMatrix();
}
