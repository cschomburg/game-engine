#ifndef GRAPHICSSUBSYSTEM_H
#define GRAPHICSSUBSYSTEM_H

#include <deque>
#include <map>
#include <memory>

#include "Rect.h"
#include "Subsystem.h"
#include "components/Positionable.h"
#include "components/Renderable.h"

class GameEngine;

typedef std::deque<Renderable::Ptr> RenderableList;

class GraphicsSubsystem : public Subsystem {
public:
	GraphicsSubsystem(GameEngine *engine);
	virtual ~GraphicsSubsystem();

	bool init();
	void update();

	void registerRenderable(Renderable::Ptr renderable);
	void unregisterRenderable(Renderable::Ptr renderable);
	Positionable::Ptr camera();
	void setCamera(Positionable::Ptr positionable);

	float scale() const;
	void setScale(float scale);
	Rect viewport() const;
	const Rect &screen() const;
	Vector2 toWorldPos(const Vector2 &pos, Anchor anchor = Anchor::center);

	void render(Renderable::Ptr renderable);

private:
	std::map<DrawLayer, RenderableList> m_renderables;
	Positionable::Ptr m_camera;

	float m_scale;
	Rect m_screen;
};

#endif /* end of include guard: GRAPHICSSUBSYSTEM_H */
