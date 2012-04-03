#include "Font.h"
#include "GameEngine.h"
#include "ResourceManager.h"

#include "components/FontRenderable.h"

FontRenderable::FontRenderable()
	: Renderable() {
	m_font = 0;
}

FontRenderable::~FontRenderable() {}

Font::Ptr FontRenderable::font() const {
	return m_font;
}

void FontRenderable::setFont(const std::string &fontPath, int size) {
	m_font = GameEngine::instance()->manager()->font(fontPath, size);
}

std::string FontRenderable::text() const {
	return m_text;
}

void FontRenderable::setText(const std::string &text) {
	m_text = text;
}

void FontRenderable::render() {
	if (m_text.empty())
		return;

	Renderable::render();
	m_font->draw(0, 0, m_text);
}
