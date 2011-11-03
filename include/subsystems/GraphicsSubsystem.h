#include <set>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "Color.h"
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

	void setColor(const Color &color);
	void render(const Renderable &renderable);

private:
	std::vector<Renderable *> m_renderables;
	Object *m_camera;
};