#ifndef FONTRENDERABLE_H
#define FONTRENDERABLE_H

#include <string>
#include "components/Renderable.h"

class Font;

class FontRenderable : public Renderable {
public:
	typedef std::shared_ptr<FontRenderable> Ptr;

	FontRenderable();
	virtual ~FontRenderable();

	std::shared_ptr<Font> font() const;
	void setFont(const std::string &fontPath, int size);

	std::string text() const;
	void setText(const std::string &text);

	void render();

private:
	std::shared_ptr<Font> m_font;
	std::string m_text;
};

#endif /* end of include guard: FONTRENDERABLE_H */
