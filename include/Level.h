#ifndef LEVEL_H
#define LEVEL_H

#include "Primitives.h"
#include "Prop.h"
#include "Vector2.h"

class Level {
public:
	Level();
	virtual ~Level();

	void setSize(int width, int height);
	void setBackground(Color colorA, Color colorB);

	void onInit();
	void onRender();

private:
	Vector2 m_size;

	Color m_bgColorA;
	Color m_bgColorB;

	Prop * m_sun;
	Prop * m_island;
	Prop * m_tree;
};

#endif /* end of include guard: LEVEL_H */
