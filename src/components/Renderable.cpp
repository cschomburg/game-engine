#include <string>
#include <vector>
#include <SDL/SDL_opengl.h>

#include "GameEngine.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "components/Renderable.h"
#include "subsystems/GraphicsSubsystem.h"

Renderable::Renderable(std::string objectID)
	: Component("Renderable", objectID) {
	m_color = Color(1, 1, 1, 1);
	m_gradient = Gradient();
	m_texture = 0;
	m_zIndex = 0.0f;
	m_blendMode = BlendMode::Blend;
}

Renderable::~Renderable() {}

bool Renderable::isValid() const {
	return !m_shape.points.empty();
}

IPositionable::Ptr Renderable::positionable() const {
	return m_positionable;
}

void Renderable::setPositionable(IPositionable::Ptr positionable) {
	m_positionable = positionable;
}

const Color &Renderable::color() const {
	return m_color;
}

void Renderable::setColor(const Color &color) {
	m_color = color;
}

const Gradient &Renderable::gradient() const {
	return m_gradient;
}

void Renderable::setGradient(const Gradient &gradient) {
	m_gradient = gradient;
}

std::shared_ptr<Texture> Renderable::texture() const {
	return m_texture;
}

void Renderable::setTexture(const std::string &texturePath) {
	m_texture = GameEngine::instance()->manager()->texture(texturePath);
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

BlendMode Renderable::blendMode() const {
	return m_blendMode;
}

void Renderable::setBlendMode(BlendMode blendMode) {
	m_blendMode = blendMode;
}

const Convex &Renderable::shape() const {
	return m_shape;
}

void Renderable::setShape(const Convex &convex) {
	m_shape = convex;
}
