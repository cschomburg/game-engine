#define NO_SDL_GLEXT

#include <algorithm>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
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
	m_screen = Rect(Vector2(), Vector2(width, height), Anchor::center);

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(m_screen.left(), m_screen.right(), m_screen.bottom(), m_screen.top(), -1.1f, 1.1f);

	setScale(100.f);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_BLEND);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cout << "Error: "  << glewGetErrorString(err) << std::endl;
		return false;
	}

	std::ifstream ifs("res/shaders/bloom1.frag");
	std::string fs((std::istreambuf_iterator<char>(ifs)),
	                std::istreambuf_iterator<char>());
	const char *fsSource = fs.c_str();

	GLhandleARB fragShader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fsSource, NULL);
	glCompileShader(fragShader);


	GLhandleARB program = glCreateProgramObjectARB();
	glAttachObjectARB(program, fragShader);
	glLinkProgramARB(program);
	glUseProgramObjectARB(program);
	GLenum errCode = glGetError();
	if (errCode != GL_NO_ERROR) {
		std::cout << gluErrorString(errCode) << std::endl;
	}

	return true;
}

void GraphicsSubsystem::update() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto renderable : m_renderables[DrawLayer::Background]) {
		render(renderable);
	}

	glScalef(m_scale, m_scale, 1.0f);
	if (m_camera) {
		Vector2 pos = m_camera->pos();
		glTranslatef(-pos.x, -pos.y, 0.0f);
	}
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
	m_scale = scale;
}

Rect GraphicsSubsystem::viewport() const {
	Rect viewport = m_screen;
	viewport.scale(1.0f/m_scale);
	if (m_camera) {
		viewport.translate(m_camera->pos());
	}
	return viewport;
}

const Rect &GraphicsSubsystem::screen() const {
	return m_screen;
}

void GraphicsSubsystem::render(Renderable::Ptr renderable) {
	IPositionable::Ptr positionable = renderable->positionable();
	Rect boundingRect = renderable->boundingRect();
	if (!positionable)
		return;

	Vector2 pos = positionable->pos();
	if (renderable->drawLayer() == DrawLayer::World) {
		if (m_camera) { // Parallax
			Vector2 camPos = m_camera->pos();
			pos += (camPos - pos) * renderable->parallax();
		}
		boundingRect.translate(pos);
		if (!viewport().intersects(boundingRect))
			return;
	} else {
		boundingRect.translate(pos);
		if (!m_screen.intersects(boundingRect))
			return;
	}


	// Set position and scale
	glPushMatrix();
	glTranslatef(pos.x, pos.y, 0);
	glRotatef(radToDeg(positionable->angle()), 0, 0, 1.0f);
	glScalef(renderable->scale(), renderable->scale(), 1.0f);

	renderable->render();

	glPopMatrix();
}
