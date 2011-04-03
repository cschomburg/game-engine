#include <SDL/SDL_opengl.h>

#include "Camera.h"

void Camera::onRender() {
	glTranslatef(-pos().x, -pos().y, 0);
}
