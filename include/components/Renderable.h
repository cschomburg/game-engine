#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Color.h"
#include "Component.h"

class Texture;

class Renderable : public Component {
public:
	Renderable(Object *object);
	virtual ~Renderable();

	void setColor(const Color &color);
	void setGradient(const Color &colorA, const Color &colorB);
	void setTexture(const std::string &texturePath);

	void onRender();

	static const ComponentType componentType;

private:
	Color m_color;
	Color m_colorA;
	Color m_colorB;
	Texture *m_texture;
};

#endif /* end of include guard: RENDERABLE_H */
