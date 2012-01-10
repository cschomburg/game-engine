#include <SDL/SDL_opengl.h>

#include "GameEngine.h"
#include "ResourceManager.h"
#include "widgets/TextWidget.h"


TextWidget::TextWidget(const std::string &name)
	: Widget("TextWidget", name) {}

TextWidget::~TextWidget() {}

Color TextWidget::color() const {
	return m_color;
}

void TextWidget::setColor(const Color &color) {
	m_color = color;
}

void TextWidget::setFont(const std::string &file, int height) {
	m_font = GameEngine::instance()->manager()->font(file, height);
}

std::string TextWidget::text() const {
	return m_text;
}

void TextWidget::setText(const std::string &text) {
	m_text = text;
}

void TextWidget::render() {
	Widget::render();
	if (m_color.a == 0.0f || !m_font || m_text.empty())
		return;

	glColor4f(m_color.r, m_color.g, m_color.b, m_color.a);
	m_font->draw(rect().bottomLeft().x, rect().bottomLeft().y, m_text);
}
