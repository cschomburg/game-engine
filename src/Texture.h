#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL/SDL.h>

class Texture {

public:
	Texture(SDL_Surface * surface = 0);
	~Texture();

	SDL_Surface * surface() const;

	static Texture * fromFile(const char * file);
	bool draw(SDL_Surface * dest, int x, int y);
	bool draw(SDL_Surface * dest, int x, int y, int x2, int y2, int w, int h);

private:
	SDL_Surface * m_surface;

};

#endif /* end of include guard: TEXTURE_H */
