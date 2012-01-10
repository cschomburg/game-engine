#ifndef WIDGET_H
#define WIDGET_H

#include <memory>
#include <vector>

#include "Rect.h"
#include "Vector2.h"

class Widget : public std::enable_shared_from_this<Widget> {
public:
	typedef std::shared_ptr<Widget> Ptr;

	Widget();
	Widget(const std::string &type, const std::string &name);
	virtual ~Widget();

	std::string type() const;

	Widget::Ptr parent() const;
	void setParent(Widget::Ptr parent);
	const std::vector<Widget::Ptr> &children() const;
	void addChild(Widget::Ptr child);
	void removeChild(Widget::Ptr child);

	bool isShown() const;
	void setShown(bool shown);

	Rect rect() const;
	Vector2 pos() const;
	Vector2 size() const;
	void setRect(const Rect &rect);
	void setPos(const Vector2 &pos);
	void setSize(const Vector2 &size);

	virtual void render();

private:
	std::string m_type;
	std::string m_name;
	Widget::Ptr m_parent;
	std::vector<Widget::Ptr> m_children;

	bool m_shown;
	Rect m_rect;
};

#endif /* end of include guard: WIDGET_H */
