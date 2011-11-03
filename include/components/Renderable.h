#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <memory>
#include <string>
#include <utility>

#include "Color.h"
#include "Component.h"
#include "Vector2.h"

class Object;
class Texture;

typedef std::pair<Color, Color> Gradient;

enum class BlendMode {
	Add,
	Blend,
	Screen,
};

class Renderable : public Component {
public:
	Renderable(Object *object);
	virtual ~Renderable();

	const Color &color() const;
	void setColor(const Color &color);

	const Gradient &gradient() const;
	void setGradient(const Gradient &gradient);

	std::shared_ptr<Texture> texture() const;
	void setTexture(const std::string &texturePath);

	float zIndex() const;
	void setZIndex(float zIndex);

	const Vector2 &parallax() const;
	void setParallax(const Vector2 &parallax);

	BlendMode blendMode() const;
	void setBlendMode(BlendMode blendMode);

	static const ComponentType componentType;

private:
	Color m_color;
	Gradient m_gradient;
	std::shared_ptr<Texture> m_texture;
	float m_zIndex;
	Vector2 m_parallax;
	BlendMode m_blendMode;
};

#endif /* end of include guard: RENDERABLE_H */
