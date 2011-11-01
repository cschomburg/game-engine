#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <string>
#include <utility>

#include "Color.h"
#include "Component.h"
#include "Vector2.h"

class Object;
class Texture;

typedef std::pair<Color, Color> Gradient;

class Renderable : public Component {
public:
	Renderable(Object *object);
	virtual ~Renderable();

	const Color &color() const;
	void setColor(const Color &color);

	const Gradient &gradient() const;
	void setGradient(const Gradient &gradient);

	Texture *texture() const;
	void setTexture(const std::string &texturePath);

	float zIndex() const;
	void setZIndex(float zIndex);

	const Vector2 &parallax() const;
	void setParallax(const Vector2 &parallax);

	static const ComponentType componentType;

private:
	Color m_color;
	Gradient m_gradient;
	Texture *m_texture;
	float m_zIndex;
	Vector2 m_parallax;
};

#endif /* end of include guard: RENDERABLE_H */
