#include <SDL/SDL_opengl.h>

#include "widgets/SolidWidget.h"

SolidWidget::SolidWidget(const std::string &name)
	: Widget("SolidWidget", name) {}

SolidWidget::~SolidWidget() {}

Color SolidWidget::color() const {
	return m_color;
}

void SolidWidget::setColor(const Color &color) {
	m_color = color;
}

void SolidWidget::render() {
	Widget::render();
	if (m_color.a == 0.0f)
		return;

	glColor4f(m_color.r, m_color.g, m_color.b, m_color.a);

	glBegin(GL_QUADS);
		Rect r = rect();
		glTexCoord2i(0, 1);
		glVertex3f(r.bottomRight().x, r.bottomRight().y, 0.0f);
		glTexCoord2i(1, 1);
		glVertex3f(r.topRight().x, r.topRight().y, 0.0f);
		glTexCoord2i(1, 0);
		glVertex3f(r.topLeft().x, r.topLeft().y, 0.0f);
		glTexCoord2i(0, 0);
		glVertex3f(r.bottomLeft().x, r.bottomLeft().y, 0.0f);
	glEnd();
}
