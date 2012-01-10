#ifndef SOLIDWIDGET_H
#define SOLIDWIDGET_H

#include "Color.h"
#include "Widget.h"

class SolidWidget : public Widget {
public:
	typedef std::shared_ptr<SolidWidget> Ptr;

	SolidWidget(const std::string &name);
	virtual ~SolidWidget();

	Color color() const;
	void setColor(const Color &color);

	virtual void render();

private:
	Color m_color;
};

#endif /* end of include guard: SOLIDWIDGET_H */
