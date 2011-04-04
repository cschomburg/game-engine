#ifndef PROP_H
#define PROP_H

#include "Positionable.h"
#include "Texture.h"

class Prop : public Positionable {
public:
	Prop(float x, float y, float w, float h, const char * texturePath);

	virtual void onRender();

private:
	Vector2 m_size;
	Texture * m_texture;
};

#endif /* end of include guard: PROP_H */
