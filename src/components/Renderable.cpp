#include <string>
#include <vector>
#include <SDL/SDL_opengl.h>

#include "Application.h"
#include "components/Renderable.h"
#include "Object.h"
#include "Texture.h"
#include "subsystems/GraphicsSubsystem.h"

const ComponentType Renderable::componentType = "Renderable";

Renderable::Renderable(Object *object)
	: Component(componentType, object) {
	m_color = Color(1, 1, 1, 1);
	m_gradient = Gradient();
	m_texture = nullptr;
	m_zIndex = 1.0f;
	m_blendMode = BlendMode::Blend;
	object->engine()->graphics()->registerComponent(this);
}

Renderable::~Renderable() {
	object()->engine()->graphics()->unregisterComponent(this);
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
	m_texture = Application::instance()->manager()->texture(texturePath);
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
