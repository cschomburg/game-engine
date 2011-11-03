#include <stdexcept>

#include "Font.h"

inline int nextPow2(int a) {
	int rval = 1;
	while (rval < a) rval <<= 1;
	return  rval;
}

Font::Font(const std::string &file, int height)
	: Resource() {
	m_filePath = file;
	m_height = height;

	FT_Library library;
	if (FT_Init_FreeType(&library))
		throw std::runtime_error("FT_Init_FreeType failed");

	FT_Face face;
	if (FT_New_Face(library, file.c_str(), 0, &face))
		throw std::runtime_error("FT_New_Face failed");

	// Multiply height with 64 to match FreeType's convention
	FT_Set_Char_Size(face, height << 6, height << 6, 96, 96);

	m_displayLists = glGenLists(128);
	glGenTextures(128, &m_textures[0]);

	for (unsigned char i = 0; i < 128; i++)
		makeDisplayList(face, i);

	FT_Done_Face(face);
	FT_Done_FreeType(library);
}

Font::~Font() {
	glDeleteLists(m_displayLists, 128);
	glDeleteTextures(128, m_textures);
}

void Font::draw(float x, float y, const std::string &text) {
	float height = m_height / 0.63f;

	// TODO: split into lines;

	glPushAttrib(GL_LIST_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT | GL_TRANSFORM_BIT);
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glListBase(m_displayLists);
	float modelviewMatrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrix);

	// Start drawing
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(x, y, 0);
	glMultMatrixf(modelviewMatrix);

	glCallLists(text.length(), GL_UNSIGNED_BYTE, text.c_str());
	glPopMatrix();

	glPopAttrib();
}

void Font::makeDisplayList(FT_Face face, char ch) {
	// Load Glyph for character
	if (FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT))
		throw std::runtime_error("FT_Load_Glyph failed");

	// Move Glyph into object
	FT_Glyph glyph;
	if (FT_Get_Glyph(face->glyph, &glyph))
		throw std::runtime_error("FT_Get_Glyph failed");

	// Convert Glyph to Bitmap
	FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
	FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
	FT_Bitmap &bitmap = bitmap_glyph->bitmap;

	// Resize to OpenGL power of 2 and two channels (luminosity and alpha)
	int width = nextPow2(bitmap.width);
	int height = nextPow2(bitmap.rows);
	GLubyte *expandedData = new GLubyte[2 * width * height];
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int pos = 2 * (x + y*width);
			expandedData[pos] = expandedData[pos+1] =
				(x >= bitmap.width || y >= bitmap.rows) ?
				0 : bitmap.buffer[x + bitmap.width * y];
		}
	}

	// Create OpenGL texture
	glBindTexture(GL_TEXTURE_2D, m_textures[ch]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
		GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expandedData);

	delete[] expandedData;

	// Now we create the Display List
	glNewList(m_displayLists+ch, GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, m_textures[ch]);
	glPushMatrix();

	// Center character correctly
	glTranslatef(bitmap_glyph->left, 0, 0);
	glTranslatef(0, bitmap_glyph->top - bitmap.rows, 0);

	// Calculate real size versus padding space
	float x = float(bitmap.width) / float(width);
	float y = float(bitmap.rows) / float(height);

	// Draw the quad
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex2f(0, bitmap.rows);
	glTexCoord2d(0, y); glVertex2f(0, 0);
	glTexCoord2d(x, y); glVertex2f(bitmap.width, 0);
	glTexCoord2d(x, 0); glVertex2f(bitmap.width, bitmap.rows);
	glEnd();
	glPopMatrix();
	glTranslatef(face->glyph->advance.x >> 6, 0, 0);

	// Increment the raster position as if it were a bitmap font
	// glBitmap(0, 0, 0, 0, face->glyph->advance.x >> 6, 0, NULL);

	glEndList();
}
