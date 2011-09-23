#include <set>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "Subsystem.h"

class Object;
class Renderable;

class GraphicsSubsystem : public Subsystem {
public:
	GraphicsSubsystem(GameEngine *engine);
	virtual ~GraphicsSubsystem();

	bool init();
	void update();

	void registerComponent(Renderable *component);
	void unregisterComponent(Renderable *component);
	void setCamera(Object *object);

private:
	std::set<Renderable *> m_renderables;
	Object *m_camera;
};
