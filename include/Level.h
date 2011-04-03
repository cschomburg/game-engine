#ifndef LEVEL_H
#define LEVEL_H

#include "Texture.h"
#include "Primitives.h"

class Level {
public:
	Level();
	virtual ~Level();

	void setSize(int width, int height);
	void setBackground(Color colorA, Color colorB);

	void onInit();
	void onRender();

private:
	int m_width;
	int m_height;

	Color m_bgColorA;
	Color m_bgColorB;

	Texture * m_sun;
	Texture * m_island;
	Texture * m_tree;
};

#endif /* end of include guard: LEVEL_H */
