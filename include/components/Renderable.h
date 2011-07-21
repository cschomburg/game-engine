#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Color.h"
#include "Component.h"

class Texture;

class Renderable : public Component {
public:
	Renderable(Object *object);
	virtual ~Renderable();

	void setGradient(const Color &colorA, const Color &colorB);
	void setTexture(const std::string &texturePath);

	void onRender();

	static const ComponentType componentType;

private:
	Texture *m_texture;
	Color m_colorA;
	Color m_colorB;
};

#endif /* end of include guard: RENDERABLE_H */
