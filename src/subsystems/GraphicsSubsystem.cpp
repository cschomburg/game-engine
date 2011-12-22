#include <iostream>
#include <iterator>
#include <sstream>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "Application.h"
#include "Font.h"
#include "Math.h"
#include "Object.h"
#include "components/Body.h"
#include "components/Renderable.h"
#include "Texture.h"
#include "subsystems/GraphicsSubsystem.h"

GraphicsSubsystem::GraphicsSubsystem(GameEngine *engine)
	: Subsystem(engine) {
	engine->objectRegistered.connect(boost::bind(&GraphicsSubsystem::registerObject, this, _1));
	engine->objectUnregistered.connect(boost::bind(&GraphicsSubsystem::unregisterObject, this, _1));
}

GraphicsSubsystem::~GraphicsSubsystem() {}

bool GraphicsSubsystem::init() {
	Application *app = Application::instance();
	int width = app->displayWidth();
	int height = app->displayHeight();
	m_lastSecond = app->time();
	m_frameCount = 0;
	m_fps = 0;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-float(width) / 2, float(width)/2, -float(height)/2, float(height)/2, -1.1f, 1.1f);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_BLEND);

	m_font16 = Application::instance()->manager()->font("res/font.ttf", 16);
	m_font32 = Application::instance()->manager()->font("res/font.ttf", 32);
	m_font48 = Application::instance()->manager()->font("res/font.ttf", 48);
}

void GraphicsSubsystem::update() {
	m_frameCount++;
	int time = Application::instance()->time();
	if (time >= m_lastSecond+1000) {
		m_lastSecond = time;
		m_fps = m_frameCount;
		m_frameCount = 0;
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// TODO: Camera zoom
	Vector2 pos;
	if (m_camera) {
		pos = m_camera->component<Body>()->pos();
	}
	glScalef(100.0f, 100.0f, 1.0f);
	glTranslatef(-pos.x, -pos.y, 0.0f);

	for (auto &renderable : m_renderables) {
		render(*renderable);
	}

	glLoadIdentity();
	glColor3f(0.0f, 0.0f, 0.0f);
	m_font32->draw(1000, 150, "Test all the things!");

	setColor(Color::fromInt(0xff, 0xee, 0x88));

	m_font16->draw(400, 100, "Graphics FPS");
	std::stringstream fpsString;
	fpsString << m_fps;
	m_font48->draw(400, 30, fpsString.str());

	SDL_GL_SwapBuffers();
}

void GraphicsSubsystem::registerObject(Object *object) {
	Renderable *component = object->component<Renderable>();
	if (!component)
		return;

	m_renderables.push_back(component);
	std::sort(m_renderables.begin(), m_renderables.end(), [=](Renderable *a, Renderable *b) {
		return a->zIndex() < b->zIndex();
	});
}

void GraphicsSubsystem::unregisterObject(Object *object) {
	Renderable *component = object->component<Renderable>();
	if (!component)
		return;

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
	Body *body= renderable.object()->component<Body>();
	if (!body)
		return;

	// Set position
	glPushMatrix();
	Vector2 pos = body->pos();
	if (m_camera) {
		pos -= (pos - m_camera->component<Body>()->pos()) * renderable.parallax();
	}
	glTranslatef(pos.x, pos.y, 0);
	glRotatef(-radToDeg(body->angle()), 0, 0, 1.0f);

	// Blend mode
	switch (renderable.blendMode()) {
	default:
	case BlendMode::Blend:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); break;
	case BlendMode::Add:
		glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA); break;
	case BlendMode::Screen:
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); break;
	}

	float zIndex = renderable.zIndex();
	const Gradient &gradient = renderable.gradient();
	setColor(renderable.color());

	Convex shape = renderable.shape();
	if (shape.points.size() == 4) {
		if (renderable.texture()) {
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, renderable.texture()->texture());

			glBegin(GL_QUADS);
				glTexCoord2i(0, 1);
				glVertex3f(shape.points[0].x, shape.points[0].y, 0.0f);

				glTexCoord2i(1, 1);
				glVertex3f(shape.points[1].x, shape.points[1].y, 0.0f);

				glTexCoord2i(1, 0);
				glVertex3f(shape.points[2].x, shape.points[2].y, 0.0f);

				glTexCoord2i(0, 0);
				glVertex3f(shape.points[3].x, shape.points[3].y, 0.0f);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		} else if (gradient.first.a > 0 || gradient.second.a > 0) {
			glBegin(GL_QUADS);
				setColor(gradient.second);
				glVertex3f(shape.points[0].x, shape.points[0].y, 0.0f);
				glVertex3f(shape.points[1].x, shape.points[1].y, 0.0f);
				setColor(gradient.first);
				glVertex3f(shape.points[2].x, shape.points[2].y, 0.0f);
				glVertex3f(shape.points[3].x, shape.points[3].y, 0.0f);
			glEnd();
		} else {
			glBegin(GL_QUADS);
				glVertex3f(shape.points[0].x, shape.points[0].y, 0.0f);
				glVertex3f(shape.points[1].x, shape.points[1].y, 0.0f);
				glVertex3f(shape.points[2].x, shape.points[2].y, 0.0f);
				glVertex3f(shape.points[3].x, shape.points[3].y, 0.0f);
			glEnd();
		}
	} else {
		glBegin(GL_POLYGON);
		for (auto &vector : shape.points) {
			glVertex3f(vector.x, vector.y, 0.0f);
		}
		glEnd();
	}

	glPopMatrix();
}
