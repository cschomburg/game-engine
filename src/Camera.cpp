#include <SDL/SDL_opengl.h>

#include "Application.h"
#include "Level.h"
#include "Camera.h"

Camera::Camera() {
	m_tracked = 0;
	setZoomLevel(1.0f);
}

Camera::~Camera() {}

void Camera::onUpdate() {
	if (m_tracked) {
		setPos(m_tracked->center(), true);
	}

	Level * level = Application::instance()->engine()->level();
	if (!level->contains(*this)) {
		float lDiff = level->left() - left();
		float rDiff = right() - level->right();
		float tDiff = top() - level->top();
		float bDiff = level->bottom() - bottom();

		if (lDiff > 0 && rDiff > 0) {
			x += (lDiff - rDiff)/2;
		} else if (lDiff > 0) {
			x += lDiff;
		} else if(rDiff > 0) {
			x -= rDiff;
		}

		if (tDiff > 0 && bDiff > 0) {
			y += (bDiff - tDiff)/2;
		} else if (tDiff > 0) {
			y -= tDiff;
		} else if (bDiff > 0) {
			y += bDiff;
		}
	}
}

void Camera::onRender() {
	Vector2 pos = center();
	glScalef(m_zoomLevel, m_zoomLevel, 1.0f);
	glTranslatef(-pos.x, -pos.y, 0);
}

void Camera::track(GameObject * object) {
	m_tracked = object;
}

float Camera::zoomLevel() const {
	return m_zoomLevel;
}

void Camera::setZoomLevel(float zoomLevel) {
	m_zoomLevel = zoomLevel;
	Vector2 pos = center();
	w = Application::instance()->displayWidth() / m_zoomLevel;
	h = Application::instance()->displayHeight() / m_zoomLevel;
	setPos(pos, true);
}
