#include "Widget.h"
#include "subsystems/UISubsystem.h"

UISubsystem::UISubsystem(GameEngine *engine)
	: Subsystem(engine) {}

UISubsystem::~UISubsystem() {}

bool UISubsystem::init() {
	m_rootWidget = std::make_shared<Widget>("Widget", "Root");
	return true;
}

void UISubsystem::update() {}

void UISubsystem::render() {
	renderTree(m_rootWidget);
}

Widget::Ptr UISubsystem::rootWidget() const {
	return m_rootWidget;
}

void UISubsystem::renderTree(Widget::Ptr widget) {
	if (!widget || !widget->isShown())
		return;

	widget->render();
	for (auto child : widget->children()) {
		renderTree(child);
	}
}
