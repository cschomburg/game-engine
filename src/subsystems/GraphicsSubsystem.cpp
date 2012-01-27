#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "Math.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "subsystems/GraphicsSubsystem.h"
#include "subsystems/UISubsystem.h"

GraphicsSubsystem::GraphicsSubsystem(GameEngine *engine)
	: Subsystem(engine) {
	m_camera = 0;
}

GraphicsSubsystem::~GraphicsSubsystem() {}

bool GraphicsSubsystem::init() {
	int width = engine()->displayWidth();
	int height = engine()->displayHeight();
	m_lastSecond = engine()->time();
	m_frameCount = 0;
	m_fps = 0;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-float(width) / 2, float(width)/2, -float(height)/2, float(height)/2, -1.1f, 1.1f);

	setScale(100.f);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_BLEND);

	return true;
}

void GraphicsSubsystem::update() {
	m_frameCount++;
	int time = engine()->time();
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
		pos = m_camera->pos();
	}
	glScalef(m_scale, m_scale, 1.0f);
	glTranslatef(-pos.x, -pos.y, 0.0f);

	for (auto renderable : m_renderables) {
		render(renderable);
	}

	// User Interface
	glLoadIdentity();
	engine()->ui()->render();

	SDL_GL_SwapBuffers();
}

void GraphicsSubsystem::registerRenderable(Renderable::Ptr renderable) {
	float zIndex = renderable->zIndex();
	auto itNext = std::find_if(m_renderables.begin(), m_renderables.end(), [&](Renderable::Ptr r) {
		return zIndex < r->zIndex();
	});
	m_renderables.insert(itNext, renderable);

}

void GraphicsSubsystem::unregisterRenderable(Renderable::Ptr renderable) {
	auto it = std::find(m_renderables.begin(), m_renderables.end(), renderable);
	if (it == m_renderables.end())
		return;
	m_renderables.erase(it);
}

IPositionable::Ptr GraphicsSubsystem::camera() {
	return m_camera;
}

void GraphicsSubsystem::setCamera(IPositionable::Ptr positionable) {
	m_camera = positionable;
}

void GraphicsSubsystem::setColor(const Color &color) {
	glColor4f(color.r, color.g, color.b, color.a);
}

float GraphicsSubsystem::scale() const {
	return m_scale;
}

void GraphicsSubsystem::setScale(float scale) {
	m_viewport = Rect(Vector2(), Vector2(
		float(engine()->displayWidth())/scale,
		float(engine()->displayHeight())/scale), true);
	m_scale = scale;
}

Rect GraphicsSubsystem::viewport() const {
	if (!m_camera) {
		return m_viewport;
	}

	Rect viewport = m_viewport;
	viewport.translate(m_camera->pos());
	return viewport;
}

void GraphicsSubsystem::render(Renderable::Ptr renderable) {
	IPositionable::Ptr positionable = renderable->positionable();
	Convex shape = renderable->shape();
	if (!positionable || shape.points.size() == 0)
		return;

	Vector2 camPos;
	if (m_camera) {
		camPos = m_camera->pos();
	}
	Vector2 pos = positionable->pos();
	pos -= (pos - camPos) * renderable->parallax();

	Rect rect = shape.boundingBox();
	rect.translate(pos-camPos);
	if (!m_viewport.intersects(rect))
		return;

	// Set position and scale
	glPushMatrix();
	glTranslatef(pos.x, pos.y, 0);
	glRotatef(radToDeg(positionable->angle()), 0, 0, 1.0f);
	glScalef(renderable->scale(), renderable->scale(), 1.0f);

	// Blend mode
	switch (renderable->blendMode()) {
	default:
	case BlendMode::Blend:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); break;
	case BlendMode::Add:
		glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA); break;
	case BlendMode::Screen:
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); break;
	}

	const Gradient &gradient = renderable->gradient();
	setColor(renderable->color());

	if (shape.points.size() == 4) {
		if (renderable->texture()) {
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, renderable->texture()->texture());

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
