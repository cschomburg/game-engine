#include <SDL/SDL_opengl.h>

#include "components/SolidRenderable.h"

SolidRenderable::SolidRenderable()
	: Renderable("SolidRenderable") {}

SolidRenderable::~SolidRenderable() {}

void SolidRenderable::render() {
	Renderable::render();

	glBegin(GL_QUADS);
		const Rect &r = boundingRect();
		glTexCoord2i(0, 1);
		glVertex3f(r.bottomLeft().x, r.bottomLeft().y, 0.0f);
		glTexCoord2i(1, 1);
		glVertex3f(r.bottomRight().x, r.bottomRight().y, 0.0f);
		glTexCoord2i(1, 0);
		glVertex3f(r.topRight().x, r.topRight().y, 0.0f);
		glTexCoord2i(0, 0);
		glVertex3f(r.topLeft().x, r.topLeft().y, 0.0f);
	glEnd();
}
