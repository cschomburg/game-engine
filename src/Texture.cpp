#include <SDL/SDL_image.h>

#include "Texture.h"

Texture::Texture(const std::string &file) {
	m_texture = 0;
	m_filePath = file;
	m_width = 0;
	m_height = 0;

	SDL_Surface * surface = 0;

	if ((surface= IMG_Load(m_filePath.c_str())) == 0) {
		printf("Could not load image: %s\n", m_filePath.c_str());
		return;
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
		printf("warning: image '%s' is not truecolor ... this will probably break\n", m_filePath.c_str());
	}

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
				 textureFormat, GL_UNSIGNED_BYTE, surface->pixels);

	SDL_FreeSurface(surface);

	m_texture = texture;
	m_width = surface->w;
	m_height = surface->h;
}

Texture::~Texture() {
	if (!m_texture)
		return;

	glDeleteTextures(1, &m_texture);
	m_texture = 0;
}

void Texture::draw(float x, float y, float width, float height) {
	if (!m_texture)
		return;

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
		glVertex3f(x, y, 0.0f);

		glTexCoord2i(1, 1);
		glVertex3f(x + width, y, 0.0f);

		glTexCoord2i(1, 0);
		glVertex3f(x + width, y + height, 0.0f);

		glTexCoord2i(0, 0);
		glVertex3f(x, y + height, 0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

