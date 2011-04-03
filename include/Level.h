#ifndef LEVEL_H
#define LEVEL_H

#include "Texture.h"

class Level {
public:
	Level();
	virtual ~Level();

	void setSize(int width, int height);
	void setBackground(int r, int g, int b);

	void onRender();

private:
	int m_width;
	int m_height;

	int m_backgroundR;
	int m_backgroundG;
	int m_backgroundB;

	Texture * m_texture;
};

#endif /* end of include guard: LEVEL_H */
