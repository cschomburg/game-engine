#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

class Texture {

public:
	Texture(GLuint texture, int width, int height);
	~Texture();

	static Texture * fromFile(const char * file);
	void draw(float x, float y, float width = 0, float height = 0);

private:
	GLuint m_texture;
	int m_width;
	int m_height;
};

#endif /* end of include guard: TEXTURE_H */
