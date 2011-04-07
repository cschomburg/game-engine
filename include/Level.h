#ifndef LEVEL_H
#define LEVEL_H

#include <vector>

#include "Primitives.h"
#include "Renderable.h"
#include "Vector2.h"

typedef std::vector<Renderable *> renderableVector;

class Level {
public:
	Level();
	virtual ~Level();

	void setSize(int width, int height);
	void setBackground(Color colorA, Color colorB);
	void addRenderable(Renderable * renderable);

	void onInit();
	void onRender();

private:
	Vector2 m_size;

	Color m_bgColorA;
	Color m_bgColorB;

	renderableVector m_renderables;
};

#endif /* end of include guard: LEVEL_H */
