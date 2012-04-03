#include <SDL/SDL_opengl.h>

#include "components/Renderable.h"
#include "subsystems/GraphicsSubsystem.h"

Renderable::Renderable() {
	m_zIndex = 0.0f;
	m_drawLayer = DrawLayer::World;
	m_parallax = Vector2();
	m_boundingRect = Rect();
	m_scale = 1.0f;
	m_color = Color(1, 1, 1, 1);
	m_blendMode = BlendMode::Blend;
}

Renderable::~Renderable() {}

DrawLayer Renderable::drawLayer() const {
	return m_drawLayer;
}

void Renderable::setDrawLayer(DrawLayer layer) {
	m_drawLayer = layer;
}

float Renderable::zIndex() const {
	return m_zIndex;
}

void Renderable::setZIndex(float zIndex) {
	m_zIndex = zIndex;
}

const Vector2 &Renderable::parallax() const {
	return m_parallax;
}

void Renderable::setParallax(const Vector2 &parallax) {
	m_parallax = parallax;
}

const Rect &Renderable::boundingRect() const {
	return m_boundingRect;
}

void Renderable::setBoundingRect(const Rect &rect) {
	m_boundingRect = rect;
}

float Renderable::scale() const {
	return m_scale;
}

void Renderable::setScale(float scale) {
	m_scale = scale;
}

const Color &Renderable::color() const {
	return m_color;
}

void Renderable::setColor(const Color &color) {
	m_color = color;
}

BlendMode Renderable::blendMode() const {
	return m_blendMode;
}

void Renderable::setBlendMode(BlendMode blendMode) {
	m_blendMode = blendMode;
}

void Renderable::render() {
	glColor4f(color().r, color().g, color().b, color().a);

	switch (m_blendMode) {
	default:
	case BlendMode::Blend:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); break;
	case BlendMode::Add:
		glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA); break;
	case BlendMode::Screen:
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); break;
	}
}
