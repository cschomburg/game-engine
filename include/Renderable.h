#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <string>

#include "Positionable.h"
#include "Texture.h"

class Renderable : public Positionable {
public:
	Renderable();
	virtual ~Renderable();

	void setTexture(const std::string &texturePath);
	virtual void onRender();

private:
	Texture * m_texture;
};

#endif /* end of include guard: RENDERABLE_H */
