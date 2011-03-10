#include <SDL/SDL_image.h>

#include "Texture.h"

Texture::Texture(SDL_Surface * surface) {
	m_surface = surface;
}

Texture::~Texture() {
	if(m_surface == 0)
		return;

	SDL_FreeSurface(m_surface);
	m_surface = 0;
}

SDL_Surface * Texture::surface() const {
	return m_surface;
}

Texture * Texture::fromFile(const char * file) {
	SDL_Surface * temp = 0;

	if ((temp = IMG_Load(file)) == 0) {
		printf("Could not load image: %s\n", file);
		return 0;
	}

	SDL_Surface * surface = SDL_DisplayFormatAlpha(temp);
	SDL_FreeSurface(temp);

	return (new Texture(surface));
}

bool Texture::draw(SDL_Surface * dest, int x, int y) {
	if (dest == 0 || this->surface() == 0)
		return false;

	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;

	SDL_BlitSurface(this->surface(), 0, dest, &destRect);

	return true;
}

bool Texture::draw(SDL_Surface * dest, int x, int y, int x2, int y2, int w, int h) {
	if (dest == 0 || this->surface() == 0)
		return false;

	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;

	SDL_Rect srcRect;
	srcRect.x = x2;
	srcRect.y = y2;
	srcRect.w = w;
	srcRect.h = h;

	SDL_BlitSurface(this->surface(), &srcRect, dest, &destRect);

	return true;
}
