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
		glVertex3f(r.left(), r.bottom(), 0.0f);
		glTexCoord2i(1, 1);
		glVertex3f(r.right(), r.bottom(), 0.0f);
		glTexCoord2i(1, 0);
		glVertex3f(r.right(), r.top(), 0.0f);
		glTexCoord2i(0, 0);
		glVertex3f(r.left(), r.top(), 0.0f);
	glEnd();
}
