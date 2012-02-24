#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "GameEngine.h"
#include "Math.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "subsystems/GraphicsSubsystem.h"

GraphicsSubsystem::GraphicsSubsystem(GameEngine *engine)
	: Subsystem(engine) {
	m_camera = 0;
}

GraphicsSubsystem::~GraphicsSubsystem() {}

bool GraphicsSubsystem::init() {
	int width = engine()->displayWidth();
	int height = engine()->displayHeight();

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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto renderable : m_renderables[DrawLayer::Background]) {
		render(renderable);
	}

	Vector2 pos;
	if (m_camera) {
		pos = m_camera->pos();
	}
	glScalef(m_scale, m_scale, 1.0f);
	glTranslatef(-pos.x, -pos.y, 0.0f);
	for (auto renderable : m_renderables[DrawLayer::World]) {
		render(renderable);
	}

	glLoadIdentity();
	for (auto renderable : m_renderables[DrawLayer::Foreground]) {
		render(renderable);
	}

	SDL_GL_SwapBuffers();
}

void GraphicsSubsystem::registerRenderable(Renderable::Ptr renderable) {
	DrawLayer layer = renderable->drawLayer();
	float zIndex = renderable->zIndex();

	RenderableList &renderables = m_renderables[layer];
	auto itNext = std::find_if(renderables.begin(), renderables.end(), [&](Renderable::Ptr r) {
		return zIndex < r->zIndex();
	});
	renderables.insert(itNext, renderable);
}

void GraphicsSubsystem::unregisterRenderable(Renderable::Ptr renderable) {
	DrawLayer layer = renderable->drawLayer();

	RenderableList &renderables = m_renderables[layer];
	auto it = std::find(renderables.begin(), renderables.end(), renderable);
	if (it == renderables.end())
		return;
	renderables.erase(it);
}

IPositionable::Ptr GraphicsSubsystem::camera() {
	return m_camera;
}

void GraphicsSubsystem::setCamera(IPositionable::Ptr positionable) {
	m_camera = positionable;
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
	Rect boundingRect = renderable->boundingRect();
	if (!positionable || boundingRect.size().isZero())
		return;

	Vector2 pos = positionable->pos();
	if (renderable->drawLayer() == DrawLayer::World) {
		Vector2 camPos;
		if (m_camera) {
			camPos = m_camera->pos();
		}
		pos -= (pos - camPos) * renderable->parallax();
		boundingRect.translate(pos-camPos);
	}

	if (!m_viewport.intersects(boundingRect))
		return;

	// Set position and scale
	glPushMatrix();
	glTranslatef(pos.x, pos.y, 0);
	glRotatef(radToDeg(positionable->angle()), 0, 0, 1.0f);
	glScalef(renderable->scale(), renderable->scale(), 1.0f);

	renderable->render();

	glPopMatrix();
}
