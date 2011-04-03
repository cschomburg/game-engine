#include <SDL/SDL_image.h>

#include "Texture.h"

Texture::Texture(GLuint texture, int width, int height) {
	m_texture = texture;
	m_width = width;
	m_height = height;
}

Texture::~Texture() {
	if(m_texture == 0)
		return;

	glDeleteTextures(1, &m_texture);
	m_texture = 0;
}

Texture * Texture::fromFile(const char * file) {
	SDL_Surface * surface = 0;

	if ((surface= IMG_Load(file)) == 0) {
		printf("Could not load image: %s\n", file);
		return 0;
	}

	if ((surface->w & (surface->w - 1)) != 0) {
		printf("warning: image '%s' width is not a power of 2\n", file);
	}
	if ((surface->h & (surface->h - 1)) != 0) {
		printf("warning: image '%s' height is not a power of 2\n", file);
	}

	GLenum textureFormat;
	GLint nOfColors = surface->format->BytesPerPixel;
	if (nOfColors == 4) {
		if (surface->format->Rmask == 0x000000ff) {
			textureFormat = GL_RGBA;
		} else {
			textureFormat = GL_BGRA;
		}
	} else if (nOfColors == 3) {
		if (surface->format->Rmask == 0x000000ff) {
			textureFormat = GL_RGB;
		} else {
			textureFormat = GL_BGR;
		}
	} else {
		printf("warning: image '%s' is not truecolor ... this will probably break\n", file);
	}

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
				 textureFormat, GL_UNSIGNED_BYTE, surface->pixels);

	SDL_FreeSurface(surface);

	return (new Texture(texture, surface->w, surface->h));
}

void Texture::draw(float x, float y, float width, float height) {
	if (width == 0) {
		width = m_width;
	}
	if (height == 0) {
		height = m_height;
	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glBegin(GL_QUADS);
		glTexCoord2i(0, 1);
		glVertex3f(x, y - height, 0.0f);

		glTexCoord2i(1, 1);
		glVertex3f(x + width, y - height, 0.0f);

		glTexCoord2i(1, 0);
		glVertex3f(x + width, y, 0.0f);

		glTexCoord2i(0, 0);
		glVertex3f(x, y, 0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
