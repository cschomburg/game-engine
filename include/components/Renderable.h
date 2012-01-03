#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <memory>
#include <string>
#include <utility>

#include "Color.h"
#include "Component.h"
#include "Convex.h"
#include "interfaces/IPositionable.h"

class Texture;

typedef std::pair<Color, Color> Gradient;

enum class BlendMode {
	Add,
	Blend,
	Screen,
};

class Renderable : public Component {
public:
	typedef std::shared_ptr<Renderable> Ptr;

	Renderable(std::string objectID);
	virtual ~Renderable();

	bool isValid() const;

	IPositionable::WeakPtr positionable() const;
	void setPositionable(IPositionable::WeakPtr positionable);

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

	Convex shape() const;
	void setShape(const Convex &convex);

private:
	IPositionable::WeakPtr m_positionable;
	Color m_color;
	Gradient m_gradient;
	std::shared_ptr<Texture> m_texture;
	float m_zIndex;
	Vector2 m_parallax;
	BlendMode m_blendMode;
	Convex m_shape;
};

#endif /* end of include guard: RENDERABLE_H */
