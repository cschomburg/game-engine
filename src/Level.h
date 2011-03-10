#ifndef LEVEL_H
#define LEVEL_H

#include <SDL/SDL.h>

class Level {
public:
	Level();
	Level(int width, int height);
	virtual ~Level();

	static Level * fromFile(const char * file);

	void setBackground(Uint8 r, Uint8 g, Uint8 b);

	void onRender(SDL_Surface * display);

private:
	int m_width;
	int m_height;

	char m_bgR;
	char m_bgG;
	char m_bgB;
};

#endif /* end of include guard: LEVEL_H */
