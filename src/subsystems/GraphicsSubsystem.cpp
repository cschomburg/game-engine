#include <iostream>
#include <iterator>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "Application.h"
#include "Object.h"
#include "components/Movable.h"
#include "components/Positionable.h"
#include "components/Renderable.h"
#include "components/Shape.h"
#include "Rect.h"
#include "Texture.h"
#include "subsystems/GraphicsSubsystem.h"

GraphicsSubsystem::GraphicsSubsystem(GameEngine *engine)
	: Subsystem(engine) {}

GraphicsSubsystem::~GraphicsSubsystem() {}

bool GraphicsSubsystem::init() {
	Application *app = Application::instance();
	int width = app->displayWidth();
	int height = app->displayHeight();

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-float(width) / 2, float(width)/2, -float(height)/2, float(height)/2, -1.1f, 1.1f);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	//glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_TRUE);
}

void GraphicsSubsystem::update() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Vector2 pos;
	if (m_camera) {
		pos = m_camera->component<Positionable>()->pos();
	}
	glTranslatef(-pos.x, -pos.y, 0.0f);
	// TODO: Camera zoom

	for (auto &renderable : m_renderables) {
		render(*renderable);
	}

	SDL_GL_SwapBuffers();
}

void GraphicsSubsystem::registerComponent(Renderable *component) {
	m_renderables.push_back(component);
	std::sort(m_renderables.begin(), m_renderables.end(), [=](Renderable *a, Renderable *b) {
		return a->zIndex() < b->zIndex();
	});
}

void GraphicsSubsystem::unregisterComponent(Renderable *component) {
	auto it = std::find(m_renderables.begin(), m_renderables.end(), component);
	if (it == m_renderables.end())
		return;
	m_renderables.erase(it);
}

void GraphicsSubsystem::setCamera(Object *object) {
	m_camera = object;
}

void GraphicsSubsystem::setColor(const Color &color) {
	glColor4f(color.r, color.g, color.b, color.a);
}

void GraphicsSubsystem::render(const Renderable &renderable) {
	Positionable *positionable = renderable.object()->component<Positionable>();
	Shape *shape = renderable.object()->component<Shape>();
	if (!positionable || !shape)
		return;

	// Set position
	glPushMatrix();
	Vector2 pos = positionable->pos();
	pos -= (pos - m_camera->component<Positionable>()->pos()) * renderable.parallax();
	glTranslatef(pos.x, pos.y, 0);

	Rect rect = shape->boundingBox();
	float zIndex = renderable.zIndex();
	const Gradient &gradient = renderable.gradient();
	setColor(renderable.color());
	if (renderable.texture()) {
		renderable.texture()->draw(rect.x, rect.y, rect.w, rect.h);
	} else if (gradient.first.a > 0 || gradient.second.a > 0) {
		glBegin(GL_QUADS);
			setColor(gradient.second);
			glVertex3f(rect.x, rect.y, 0.0f);
			glVertex3f(rect.x + rect.w, rect.y, 0.0f);
			setColor(gradient.first);
			glVertex3f(rect.x + rect.w, rect.y + rect.h, 0.0f);
			glVertex3f(rect.x, rect.y + rect.h, 0.0f);
		glEnd();
	} else {
		glBegin(GL_POLYGON);
		for (auto &vector : shape->shape().points) {
			glVertex3f(vector.x, vector.y, 0.0f);
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

		glVertex3f(start.x, start.y, 0.0f);
		glVertex3f(end.x, end.y, 0.0f);
	}
	glEnd();

	// Debug velocity and acceleration
	Movable *movable = renderable.object()->component<Movable>();
	if (movable) {
		Vector2 vel = movable->velocity()/5;
		Vector2 acc = movable->acceleration()/100;
		glBegin(GL_LINES);
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0.0f);
		glVertex3f(vel.x, vel.y, 0.0f);
		glColor3f(1, 1, 0);
		glVertex3f(0, 0, 0.0f);
		glVertex3f(acc.x, acc.y, 0.0f);
		glEnd();
	}

#endif /* end of DEBUG_RENDERABLE */

	glPopMatrix();
}
