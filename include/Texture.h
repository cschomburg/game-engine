#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "Resource.h"

class Texture : public Resource {
public:
	Texture(const std::string &file);

	void draw(float x, float y, float width = 0, float height = 0);

	void load();
	void destroy();

private:
	std::string m_filePath;
	GLuint m_texture;
	int m_width;
	int m_height;
};

#endif /* end of include guard: TEXTURE_H */
