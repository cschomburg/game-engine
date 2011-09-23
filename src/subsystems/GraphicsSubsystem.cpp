#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "Application.h"
#include "Object.h"
#include "components/Positionable.h"
#include "components/Renderable.h"
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
	glOrtho(-float(width) / 2, float(width)/2, -float(height)/2, float(height)/2, -1.0f, 1.0f);

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
	glTranslatef(-pos.x, -pos.y, 0);
	// TODO: Camera zoom

	for (auto &renderable : m_renderables) {
		renderable->render();
	}

	SDL_GL_SwapBuffers();
	SDL_Delay(0);
}

void GraphicsSubsystem::registerComponent(Renderable *component) {
	m_renderables.insert(component);
}

void GraphicsSubsystem::unregisterComponent(Renderable *component) {
	m_renderables.erase(component);
}

void GraphicsSubsystem::setCamera(Object *object) {
	m_camera = object;
}
