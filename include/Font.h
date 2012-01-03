#ifndef FONT_H
#define FONT_H

#include <memory>
#include <string>
#include <vector>
#include <ft2build.h>
#include <freetype/ftglyph.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "Resource.h"

class Font;

class Font : public Resource {
public:
	typedef std::shared_ptr<Font> Ptr;

	Font(const std::string &file, int height);
	virtual ~Font();

	void draw(float x, float y, const std::string &text);

private:
	void makeDisplayList(FT_Face face, char ch);

private:
	std::string m_filePath;
	float m_height;
	GLuint m_textures[128];
	GLuint m_displayLists;
};


#endif /* end of include guard: FONT_H */
