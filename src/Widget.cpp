#include <iostream>
#include "Widget.h"

Widget::Widget() {
	m_type = "Widget";
	m_shown = true;
}

Widget::Widget(const std::string &type, const std::string &name) {
	m_type = type;
	m_name = name;
	m_shown = true;
}

Widget::~Widget() {}

std::string Widget::type() const {
	return m_type;
}

Widget::Ptr Widget::parent() const {
	return m_parent;
}

void Widget::setParent(Widget::Ptr parent) {
	if (m_parent == parent)
		return;

	if (m_parent) {
		std::cout << m_parent << std::endl;
		Widget::Ptr old = m_parent;
		m_parent = 0;
		old->removeChild(shared_from_this());
	}

	if (parent) {
		m_parent = parent;
		parent->addChild(shared_from_this());
	}
}

const std::vector<Widget::Ptr> &Widget::children() const {
	return m_children;
}

void Widget::addChild(Widget::Ptr child) {
	if (child->parent().get() != this) {
		return child->setParent(shared_from_this());
	}

	m_children.push_back(child);
}

void Widget::removeChild(Widget::Ptr child) {
	if (child->parent() != 0) {
		return child->setParent(0);
	}

	auto it = std::find(m_children.begin(), m_children.end(), child);
	if (it != m_children.begin()) {
		m_children.erase(it);
	}
}

bool Widget::isShown() const {
	return m_shown;
}

void Widget::setShown(bool shown) {
	m_shown = shown;
}

Rect Widget::rect() const {
	return m_rect;
}

Vector2 Widget::pos() const {
	return m_rect.bottomLeft();
}

Vector2 Widget::size() const {
	return m_rect.size();
}

void Widget::setRect(const Rect &rect) {
	m_rect = rect;
}

void Widget::setPos(const Vector2 &pos) {
	m_rect.setPos(pos);
}

void Widget::setSize(const Vector2 &size) {
	m_rect.setSize(size);
}

void Widget::render() {}
