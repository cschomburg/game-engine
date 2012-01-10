#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include <memory>
#include <string>

#include "Color.h"
#include "Font.h"
#include "Widget.h"

class TextWidget : public Widget {
public:
	typedef std::shared_ptr<TextWidget> Ptr;

	TextWidget(const std::string &name);
	virtual ~TextWidget();

	Color color() const;
	void setColor(const Color &color);

	void setFont(const std::string &file, int height);

	std::string text() const;
	void setText(const std::string &text);

	virtual void render();

private:
	Color m_color;
	Font::Ptr m_font;
	std::string m_text;
};

#endif /* end of include guard: TEXTWIDGET_H */
